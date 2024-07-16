#all the imports
import cv2
import numpy as np
import os

#set the video resolution (height, width)
frameWidth = 720
frameHeight = 480

#own functions
def empty(a):
    pass

#function to save the trackbar positions to a file
def load_params_from_file(filename, trackbar_name, window_name, index, default_value):
    try:
        with open(filename, 'r') as f:
            param_str = f.read()
            txt = param_str.split('\n')
            if len(txt) <= index:
                value = default_value
            else:
                txt2 = txt[index].split(" = ")
                if len(txt2) == 2:
                    value = int(txt2[1])
                else:
                    value = default_value
    #if the file is not found or the index is out of range, set the value to default
    except (FileNotFoundError, IndexError, ValueError):
        value = default_value
    
    #create the trackbar and set the position to the value
    cv2.setTrackbarPos(trackbar_name, window_name, value)
    return value

#uses os.path.join to get the current folder and then joins the file name to the path
current_folder = os.getcwd()
file_path1 = os.path.join(os.path.dirname(__file__), 'G_params.txt')
file_path2 = os.path.join(os.path.dirname(__file__), 'R_params.txt')

# all of the trackbars for the color green
cv2.namedWindow("G_HSV")
cv2.resizeWindow("G_HSV", 640, 240)
cv2.createTrackbar("G HUE Min", "G_HSV", 0, 179, empty)
cv2.createTrackbar("G HUE Max", "G_HSV", 179, 179, empty)
cv2.createTrackbar("G SAT Min", "G_HSV", 0, 255, empty)
cv2.createTrackbar("G SAT Max", "G_HSV", 255, 255, empty)
cv2.createTrackbar("G VAL Min", "G_HSV", 0, 255, empty)
cv2.createTrackbar("G VAL Max", "G_HSV", 255, 255, empty)

# all of the trackbars for the color red
cv2.namedWindow("R_HSV")
cv2.resizeWindow("R_HSV", 640, 240)
cv2.createTrackbar("R HUE Min", "R_HSV", 0, 179, empty)
cv2.createTrackbar("R HUE Max", "R_HSV", 179, 179, empty)
cv2.createTrackbar("R SAT Min", "R_HSV", 0, 255, empty)
cv2.createTrackbar("R SAT Max", "R_HSV", 255, 255, empty)
cv2.createTrackbar("R VAL Min", "R_HSV", 0, 255, empty)
cv2.createTrackbar("R VAL Max", "R_HSV", 255, 255, empty)

# opens the file "G_params.txt" and reads the trackbar positions
G_h_min = load_params_from_file(file_path1, "G HUE Min", "G_HSV", 0, default_value=0)
G_h_max = load_params_from_file(file_path1, "G HUE Max", "G_HSV", 1, default_value=179)
G_s_min = load_params_from_file(file_path1, "G SAT Min", "G_HSV", 2, default_value=0)
G_s_max = load_params_from_file(file_path1, "G SAT Max", "G_HSV", 3, default_value=255)
G_v_min = load_params_from_file(file_path1, "G VAL Min", "G_HSV", 4, default_value=0)
G_v_max = load_params_from_file(file_path1, "G VAL Max", "G_HSV", 5, default_value=255)

# opens the file "R_params.txt" and reads the trackbar positions
R_h_min = load_params_from_file(file_path2, "R HUE Min", "R_HSV", 0, default_value=0)
R_h_max = load_params_from_file(file_path2, "R HUE Max", "R_HSV", 1, default_value=179)
R_s_min = load_params_from_file(file_path2, "R SAT Min", "R_HSV", 2, default_value=0)
R_s_max = load_params_from_file(file_path2, "R SAT Max", "R_HSV", 3, default_value=255)
R_v_min = load_params_from_file(file_path2, "R VAL Min", "R_HSV", 4, default_value=0)
R_v_max = load_params_from_file(file_path2, "R VAL Max", "R_HSV", 5, default_value=255)


# start the video capture with the Media Foundation backend
for i in range(10):
    cap = cv2.VideoCapture(i, cv2.CAP_DSHOW)  # or cv2.CAP_V4L
    ret, frame = cap.read()
    if ret:
        print(f"Camera found at index {i}")
        break
    else:
        print(f"No camera found at index {i}")

