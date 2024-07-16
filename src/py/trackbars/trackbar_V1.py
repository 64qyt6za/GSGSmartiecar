# all the imports
import cv2
import numpy as np

#set video resolution (height, width)
frameWidth = 320
frameHeight = 240

#own functions
def empty(a):
    pass

# load Green stored Params
def load_params_from_file(filename, trackbar_name, window_name, index):
    f = open(filename, 'r')
    param_str = f.read()
    txt = param_str.split('\n')
    txt2 = txt[index].split(" = ")
    value = int(txt2[1])
    cv2.setTrackbarPos(trackbar_name, window_name, value)
    f.close()


#trackbar main program
cv2.namedWindow("HSV")
cv2.resizeWindow("HSV", 640, 240)
cv2.createTrackbar("G HUE Min", "HSV", 0, 179, empty)
cv2.createTrackbar("G HUE Max", "HSV", 179, 179, empty)
cv2.createTrackbar("G SAT Min", "HSV", 0, 255, empty)
cv2.createTrackbar("G SAT Max", "HSV", 255, 255, empty)
cv2.createTrackbar("G VAL Min", "HSV", 0, 255, empty)
cv2.createTrackbar("G VAL Max", "HSV", 255, 255, empty)


load_params_from_file("G_params.txt", "G HUE Min", "HSV", 0)
load_params_from_file("G_params.txt", "G HUE Max", "HSV", 1)
load_params_from_file("G_params.txt", "G SAT Min", "HSV", 2)
load_params_from_file("G_params.txt", "G SAT Max", "HSV", 3)
load_params_from_file("G_params.txt", "G VAL Min", "HSV", 4)
load_params_from_file("G_params.txt", "G VAL Max", "HSV", 5)

#start video stream
cap = cv2.VideoCapture(0)
cap.set(3, frameWidth)
cap.set(4, frameHeight)

#livestream main loop
while True:    
    ret, img = cap.read()
    imgHsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
 
    G_h_min = cv2.getTrackbarPos("G HUE Min", "HSV")
    G_h_max = cv2.getTrackbarPos("G HUE Max", "HSV")
    G_s_min = cv2.getTrackbarPos("G SAT Min", "HSV")
    G_s_max = cv2.getTrackbarPos("G SAT Max", "HSV")
    G_v_min = cv2.getTrackbarPos("G VAL Min", "HSV")
    G_v_max = cv2.getTrackbarPos("G VAL Max", "HSV")

    G_lower = np.array([G_h_min, G_s_min, G_v_min])
    G_upper = np.array([G_h_max, G_s_max, G_v_max])
    G_mask = cv2.inRange(imgHsv, G_lower, G_upper)

    #show images
    cv2.imshow('livestream', img)
    cv2.imshow('maskstream', G_mask)
    #saves the values only if pressed x
    if cv2.waitKey(10) == ord('x'):
        break

G_paramstr = 'G_h_min = ' + str(G_h_min) + '\n' + 'G_h_max = ' + str(G_h_max) + '\n'
G_paramstr = G_paramstr + 'G_s_min = ' +  str(G_s_min) + '\n' + 'G_s_max = ' + str(G_s_max) + '\n'
G_paramstr = G_paramstr + 'G_v_min = ' + str(G_v_min) + '\n' + 'G_v_max = ' + str(G_v_max) + '\n'
 
f = open('G_params.txt', 'w')
f.write(G_paramstr)
f.close()

#cleanup the windows
cap.release()
cv2.destroyAllWindows