from grove_rgb_lcd import *

#all used lcd colors for py

def setColor_red():
    setRGB(1,254,0)

def setColor_green():
    setRGB(4,251,0)

def setColor_blue():
    setRGB(16,239,0)
    
def setColor_yellow():
    setRGB(5,250,0)

def setColor_white():
    setRGB(21,234,0)

def setColor_purple():
    setRGB(17,238,0)

def setColor_none():
    setRGB(0,0,0)
    
def print(message):
    setText(message)