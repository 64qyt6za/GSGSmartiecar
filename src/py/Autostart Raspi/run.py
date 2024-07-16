from datetime import datetime
import time
import cv2

# own functions
import lcd
import arduino
import imgProc

lastDisplayTime = 0.0


def endProgram(status, msg):
    if status == 0:
        mytext = "Done"
        lcd.setText(mytext)
        # white
        lcd.setColor_white()
        imgProc.stopCam()
        exit(0)
    else:
        mytext = msg
        lcd.setColor_red()
        lcd.setText(mytext)
        imgProc.stopCam()
        raise


def displayData(data):
    global lastDisplayTime
    now = time.time()
    deltaTime = lastDisplayTime - now
    if deltaTime > 0.2: 
        lcd.setText(data)
        lastDisplayTime = now
    return

############################################################################################################################################
# MAIN PROGRAM
############################################################################################################################################
try:
    currentDateAndTime = datetime.now()
    mytext = "Main program"
    lcd.setText(mytext)
    displayCount = 0
    # red
    lcd.setColor_red()
    print("Run started at ", currentDateAndTime)

    #init image processor: read stored filter values for red and green
    imgProc.init()

    # start camera from img processor module
    ret = imgProc.startCam()

    if ret == False:
        endProgram(1, "cam ERR")

    # arduino handshake function
    ret = arduino.handshake()

    if ret == False:
        endProgram(2, "ino ERR")

    # yellow for ready
    lcd.setColor_yellow()

    # set the text
    lcd.print("ready\n")

    print("start loop")

    lastDisplayTime = time.time()
    time.sleep(0.5)
    while True:
        # get image from img processor module
        img = imgProc.getImg()        

        # process image from img processor module
        data = imgProc.procImg(img)
        # check if arduino requested data
        arduino.answer2req(data)
        
        # display result data every 200 msec
        if time.time() - lastDisplayTime > 0.15:
            lcd.setText(data)
            lastDisplayTime = time.time()

        #has to be fixed
        #displayData(data)

    ########################################################
    #    Program end
    ########################################################
    endProgram(0, "OK")

except Exception as err:
    
    endProgram(3, "CRASH")
