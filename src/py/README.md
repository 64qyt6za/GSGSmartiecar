# python code description
## trackbars
the **[trackbar](https://github.com/Nezar187/GSG_SmartiecarV2/blob/86f0c1b14511880a173588d8bd0babd93a239858/src/py/trackbars)** folder has the code for the trackbars that are used to adjust the corrct values for the HSV and RGB filters for the image processor the pi uses.

## Tools
the **[Tools](https://github.com/Nezar187/GSG_SmartiecarV2/blob/86f0c1b14511880a173588d8bd0babd93a239858/src/py/Tools)** folder has the last code for the color settings which are optimal to the raspberry pi camera in order to process correct images.

## images
the **[images](https://github.com/Nezar187/GSG_SmartiecarV2/blob/86f0c1b14511880a173588d8bd0babd93a239858/src/py/images)** folder has the raw image and the cropped image.

## blobtest
the **[blobtest](https://github.com/Nezar187/GSG_SmartiecarV2/blob/86f0c1b14511880a173588d8bd0babd93a239858/src/py/blobtest)** folder contains a blob detecor test program which is used to test the blob detector on a live camera feed for any errors. the images are the result of the blob detector.

## Autostart Raspi
the **[Autostart Raspi](https://github.com/Nezar187/GSG_SmartiecarV2/blob/86f0c1b14511880a173588d8bd0babd93a239858/src/py/Autostart_Raspi)** folder contains the code that is automatically ran as soon as power is coming through both the arduino and raspberry pi. It has the main code for the communication, image processing, and the blob detector for the car.