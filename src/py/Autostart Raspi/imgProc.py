import cv2
import numpy as np
import lcd
import time

imgcount = 0
# set the video resolution (height, width)
frameWidth = 320
frameHeight = 240

# empty cam obj
cam = None

#empty detector obj
detector = None
logged = False

R_mask = None
G_mask = None
pathMask_L = None
pathMask_R = None

# green and red trackbar values as globally accessable variables
G_h_min = 0
G_h_max = 0
G_s_min = 0
G_s_max = 0
G_v_min = 0
G_v_max = 0

R_h_min = 0
R_h_max = 0
R_s_min = 0
R_s_max = 0
R_v_min = 0
R_v_max = 0

wz_L_x1 = 40
wz_L_y1 = 40
wz_L_x2 = wz_L_x1 + 80
wz_L_y2 = wz_L_y1 + 70

wz_R_x1 = 320 - wz_L_x2
wz_R_y1 = wz_L_y1
wz_R_x2 = 320 - wz_L_x1
wz_R_y2 = wz_L_y2


def detectWalls(img):
    wall_L = 'N'
    wall_R = 'N'
    img_contrast1 = img
    #detector = cv2.SimpleBlobDetector_create()
    
    # crop wall collision zones and convert to grayscale to filter walls
    imgWallZone_L = img_contrast1[wz_L_y1:wz_L_y2, wz_L_x1:wz_L_x2]
    imgWallZone_L = cv2.cvtColor(imgWallZone_L,cv2.COLOR_BGR2GRAY)
    
    imgWallZone_R = img_contrast1[wz_R_y1:wz_R_y2, wz_R_x1:wz_R_x2]
    imgWallZone_R = cv2.cvtColor(imgWallZone_R,cv2.COLOR_BGR2GRAY)
    
       # dark parts (walls appear white in threshold image
    ret,imgWall_L = cv2.threshold(imgWallZone_L,70,255,cv2.THRESH_BINARY_INV)
    ret,imgWall_R = cv2.threshold(imgWallZone_R,70,255,cv2.THRESH_BINARY_INV)
    
    imgWall_L = cv2.medianBlur(imgWall_L,5)
    imgWall_R = cv2.medianBlur(imgWall_R,5)
 
    # Do a bitwise-and of pathMasks and image wall Zones to find walls:
    # walls are white, the path projection is white, too -> collisions occur in areas, that are white in both images

    collision_L = cv2.bitwise_and(imgWall_L,pathMask_L)
    collision_R = cv2.bitwise_and(imgWall_R,pathMask_R)
    
    # Invert result image to be usable in opencv blob detector
    collision_L = cv2.bitwise_not(collision_L)
    collision_R = cv2.bitwise_not(collision_R)

    collision_L = cv2.medianBlur(collision_L,5)
    collision_R = cv2.medianBlur(collision_R,5)

    # opencv does not detect blobs touching the border, therefore draw white frame
    collision_L = cv2.copyMakeBorder(collision_L,1,1,1,1, cv2.BORDER_CONSTANT, value=[255,255,255])
    collision_R = cv2.copyMakeBorder(collision_R,1,1,1,1, cv2.BORDER_CONSTANT, value=[255,255,255])

    wall_L_keypoints = detector.detect(collision_L)
    wall_R_keypoints = detector.detect(collision_R)

    # Noise is filtered by detector minimum area
    if len(wall_L_keypoints) > 0:
        wall_L = "Y"
        
    if len(wall_R_keypoints) > 0:
        wall_R = "Y"
        
    return wall_L, wall_R
    