if cap is None:
    print("No camera found.")
    exit()

cap.set(3, frameWidth)
cap.set(4, frameHeight)

#start the while loop
while True:    
    ret, img = cap.read()
    imgHsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    
    #get the trackbar positions for the color green
    G_h_min = cv2.getTrackbarPos("G HUE Min", "G_HSV")
    G_h_max = cv2.getTrackbarPos("G HUE Max", "G_HSV")
    G_s_min = cv2.getTrackbarPos("G SAT Min", "G_HSV")
    G_s_max = cv2.getTrackbarPos("G SAT Max", "G_HSV")
    G_v_min = cv2.getTrackbarPos("G VAL Min", "G_HSV")
    G_v_max = cv2.getTrackbarPos("G VAL Max", "G_HSV")
    
    #get the positions for the color green
    G_lower = np.array([G_h_min, G_s_min, G_v_min])
    G_upper = np.array([G_h_max, G_s_max, G_v_max])
    G_mask = cv2.inRange(imgHsv, G_lower, G_upper)

    #get the trackbar positions for the color red
    R_h_min = cv2.getTrackbarPos("R HUE Min", "R_HSV")
    R_h_max = cv2.getTrackbarPos("R HUE Max", "R_HSV")
    R_s_min = cv2.getTrackbarPos("R SAT Min", "R_HSV")
    R_s_max = cv2.getTrackbarPos("R SAT Max", "R_HSV")
    R_v_min = cv2.getTrackbarPos("R VAL Min", "R_HSV")
    R_v_max = cv2.getTrackbarPos("R VAL Max", "R_HSV")

    #get the positions for the color red1
    R_lower1 = np.array([0, R_s_min, R_v_min])
    R_upper1 = np.array([R_h_min, R_s_max, R_v_max])
    R_mask1 = cv2.inRange(imgHsv, R_lower1, R_upper1)

    #get the positions for the color red2
    R_lower2 = np.array([R_h_max, R_s_min, R_v_min])
    R_upper2 = np.array([179, R_s_max, R_v_max])
    R_mask2 = cv2.inRange(imgHsv, R_lower2, R_upper2)

    #calculate summary mask from mask1 and mask2
    R_mask = cv2.bitwise_or(R_mask1, R_mask2)

    flipped_img = cv2.flip(img, 0)
    flipped_G_mask = cv2.flip(G_mask, 0)
    flipped_R_mask = cv2.flip(R_mask, 0)

    #live stream the color green
    cv2.imshow('livestream', flipped_img)
    cv2.imshow('G_maskstream', flipped_G_mask)
    cv2.imshow('R_maskstream', flipped_R_mask)
    
    if cv2.waitKey(10) == ord('x'):
        break

#save the color green parameters to the txt
G_paramstr = 'G_h_min = ' + str(G_h_min) + '\n' + 'G_h_max = ' + str(G_h_max) + '\n'
G_paramstr = G_paramstr + 'G_s_min = ' + str(G_s_min) + '\n' + 'G_s_max = ' + str(G_s_max) + '\n'
G_paramstr = G_paramstr + 'G_v_min = ' + str(G_v_min) + '\n' + 'G_v_max = ' + str(G_v_max) + '\n'

# Opens the text file and writes the green params
with open(file_path1, 'w') as f:
    f.write(G_paramstr)

#save the color red parameters to the txt
R_paramstr = 'R_h_min = ' + str(R_h_min) + '\n' + 'R_h_max = ' + str(R_h_max) + '\n'
R_paramstr = R_paramstr + 'R_s_min = ' + str(R_s_min) + '\n' + 'R_s_max = ' + str(R_s_max) + '\n'
R_paramstr = R_paramstr + 'R_v_min = ' + str(R_v_min) + '\n' + 'R_v_max = ' + str(R_v_max) + '\n'

#opens the text file and writes the red params
with open(file_path2, 'w') as f:
    f.write(R_paramstr)

#if the waitkey is pressed, the video capture will stop and the new parameters will be saved
cap.release()
cv2.destroyAllWindows()
