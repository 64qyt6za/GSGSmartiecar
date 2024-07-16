import cv2
import time

frameWidth = 320
frameHeight = 240

cam = cv2.VideoCapture(0)  # or cv2.CAP_V4L
cam.set(cv2.CAP_PROP_FRAME_WIDTH, frameWidth)
cam.set(cv2.CAP_PROP_FRAME_HEIGHT, frameHeight)
cam.set(cv2.CAP_PROP_BRIGHTNESS,60.0)
cam.set(cv2.CAP_PROP_CONTRAST,100.0)


value = cam.get(cv2.CAP_PROP_FRAME_HEIGHT)
print ("Height: ",value)
value = cam.get(cv2.CAP_PROP_FRAME_WIDTH)
print ("Width: ",value)
value = cam.get(cv2.CAP_PROP_FPS)
print ("FPS: ",value)
value = cam.get(cv2.CAP_PROP_BRIGHTNESS)
print ("Brightness: ",value)
value = cam.get(cv2.CAP_PROP_CONTRAST)
print ("Contrast: ",value)
value = cam.get(cv2.CAP_PROP_HUE)
print ("Hue: ",value)
value = cam.get(cv2.CAP_PROP_GAIN)
print ("Gain: ",value)


imgcount = 0
imgtime = 0.0

while (True):
    
    start = time.time()
    ret, imgraw = cam.read()
    
    #crop Region of Interest img[y:y+h, x:x+w]
    img_h = round(0.56 * frameHeight)
    img_w = frameWidth
    img = imgraw[0:img_h,0:img_w]
    img = cv2.flip(img,-1)
    
    contrast1 = 1.5
    brightness1 = 0.0
    #increase contrast and brightness with addWeighted
    #img_contrast1 = cv2.convertScaleAbs(img2, alpha=contrast1, beta=brightness1)
    img_contrast1 = cv2.addWeighted( img, contrast1, img, 0, brightness1)

    #img_contrast1 = img
    
    delta = time.time() -start
    imgcount = imgcount +1
    imgtime = imgtime + delta

    cv2.imshow("Testraw",img)
    cv2.imshow("Testcontrast",img_contrast1)

    
    if cv2.waitKey(1) == ord('x'):
        break

print ("Frames processed: ",imgcount)
print ("Time: ",imgtime)
print ("Framerate: ",imgcount/imgtime)
cam.release()