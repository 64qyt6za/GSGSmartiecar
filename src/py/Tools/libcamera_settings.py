import libcamera
from picamera2 import Picamera2
from libcamera import controls
import time
import cv2

frameWidth = 320
frameHeight = 160

"""
cam = cv2.VideoCapture(0)  # or cv2.CAP_V4L
cam.set(cv2.CAP_PROP_FRAME_WIDTH, frameWidth)
cam.set(cv2.CAP_PROP_FRAME_HEIGHT, frameHeight)
cam.set(cv2.CAP_PROP_BRIGHTNESS,60.0)
cam.set(cv2.CAP_PROP_CONTRAST,100.0)
"""

cam = Picamera2()

# Camera configuration
# BGR = kompatibel mit opencv, RGB = standardbild

config = cam.create_preview_configuration(
    {"format": "RGB888", "size": (frameWidth, frameHeight)}
)
# config["transform"] = libcamera.Transform(hflip=1,vflip=1)
config["transform"] = libcamera.Transform(vflip=1)
cam.configure(config)
min_bright, max_bright, default_bright = cam.camera_controls["Brightness"]
min_contrast, max_contrast, default_contrast = cam.camera_controls["Contrast"]
min_sat, max_sat, default_sat = cam.camera_controls["Saturation"]

print("Brightness :", min_bright, max_bright, default_bright)
print("Contrast :", min_contrast, max_contrast, default_contrast)
print("Saturation :", min_sat, max_sat, default_sat)


cam.set_controls(
    {"FrameRate": 40, "Brightness": 0.5, "Saturation": 3.0, "Contrast": 1.5}
)
cam.set_controls({"AwbEnable": 1})
cam.start()
time.sleep(2)
"""
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
"""

imgcount = 0
imgtime = 0.0

imgraw = cam.capture_array()
cv2.imshow("Testraw", imgraw)
start = time.time()
while True:

    # imgraw = cam.read()
    imgraw = cam.capture_array()

    # crop Region of Interest img[y:y+h, x:x+w]
    # img_h = round(0.56 * frameHeight)
    # img_w = frameWidth
    # img = imgraw[0:img_h,0:img_w]
    # img = cv2.flip(img,-1)

    img = imgraw

    cv2.imshow("Testraw", img)
    imgcount = imgcount + 1
    endtime = time.time()
    imgtime = endtime - start
    if cv2.waitKey(1) == ord("x"):
        break

print("Frames processed: ", imgcount)
print("Time: ", imgtime)
print("Framerate: ", imgcount / imgtime)
cam.stop()
cv2.destroyAllWindows()