def detectPillars(img):
    global R_mask
    global G_mask
    global logged

    img_contrast1 = img
    # convert to HSV to filter colors
    imgHsv = cv2.cvtColor(img_contrast1, cv2.COLOR_BGR2HSV)

    # get the positions for the color green
    G_lower = np.array([G_h_min, G_s_min, G_v_min])
    G_upper = np.array([G_h_max, G_s_max, G_v_max])
    G_mask = cv2.inRange(imgHsv, G_lower, G_upper)

    # B_lower = np.array([B_h_min, B_s_min, B_v_min])
    # B_upper = np.array([B_h_max, B_s_max, B_v_max])
    # B_mask = cv2.inRange(imgHsv, B_lower, B_upper)

    # get the positions for the color red1
    R_lower1 = np.array([0, R_s_min, R_v_min])
    R_upper1 = np.array([R_h_min, R_s_max, R_v_max])
    R_mask1 = cv2.inRange(imgHsv, R_lower1, R_upper1)

    # get the positions for the color red2
    R_lower2 = np.array([R_h_max, R_s_min, R_v_min])
    R_upper2 = np.array([179, R_s_max, R_v_max])
    R_mask2 = cv2.inRange(imgHsv, R_lower2, R_upper2)

    # calculate summary mask from mask1 and mask2
    R_mask = cv2.bitwise_or(R_mask1, R_mask2)

    # remove noise pixels
    R_mask = cv2.medianBlur(R_mask, 5)
    G_mask = cv2.medianBlur(G_mask, 5)

    # opencv does not detect blobs touching the border, therefore draw black frame
    R_mask = cv2.copyMakeBorder(
        R_mask, 1, 1, 1, 1, cv2.BORDER_CONSTANT, value=[0, 0, 0]
    )
    G_mask = cv2.copyMakeBorder(
        G_mask, 1, 1, 1, 1, cv2.BORDER_CONSTANT, value=[0, 0, 0]
    )
    # B_mask = cv2.copyMakeBorder(B_mask,1,1,1,1, cv2.BORDER_CONSTANT, value=[0,0,0])

    # Invert masks, Find blobs and draw on the contrast image
    # G_mask_inv = cv2.bitwise_not(G_mask)
    # R_mask_inv = cv2.bitwise_not(R_mask)
    # B_mask_inv = cv2.bitwise_not(B_mask)

    green_contours = cv2.findContours(
        G_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE
    )
    green_contours = (
        green_contours[0] if len(green_contours) == 2 else green_contours[1]
    )

    g_h = 0
    g_maxh = 0
    g_num = 0
    for i in green_contours:  # find height of tallest green object
        g_x, g_y, g_w, g_h = cv2.boundingRect(i)
        area = int(cv2.contourArea(i))
        if g_h > g_maxh:
            g_maxh = g_h
            g_num = i
            g_cen_x = g_x + g_w / 2
            g_cen_y = g_y + g_h / 2
            g_area = area
            g_height = g_h
            g_width = g_w

    red_contours = cv2.findContours(R_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    red_contours = red_contours[0] if len(red_contours) == 2 else red_contours[1]

    r_h = 0
    r_maxh = 0
    r_num = 0
    for i in red_contours:  # find height of tallest green object
        r_x, r_y, r_w, r_h = cv2.boundingRect(i)
        area = int(cv2.contourArea(i))
        if r_h > r_maxh:
            r_maxh = r_h
            r_num = i
            r_cen_x = r_x + r_w / 2
            r_cen_y = r_y + r_h / 2
            r_area = area
            r_height = r_h
            r_width = r_w

    if g_maxh > r_maxh:
        pillar_col = "G"
        pillar_x = round(g_cen_x)
        pillar_y = round(g_cen_y)
        pillar_dist = g_area
        pillar_height = g_height
        pillar_width = g_width
        lcd.setColor_green()

    elif (r_maxh >= g_maxh) and (r_maxh > 0):
        pillar_col = "R"
        pillar_x = round(r_cen_x)
        pillar_y = round(r_cen_y)
        pillar_dist = r_area
        pillar_height = r_height
        pillar_width = r_width
        lcd.setColor_red()
        

    else:
        pillar_col = "U"
        pillar_x = 0
        pillar_y = 0
        pillar_height = 0
        pillar_width = 0
        lcd.setColor_white()
    
    return pillar_col, pillar_x, pillar_y, pillar_height, pillar_width


def startCam():
    global cam

    try:
        cam = cv2.VideoCapture(0)
        cam.set(cv2.CAP_PROP_FRAME_WIDTH, frameWidth)
        cam.set(cv2.CAP_PROP_FRAME_HEIGHT, frameHeight)
        cam.set(cv2.CAP_PROP_BRIGHTNESS, 80.0)
        cam.set(cv2.CAP_PROP_CONTRAST, 80.0)
        ret, frame = cam.read()  # read test frame
        return True

    except:
        print("cam err")
        return False


def stopCam():
    global cam
    cam.release()


def getImg():
    ret, imgraw = cam.read()
    imgraw2 = cv2.flip(imgraw, -1)
    # crop Region of Interest img[y:y+h, x:x+w]
    img_h = 134
    img_w = 320
    img = imgraw[0:img_h, 0:img_w]
    img2 = cv2.flip(img, -1)

    return img2


def procImg(img):
    data = "U 0 0"
    # global imgHsv
    # global imgWall_L
    # global imgWall_R
    # global imgWallZone_L
    # global imgWallZone_R
    global R_mask
    global G_mask
    global logged
     # global B_mask

    # init return values
    pillar_col = "U"
    pillar_dist = 0
    pillar_x = 0
    pillar_y = 0
    pillar_height = 0
    pillar_width = 0
    wall_L = "N"
    wall_R = "N"

    if logged == False:
        print("R_h_min=",R_h_min)
        print("R_s_min=",R_s_min)
        print("R_v_min=",R_v_min)
        print("R_h_max=",R_h_max)
        print("R_s_max=",R_s_max)
        print("R_v_max=",R_v_max)
        logged = True
            
    img_contrast1 = img
    
    #call the wall detector
    wall_L, wall_R = detectWalls(img_contrast1)
    pillar_col, pillar_x, pillar_y, pillar_height, pillar_width = detectPillars(img_contrast1)
    data = pillar_col + " " + str(pillar_x) + " " + str(pillar_height) + " " + wall_L + " " + wall_R
    return data


def load_params_from_file(filename, trackbar_name, window_name, index, default_value):
    try:
        with open(filename, "r") as f:
            param_str = f.read()
            txt = param_str.split("\n")
            if len(txt) <= index:
                value = default_value
            else:
                txt2 = txt[index].split(" = ")
                if len(txt2) == 2:
                    value = int(txt2[1])
                else:
                    value = default_value
    # if the file is not found or the index is out of range, set the value to default
    except (FileNotFoundError, IndexError, ValueError):
        value = default_value

    return value


# reads the trackbar values
def init():
    global G_h_min
    global G_h_max
    global G_s_min
    global G_s_max
    global G_v_min
    global G_v_max
    global R_h_min
    global R_h_max
    global R_s_min
    global R_s_max
    global R_v_min
    global R_v_max
    global detector
    global logged
    
    global pathMask_L
    global pathMask_R
    
    logged = False
  
  
    #create blob detector
    blob_params = cv2.SimpleBlobDetector_Params()
    blob_params.filterByArea = True
    blob_params.minArea = 30
    blob_params.maxArea = 10000
    blob_params.filterByCircularity = False
    blob_params.filterByConvexity = False
    blob_params.filterByInertia = False

    # Create blob detectors
    detector = cv2.SimpleBlobDetector_create(blob_params)

# hard coded paths
    file_path1 = "/home/pi/Desktop/tools/G_params.txt"
    file_path2 = "/home/pi/Desktop/tools/R_params.txt"

    # opens the file "G_params.txt" and reads the trackbar positions
    G_h_min = load_params_from_file(
        file_path1, "G HUE Min", "G_HSV", 0, default_value=0
    )
    G_h_max = load_params_from_file(
        file_path1, "G HUE Max", "G_HSV", 1, default_value=179
    )
    G_s_min = load_params_from_file(
        file_path1, "G SAT Min", "G_HSV", 2, default_value=0
    )
    G_s_max = load_params_from_file(
        file_path1, "G SAT Max", "G_HSV", 3, default_value=255
    )
    G_v_min = load_params_from_file(
        file_path1, "G VAL Min", "G_HSV", 4, default_value=0
    )
    G_v_max = load_params_from_file(
        file_path1, "G VAL Max", "G_HSV", 5, default_value=255
    )

    # opens the file "R_params.txt" and reads the trackbar positions
    R_h_min = load_params_from_file(
        file_path2, "R HUE Min", "R_HSV", 0, default_value=0
    )
    R_h_max = load_params_from_file(
        file_path2, "R HUE Max", "R_HSV", 1, default_value=179
    )
    R_s_min = load_params_from_file(
        file_path2, "R SAT Min", "R_HSV", 2, default_value=0
    )
    R_s_max = load_params_from_file(
        file_path2, "R SAT Max", "R_HSV", 3, default_value=255
    )
    R_v_min = load_params_from_file(
        file_path2, "R VAL Min", "R_HSV", 4, default_value=0
    )
    R_v_max = load_params_from_file(
        file_path2, "R VAL Max", "R_HSV", 5, default_value=255
    )
    
    #load Mask for path projection
    file_path3 = "/home/pi/Desktop/tools/Path_mask.jpg"
    pathImg = cv2.imread(file_path3)
    pathGray = cv2.cvtColor(pathImg,cv2.COLOR_BGR2GRAY)

    #crop wall collision zones from path Image
    pathGray_L = pathGray[wz_L_y1:wz_L_y2,wz_L_x1:wz_L_x2]
    pathGray_R = pathGray[wz_R_y1:wz_R_y2,wz_R_x1:wz_R_x2]

    # make masks for wall zones
    ret,pathMask_L = cv2.threshold(pathGray_L,10,255,cv2.THRESH_BINARY)
    ret,pathMask_R = cv2.threshold(pathGray_R,10,255,cv2.THRESH_BINARY)
    


##############################################################################################################################
# Main
##############################################################################################################################

# =============================================================
# Main for interactive test run
# =============================================================
if __name__ == "__main__":
    init()
    startCam()
    lcd.setColor_white()
    while True:
        # get image from img processor module
        img = getImg()

        # process image from img processor module
        data = procImg(img)
        lcd.print(data)
        time.sleep(0.1)

        cv2.imshow("live", img)
        cv2.imshow("red", R_mask)
        cv2.imshow("green", G_mask)
        cv2.waitKey(1)
