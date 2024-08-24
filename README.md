<a name="top"></a>

# WRO European Finals 2024 by Team Smart Riders 

![logo](https://github.com/Nezar187/GSG_SmartiecarV2/assets/131591590/ee130cae-55c6-4d7b-ba02-26129456f831)

## Table of Contents 📚👇

1. [Overview](#overview) 🌟
2. [Design Process](#Design-Process)🔧
3. [Car Photos](#carphoto)
4. [Mobility Management](#Mobility-Management)
    - [Chassis](#Chassis)
    - [Assembly Instructions](#assembly-instructions) 🛠
    - [Driving Motor and Gearing](#Driving-Motor-and-Gearing)
    - [Steering Mechanism](#Steering-Mechanism)
    - [Power and Sense Management](#Power-and-Sense-Management)  
    - [Power supply](#Power-supply)
    - [Controllers](#Controllers)
    - [Sensors](#Sensors)
    - [Camera](#camera)
    - [Schematics](#schematics) 📐👀
    - [Components List](#components-list) 🔍
5. [Software Design](#software) 💻👨‍💻
    - [Software Development](#software-development)
    - [Opening Race](#opening-race)
    - [Obstacle Race](#obstacle-race)
    - [Programming Languages](#programming-languages) 👩‍💻
    - [Dependencies](#dependencies) 
6. [Utilities](#utilities) 🛠
    - [Failsafe Mechanisms](#failsafe)
    - [Debugging Tools](#debugging-tools) 🐞🔍
7. [Team Photos](#team-photos) 📸
8. [Demonstration Videos](#demonstration-videos) 🎥
9. [Contributors](#contributors) 👥
10. [Resources](#sources) ℹ

   
<a name="overview"></a>


## Overview 🌟

![Foto 01 10 23, 13 22 02](https://github.com/Nezar187/GSG_SmartiecarV2/assets/131591590/60bbc2ea-8552-432e-a204-dabbc420be3d)

Welcome to the official GitHub repository for Team Smart Riders from Germany, participating in the WRO World Finals 2023. This repository contains all the code, documentation, and resources for our project, SmartiecarV2. We have used scoring criteria from the ruleblock as headings in our documentation to make it easy to navigate our repository.

<img src="https://github.com/Nezar187/GSG_SmartiecarV2/assets/131591590/7b0c5513-870f-475c-9993-cfca6aa5659f" width="75%">

For the wold final we decided to redesign our future engineers car.
Now our car consists of an arduino which controls the sensors and the motors and a raspbarry pi which does all the image prossesing in the obstacle race.


<a name="Design-Process"></a>


### Design Process

For the World Final, we ran a throurogh analysis of our German Final car version to identify, what worked well and what did not works so well.
From that, we compiled a list what to keep and what we want to improve..

Results of analysis:
ok:
- arduino work with ultrasonic and gyro
- rgb lcd display for feedback
- gyro sensor precision

inprove:
- image processing unstable
- curve detection in obsticle race
- precision
- stopping in the start area
- hardware repairs too time consuming due to complex chassis
- car track width to large (17cm)
- driving low speed
- breaking distance to long

  For the WRO Final car, we designed 3 modular layers to seperate funktions from each other and make it much easier to repair.
  We adress the detailed solutions we found to the identified issues in detail in the following chapters.

<img src="https://github.com/Nezar187/GSG_SmartiecarV2/assets/131591590/40d8d0fe-efb5-4642-bb60-c71df9333944" width="75%">



<a name="carphoto"></a>


### Car Photos

Here are our official photos of our car:

![All Pictures](https://github.com/Nezar187/GSG_SmartiecarV2/assets/131177565/9b42ea9a-2da7-4fc8-b259-429de187d35e)


For high resulution pictures please visit: [Car Photos](Carphotos)

<a name="Mobility-Management"></a>


### Mobility Management 


<a name="Chassis"></a>


### Chassis

We used the Totemmaker construction system to design and build our own car chassis. This set consits of plastic beams and plates as structural
elements and aluminium connectors. For specific parts as the front of the wheel barrel and the motor bracket, totemmaker.net offers a free STL-Libary of 3D-printable parts.
To get a small but strong structure, we used rectangular grids as the basic element of each layer. The first layer had to be as thin as possible but still had to contain the motor, the axles and the servo. We did not have much room to work with. Thats why we did not use a baseplate. A baseplate would have been to large for our car. We just build a stable rectangular frame, two beams wide, and mounted the front and back axle to it. After that we rounded up the edges of the layer because it does not have much space between it and the game field and our field was a bit wavy.
Because the last car was difficult to repair we wanted to construct the next version of our car with that in mind. We now have a modular system with three individual layers. The top two have the same base of contruction. For both layers we started with a stable rectangular frame of four plastic beams. These beams make the layers stable and strong but not to heavy at the same time. We wanted the layers to be easily connected to each other with screws. The third layer just has two extra beams for the ultrasonic sensors. Because the third layer is the "sensors and control" layer, we wanted to mount the ultrasonic sensors to it. But it was to high. That is why we used the beams to lower them closer to the ground.

Layer 2:

<img src="https://github.com/Nezar187/GSG_SmartiecarV2/assets/131177565/ba4adc89-2f2b-4595-a860-c548b5dc5555" width="50%">


Layer 3:

<img src="https://github.com/Nezar187/GSG_SmartiecarV2/assets/131177565/86b0d644-9015-47d7-bda9-f8d0e95e0f0b" width="50%">

For more sketches of the chassis please visit [Schematics](schematics)


Tires:

In our building process we tested different tires from different manufacturers. We tested the tires that were included in the Totemmaker contruction
system, standard racing tires we bought from Funduino and onother set of tires with no tread pattern.
During the initial test drives, we noticed that the tires we took from the Totem Maker construction system were too large and were rubbing against the frame. The second set of tires from Funduino were smaller and harder, but they often caused oversteering when the car was turning sharply. Now, for the final setup, we are using softer tires without any tread pattern, which maximizes ground contact. 

<img src="https://github.com/Nezar187/GSG_SmartiecarV2/assets/131177565/5ae149b4-5e5d-40b0-987d-e4460998b52e" width="75%">


<a name="assembly-instructions"></a>


### Assembly Instructions 🛠

In order to build our car you have to build the different layers seperately and connect the later. 
First start with the first layer. Cut the beams and connectors to size and connect them like shown here:

![Layer 1 SIde](https://github.com/Nezar187/GSG_SmartiecarV2/assets/131177565/01643d91-ad0c-45a6-9f48-54e8f5fc4d56)

[Totemmaker Build Instructions](https://totemmaker.net/wiki/robocar-chassis-building-instruction/)
After you built the frame you can build and attach the front axle. You will need the 3D printed parts from Totemmaker.net. For the back axle we used parts from the Make-Block construction set, which we cut to size as well. Additionally you have to use another 3D printed part from Totemmaker.net to screw the motor in place. Because the frame is very thinn you will have to connect the motor with the back axle via a set of bevel gears. Next you build the second layer like shown in the schematics. You will have to cut the parts again:

<img src="https://github.com/Nezar187/GSG_SmartiecarV2/assets/131177565/41f219ce-67e9-4a65-90ca-390a18fd90e6" width="75%">

Next you have to again cut the beams and assemble them according to the schematics to build the third layer:

<img src="https://github.com/Nezar187/GSG_SmartiecarV2/assets/131177565/d80702c1-a0fb-4a31-8272-6fe0d7570646" width="75%">

Next you will have to put all of the other electronic components on the layers. The sensors and the controllers on the third layer. The power management on the second and the motor with the servo on the first.

<img src="https://github.com/Nezar187/GSG_SmartiecarV2/assets/131177565/88f3d4e9-18e9-400f-a58b-6c2d27d12d84" width="75%">




<a name="Driving-Motor-and-Gearing"></a>


### Driving Motor and Gearing

We tested two different motors. One which operates on 6V and another which does on 12V. In our last version of our car we used a 12V motor. We wanted to use the 6V motor so that we do not have so many different voltages in our car. In our testing the 6V motor broke quite often. The 12V motor was more reliable. That is why we decided to use the 12V motor instead of the 6V. After we had decided what motor to use we had to decide how to screw it to the frame. In our first version of our car the axis of the motor was parallel to the back axle. Because of the limited space we had we had to turn the motor so taht its axis pointed to the back axle. We connected the motor and the back axle with bevel gears for a 1:1 ratio.

<img src="https://github.com/Nezar187/GSG_SmartiecarV2/assets/131177565/f8b99575-93f0-4b29-bc44-e6aac457f7e1" width="50%">

In our previous car version, we used a L298D motor driver. We had several issues with motor control. 
With this driver, the minimum PWM speed control value to make the car start running was rather high, so we could not drive slow enough for a good control.
As a result, the braking distance was also rather long, almost 30cm. Additionally, the L298D dissipates 1.4V as heat during operation.
To solve these issues, we experimented with other motor drivers and finally decided to use the Cytron MD13S motor driver instead.
With this motor driver, the motor starts running at much lower PWM settings and therefore allows us to drive much slower. 
The braking distance is down to a few centimeters now. As it uses a different type (MOSFET) transistors, heat is much lower. 
And it has a nice cable plugin socket, which was very convenient for our hardware layers concept.
It also comes with a very good Arduino library by the manufacturer, which made it easy to use in the arduino software.


<img src="https://github.com/Nezar187/GSG_SmartiecarV2/assets/131591590/8894ff8a-f424-47e5-81c8-1b6b1415c278" width="50%">


<a name="Steering-Mechanism"></a>


### Steering Mechanism

We used the ackermann steering geometry for our steering mechanism. The idea behind the ackerman steering is that the inner wheel turs a bigger angle than the one on the
outside. In order for it to turn around the middle axis of the axle. We use a metal gear servo (Tower Pro MG995) because our car is very heavy. The axis of the servo is in the middle of the front axle. It is directly connected to the steering rod, because the power of the servo transfers better to the steering rod with a direct connection. Another reason for us to build a direct connection is that the first layer of our car is very thin and there is not much space to build any other connetion from the servo to the steering rod. 

We used a steering trapeze to calculate where to put the back axle of our car and the length of our steering rod. We drew it on a piece of paper and later transfered it to the computer.

Steering Trapeze:

<img src="https://github.com/Nezar187/GSG_SmartiecarV2/assets/131177565/d627f769-6dab-4882-8252-478ff478e4c7" width="50%">

Because of the layers in our car, the servo motor for the steering had to be mounted on the first (lowest) layer. Because of that it was difficult to connect the servo with the steering mechanism. The plastic beams from the layer around the servo limited its range of motion. That is why we had to extend the connection between the steering shaft and the servo. The servo is now directly connected to the steering mechanism via the steering shaft.

<img src="https://github.com/Nezar187/GSG_SmartiecarV2/assets/131177565/187e7521-fa72-4f78-aafa-8d5d0df6fac5" width="75%">


<a name="Power-and-Sense-Management"></a>


### Power and Sense Management
<img src="https://github.com/Nezar187/GSG_SmartiecarV2/assets/131591590/35a215e8-1b19-4504-bd92-aa972cfa088c" width="75%">


Our car has a special level called "Power and Sense Management" level.
On this level, there are important parts that affect the car´s performance and control.
At the center of Power and Sense Management is a step-up converter that is specifically responsible for the motor.
On the right side of this level we find the on/off switch.
There are two step-down converters on both the left and right sides of the vehicle. In addition to these components
and the motor driver is also housed on this level. 


<a name="Power-supply"></a>


### Power supply
<img src="https://github.com/Nezar187/GSG_SmartiecarV2/assets/131591590/7235a714-503e-4248-bcb2-d01d52edebd4" width="75%">





We use 7.4 V-Lithium-polymer battery as our central power supply it is locatet in the space between layers one and two.
In our previous car version, we used a 11.1 V Lipo. AS this one is very heavy, we decided to exchange it for a less heavy 7.4 V Lipo 
of the same capacity.
 we use a 3000 mAh lipo,as the Raspberry Pi is very Power-hungry when doeing image processing. 
The on/off switch is connectetet directly to the output of the Lipo Behind the switch,we disstribute the power to 2 step-down and one step-up converters .

The step-up converter produces 12V for our motor driver. 
The two step-downs both produce 5V,one is used for the controllers ( Raspberry  Pi and Arduino ), the other for the steering servo and lights.
See circuit diagram for details on connections.
[Schematics](#schematics)





<a name="Controllers"></a>


### Controllers
In our previous car version, we used an Arduino Nano as a controller and a Smart Camera Module for the image processing. 
Due to the problems with the smart camera solution, we wanted to replace it with a raspberry pi and our own image processing.
We considered moving all functionality over to raspberry pi but decided against it. The arduino with its sensors worked quite well.
We were afraid to hit hardware and compatibility problems we could not solve fast enough when running all on the raspberry pi.
Due to having two controllers, we needed to let them communicate with each other. The communication runs over serial interface.
We tried to establish the serial communcation via the RX/TX Pins of the raspberry pi and the arduino. 
As the raspberry pi runs on 3.3V and the arduino on 5V, we needed a level shifter in between. But this solution did not work, the connection failed.
Therefore, we got back to the easy way: the arduino is plugged into one of the USB ports of the raspberry pi.
The problem we had to solve with this setup is, that on Power-on, the raspberry pi always resets the arduino when it opens the serial connection.
We solved that with a software handshake between arduino and raspberry pi during startup.
The arduino is responsible to control all motors and sensors, the raspberry pi has a camera attached to it and does the image processing.


<a name="Sensors"></a>


### Sensors

Our car is equipped with a total of four sensors.
Three of them are ultrasonic sensors, which allow for the detection of nearby obstacles.
In addition our vehicle has a gyro sensor, which is located in the Third level of the car.
Our gyro sensor helps measure rotational movements, providing more precise control.


![Foto 01 10 23, 13 21 16](https://github.com/Nezar187/GSG_SmartiecarV2/assets/131591590/3d9320cd-b7b1-484e-a440-67566e307d7c)

In the front sensor grid, we have three ultrasonic sensors to measure distances to the left, the front and the right. 
The ultrasonics are all mounted in the front part, as we use them to detect the curves. In the opening race, some of the streets can be narrow. To run a good curve,
the car must sense the opening of the curve as soon as possible.
We chose the DFRobot ultrasonic boards as they can be mounted easily on our chassis. Additionally, they have plastic covers to avoid damage when the robot runs into something.
To run rather reliable turns and to go straight no matter which starting place, we use a Bosch BNO055 IMU sensor. 
This sensor has a gyroscope, an accelerometer and a compass onboard. What we need from the sensor is the orientation angle on the field. In theory, a gyroscope only would do that.
However, gyroscopes tend to drift, when mounted on moving vehicles. The BNO055 has an onboard processor to calculate reliable angles by combining measurements from all its sensors.
As the compass is unreliable indoors, we switch it off and run on gyroscope and accelerometer data only.

<a name="camera"></a>


### camera

One of the problems withour previous smart cam was the angle of view. We wanted to use a wide angle camera.
For raspberry pi 4, there are different options. The native raspberry pi v3 wide angle camera is not yet compatible with the opencv image processing package, so we could not use it.
We tested the Waveshare wide angle camera and skipped it, because the color saturation of the image was poor. In some light conditions, it was hard to distinguish green pillars and the walls.
The best fit was the raspberry pi HQ camera with M12 mount and a Arducam wide angle lens. The driver allows to set color saturation and brightness so we get a bright image with clear colors.
The disadvantage of this camera is, that it is rather big and heavy compared with the others.





<a name="schematics"></a>


### Schematics 📐

Circuit schematics and hardware layouts are available in the [Schematics folder](schematics).

Circuit Diagramm:

In our last car we used HCSR 04 Ultra- Sonic Sensors. The ones we use now are compatible but have a common echo and trigger pin. That is why we connected the two pins.

![circuit diagram3](https://github.com/Nezar187/GSG_SmartiecarV2/assets/131177565/fea9d000-b137-442d-b9b0-54673bf2bf8d)



<a name="components-list"></a>


### Components List 📦

Hardware components:
Chassis:
- Totemmaker construction set
- Totemmaker 3D Print elements
- For back axle Parts from Make-Block construction set

Driving and Steering components:
- Tower Pro MG995 Servo
- Motor Controller Cytron MD13S
- totem CHRGM25-370 Gear Box Motor (12.0V)
- Matrix Ep Rubber Tires (6,5 cm)

Sensors and Controllers:
- Arduino Nano
- Rasperry PI 4
- DFROBOT Ultrasonic sensors
- Gyro -> BNO-055
- Rasperry PI Camera
  
Powersupply and management:
- Lipo 7.4V
- Step Down Converter
- Step Up converter

Softwarepackages:


<a name="software"></a>


## Software 💻

<a name="software-development"></a>

### Software Development

Our car has two controllers, an arduino nano and a raspberry pi. 
For our Arduino software, we have used Microsoft Visual Studio Code as our IDE. We have directly synchronized VSCode with our source code repository on GitHub, which is part of our overall documentation repository.
The Arduino software is written in the Arduinio variant of C++.
The complete arduino source code listings are found in https://github.com/Nezar187/GSG_SmartiecarV2/tree/main/src/ino.
Our raspberry pi software is written in python 3. On the raspberry pi, we have used Thonny IDE as our development tool. The updating of the source code repository on Github for our python software has been done manually.
The complete raspberry pi python source code listings are found in https://github.com/Nezar187/GSG_SmartiecarV2/tree/main/src/py.
We have structured our source code in layers. For the arduino software, we have put all functions dealing with specific hardware components or specific interfaces in separate header files. This allows us to include them in the opening race and obstacle race programs as well. 
Changes and fixes then apply to both programms immediately.
In the main programs for the two race types, we have created own functions for repeating movement sequences like curves or steerig straight using gyro orientation angles.
For a better overview, the main programms themselves are structured in race phases.



![blockdiagram_software](https://github.com/Nezar187/GSG_SmartiecarV2/assets/131591590/5b52f9c3-a2cb-43c9-ac6e-0e6e4c6b5113)


<a name="opening-race"></a>

### Opening Race
In the opening race, we only use the arduino and the sensors attached to it, so the software for the opening race is arduino software only.
The opening race consists of four phases: init phase, start phase, run phase and end phase.

![Diagram_open_phases](https://github.com/Nezar187/GSG_SmartiecarV2/assets/131591590/2c19f09d-0d59-42b5-858b-588c2e19e0fa)

## Init Phase

In the init phase, we initialize all sensors and motors. Next is a handshake with the raspberry pi, even though we do not really use the pi during the opening race. 
The handshake is necessary, because the arduino is powered via the raspberry pi's USB port and we do not switch off the raspberry pi's image processing software during the opening race.
When the image processing software on the raspberry pi starts, it automatically resets the arduino. 
As the arduino boots much faster as the raspberry pi, there is a risk that we would start the opening race before the reset is done.
To avoid that, we use the handshake to be sure that the reset is done before the arduino indicates that the init is completed.
To show the current state of the software, we use a RGB LCD display. During initialization and handshake, the background color is red. 
When all sensors are ready, the background color switches to yellow. Ee get a first set of measurements from all sensors and display them on the screen, so we can see if we get proper readings before the race is started.
The arduino already tries to determine the turning direction (clockwise = R(ight) or counter-clockwise = L(eft)) of the race. 
If the starting position is in a narrow street and distance to one of the walls is < 10cm, this is the inner wall. Now the arduino waits for the start button to be pressed.


![init phase](<src/ino/flow charts/init phase.jpg>)

## Start phase

In the start phase, the arduino first runs the motor at slow speed. If the car is placed very close to a wall, it first steers away from that wall to avoid hitting it.
The car now drives slowly and steers straight using its gyro, until one of the side ultrasonics measure a distance > 80 cm, which indicates a curve. If the turning direction was not already known, it is now.
The arduino now runs the first curve.
To make the most use of the gyro, we measure the orientation angle and map it to -180.0 to 180.0 degrees. 
Whith every call of the gyro, we also accumulate the total angle the car has turned, so we can easily calculate the target angle of a curve by just adding 90 degrees for clockwise or subtracting 90 degrees for counter-clockwise.


![Diagram_open_start_phase](https://github.com/Nezar187/GSG_SmartiecarV2/assets/131591590/256168aa-4b73-4df9-82f2-407d8ddf0279)

## Run phase

In the run phase, the arduino knows the turning direction and so knows the inner wall. 
So we can reduce ultrasonic measurement to just the sensor facing the inner wall, which makes our loop run faster and more reliable.
The curve is detected as early as possible and a turn to a narrow street is detected before the car comes too close to the opposite outer wall.
The arduino tries to steer with a configurable fixed distance to the inner wall, which lets the car run the shortest way possible. 30cm was the most stable in our tests. 
When the distance to the inner wall exceeds 60cm, a curve is detected.
Every curve is counted to go to the end phase after 12 curves.
During start phase and run phase, the LCD background color is set to green while the car is driving along a wall and to blue when a curve is detected. 
It is set back to green, when the inner wall is found again after the curve.
These color changes can be watched easily while the car is driving (better than small text on the LCD screen). 
In case of an error or strange behaviour of the car, this helps us to know immediately, in which part of the program we have to look for the problem.


![Diagram_open_run_phase](https://github.com/Nezar187/GSG_SmartiecarV2/assets/131591590/55016df2-c66b-4c70-bcf0-099ffa39064f)

After 12 curves, the car must find starting area the middle of the street no matter which inner wall setup. 
Our strategy for this is to measure the distance to the opposite outer wall using our front ultrasonic sensor and stop when the distance is below 120cm. 
Unfortunately, when the car points slightly to one side after the last curve, the front sensor gets readings from the side wall rather than the opposite wall and stops early.
To avoid that, we drive slowly after the last curve and adjust the car's orientation with the gyro before starting to measure the front distance.


![Diagram_open_end_phase](https://github.com/Nezar187/GSG_SmartiecarV2/assets/131591590/3bef31ec-63fa-43af-b891-40bf17d13757)


<a name="obstacle-race"></a>

### Obstacle Race

During the obstacle race, the raspberry pi processes camera images in an endless loop. The arduino receives the image processing results via serial interface and steers accordinrly.

## Raspberry Pi software

The purpose of the raspberry pi software is to process camera images and send the results to the arduino.
We decided to use a rather small image resolution of 320x240 pixels. 
These images are big enough for a good pillar detection and can be processed fast enough to use it for driving.
We tried 640x480 first, but image processing was too slow with that resolution.
Additionally, we crop the region of interest = view of the playfield from the image before processing it.
First, this prevents the pillar detector from getting false positives from red or green colors in the environment, second, it further reduces the amount of data to be processed.

The image processing is split into two major parts:
red/green pillar detection and wall collision detection.
The pillar detection function processes the camera image to find the biggest=nearest pillar. It returns 3 values:
- color of the biggest pillar (R=red, G=green, U=unkown, when no pillar is in sight)
- x-coordinate in pixels = left-right position of the pillar's center in the image -> this tells the arduino where to steer
- pillar height in pixels, this tells the arduino the distance of the pillar

The wall collision detector finds out, whether the car would collide with a wall on the left or right when it continues to drive in the current direction.
It returns two values:
- wall_L = Y for wall ahead on left side,  N for no collision danger
- wall_R = Y for wall ahead on right side, N for no collision danger

The main function combines these 5 values to a result string that can be sent to the arduino.
For debugging and testing purposes, the raspberry pi has an RGB LCD, too.
It sets its LCD's background color according to the color of the pillar currently in sight, white for no pillar.
The current result string is displayed too.
However, the raspberry pi image processing is faster than the LCD display, so the result string on the display is only updated ever 200 msec.

To send the result to the arduino, we have developed a request-response protocol. The arduino send the character 'r' to request the most recent result. 
The raspberry pi answers with the latest processing result string. 
First, we just wanted to send the data from the pi to the arduino as fast as possible, but this has a risk of the pi filling up the arduinos serial buffer.
When the arduino then reads the next result, it would be already outdated. So we decided to let the raspberry pi process as fast as it can and just send data the most recent data to the arduino when it needs them.

![Raspberry_Pi_main_run](https://github.com/Nezar187/GSG_SmartiecarV2/assets/131177565/b2b6ec6b-dc3f-4678-a3f4-ea79f93baadb)

------------------------------------------------

- Raspberry Pi Software test

To test the image processing software, we first took and saved a number of testimages on the playfield. 
In the first test versions, we read one of the saved image from a file, processed it and displayed the steps on the screen.
After the software worked from single files, we started using live images from the camera.
The image processor module has its own unit test included. To use it, the background process running the autostarted image processor must be stopped to free the camera.
Then the image processor module can be run interactively in the Thonny IDE and displays intermediate image processing steps to debug problems on the playfield.


- Raspberry pi autostart

When the car is powered up, the image processing software on the raspberry pi must startup automatically. 
We start it as a background process using the operating system method systemd. 
To be able to use our opencv image processing library, the background process must run as the user'pi', not the user 'root', which is the default.
With systemd, it is possible to configure dependencies which must be started first and the user that shall be logged in.
The systemctl tool of the raspberry pi operating system allows us to start and stop the background process manually.

- Raspberry pi error handling

Any outputs or errors are logged in the background processes' logfile and can be accessed with the systemctl tool.
When running tests, we need to notice that the image processor has crashed. To catch any error exception, we use python try-except blocks.
In our error handler, the Raspberry's LCD is switched to red and the text "CRASH" is displayed. 
After that, the error handler raises the exception again that it can be written to the logfile by the operating system. 

- Performance tests

We tested the image processing and communication performance with a test program.
In this test, the arduino reads image processing results from the raspberry pi as fast as possible. It the measures the time for 50 requests.
We achieve a rate of about 25 images/frames per second. Without the arduino communication, the raspberry pi can run at about 35-40 images per second.

## Pillar detection

For the pillar detection, we filter the red and green parts from the image. To do this, we use the opencv image processing library.
We first convert the image to the HSV (Hue,Saturation,Value) color space. This makes it easier to filter for specific colors.
For the filter, we need minimum and maximum vales for the three HSV values for green and for red.
As these min and max values vary for different locations with different lights, we developed a tool (trackbars_....py) to determine these.
The tool has a trackbar for each value. It shows the live camera image and processes a mask, where green/red parts appear white, the rest appears black when the filter values are correct.
The tool can store the adjusted filter values in files (one for green, one for red).

![imgProc settings](https://github.com/Nezar187/GSG_SmartiecarV2/assets/131177565/d656a8d4-e3d8-497e-b361-78ad3aef6fb9)

The live image processor reads these filter values from the files when it starts.
The image processot then filters the image to get a mask for red, where the red pillars appears white and the rest appears black. 
We then use the opencv functions findContours to find the white shape. With the opencv function boundingRect we get the center point, height and width of each white blob in the mask.
We then calculate the biggest one (= biggest height), this is the nearest red pillar.
We repeat the same for green. We then compare the biggest red and biggest green to find the biggest pillar in the image.
Its color, x-coordinate of center point and height are returned. These are the minimum data the arduino needs for steering.

In general, there are two different technics available in opencv to detect a pillar on the mask image. 
One is the opencv simple blob detector, the other is findContours and boundingRect. 
The blob detector has the advantage that it can filter small noise elements in advance by setting a minimum size in pixels. 
The disadvantage is, that it just gives an area size information to determine the height. 
When we tested, we had the problem, that the blob detector sometimes detected part of the orange line as a red pillar.
With the contours method, we can discard blobs where width is bigger than height to avoid this type of problem.


![pillar_detector](https://github.com/Nezar187/GSG_SmartiecarV2/assets/131177565/350c4fe0-f3b5-4a76-b5a1-d5e64a57f9b4)


![Raspberry_Pi_detect_pillars](https://github.com/Nezar187/GSG_SmartiecarV2/assets/131177565/bdcc6720-e357-4e31-b171-1be4dae4c5e4)
---

Wall collision detector
---

When the car evades a pillar which is placed close to a wall, there is a risk of colliding with the wall. 
The problem is, that the car drives toward the wall at an angle, so the ultrasonic reads too big distances.
So we defined two "wall collision zones" in the camera image. 
We crop those areas from the image and process only these to make the detector run faster.
First try: When a wall appears in a collision zone, the wall detector returns a 'Y' for this zone.
The walls are the darkest elements in the image, so to detect these, we convert the zones images to grayscale and did a threshold. 
Problem: This tends to give false positives, when the car just drives along a wall.
There would only be a collision, if the car's path in the image overlaps with the wall.
So we created a triangle mask which gives the projektion of the car's path in the image. The path is white, the rest is black.
We crop the wall collision areas from this mask, too.
We then inverted the wall threshold, so now walls appear white, the rest is black.
When there are areas, that are white in the path image AND in the wall threshold, that is where the car will hit the wall.
So we combine the two images by logical-and to get white areas, where both images have white pixels.
We apply a blur to eliminate noise and reflections.
We then invert the resulting image and use the opencv simple blob detector to find blobs on this image. 
If any, a collision will occur and the detector returns a 'Y' for this area.
We do the same processing for the left wall collision area and the right wall collision area.

![wall collision detector](<src/ino/flow charts/wall_detector.jpg>)

---

Wall collison flow chart
---

![wall collision detector flowchart](<src/ino/flow charts/Raspberry_Pi_detect_wall_collisions.jpg>)

---
## Obstacle Arduino Software

Introduction
---
In the obstacle race, we use the arduino with the sensors attached to it and the raspberry pi.

The obstacle race consists of four phases: init phase, start phase, run phase and end phase.

general obstacle race description
---

Our strategy for the obstacle race is to divide the necessary car movements into functions and then run a sequence of those functions.
On the first level, we have a function to run a curve and a function to run a lane with obstacles.
In the runLane function, the car first drives towards the first obstacle. It approaches the obstacle until it is near enough to evade it.
The car remembers the Straight direction for this lane and steers back to a straight orientation after evading the obstacle. 
It then finds out, whether there is a second obstacle in this lane. If yes, it approaches it and then evades it. If there is no second obstacle,
our car steers to the center of the lane and then goes straight with its gyro until the next curve. 
It then uses its front ultrasonic to know when it has arrived at the curve.
After this, the lane is done.
Then, our car executes a runCurve. The goal of the runCurve function is to steer to the straight orientation of the next lane.
We also try to steer to a position in the center of the curve field. From this position, we can steer to each possible next obstacle behind the curve.
To reach the center position, we have implemented a curve- and a turn- maneuver for each driving direction.
The curve maneuver is chosen when the car starts the curve from very near the outer wall. It changes its LCD color to blue to indicate that.
If there is enough room to the outer wall, the car runs a turn. For the turn, it changes its LCD color to purple.
A turn starts with turning backwards for the first 45 degrees and the turn forward for the second 45 degrees. A curve does it vice-versa.

This strategy enables the car to navigate the track, effectively evading obstacles and maneuvering through curves by leveraging sensor feedback and implementing adaptive maneuvers based on the car's orientation using the gyro and the distances to obstacles and walls.

---

init phase
---
The init phase is very similar to the init phase of the opening race. The difference is, that the arduino requests a first result from the raspberry pi.
From the image processing result, the arduino knows, if there is a pillar in front of it. If yes, it needs to evade this pillar immediately.
As the camera has a wide angle lens, the raspberry pi can also detect pillars right behind the first curve from the start position. 
The pillar's x-position in the image tells the arduino whether the pillar in the image is in front or behind the curve.
When the first pillar is detected behind the curve, the arduino already knows the turning direction.


![Diagram_obstacle_init_phase](https://github.com/Nezar187/GSG_SmartiecarV2/assets/131177565/88528b2c-3c65-4423-a112-af514e76d03b)
---
 
start phase
---
At the beginning the car drives at slow speed. As soon as a pillar is detected in the field of vision, the car checks its position. If the pillar is directly in front of the car, it will be avoided. The car then heads to the opposite wall to determine the exact direction of travel. Depending on whether the pillar was left or right, the car determines its direction of rotation and continues its journey. It then enters the running phase of the race.

![obstacle start phase](<src/ino/flow charts/Diagram_obstacle_start_phase.jpg>)
---

run phase
---
In the run phase, we navigate a lane with obstacles followed by a curve until we've passed 8 corners. Upon reaching the next lane, we conclude the second round and need to determine whether to execute a U-Turn. This decision is facilitated by a specialized version of the 'runLane' function. Afterward, we proceed to the final round.

![obstacle run phase](<src/ino/flow charts/Obstacle Run Phase.jpg>)
---

runlane detailed
---
In the 'runLane' detail, the process begins by driving straight until a pillar is detected. Upon detection, the car approaches and subsequently evades the pillar. The system then assesses whether a second pillar is visible. By evaluating its x-position in the camera image, it determines whether the pillar is positioned within the lane or beyond the upcoming curve. If the pillar is within the lane, the car approaches and evades it. If not, the car continues driving straight until the next curve is detected.

![run lanes](<src/ino/flow charts/runlane.jpg>)
---


Information
---
all of our flow charts can be found by clicking ->
[Flow charts](https://github.com/Nezar187/GSG_SmartiecarV2/tree/50eac4c4b92e603ed27ed5b83ed94a7224463f0e/src/ino/flow%20charts)
---

<a name="programming-languages"></a>




### Programming Languages 👩‍💻

- Python
- C++ (Arduino)
- C


<a name="dependencies"></a>


### Dependencies 📚

C++ (Arduino) Libraries
----

Servo.h

wire.h

rgb_lcd.h

Adafruit_Sensor.h

Adafruit_BNO055.h

utility/imumaths.h

---

Python (Raspberry pi) Libraries:
---
Opencv

pyserial

time

os

sys

grove_rgb_lcd

numpy

datetime

---


<a name="utilities"></a>


## Utilities 🛠


<a name="failsafe"></a>


### Failsafe Mechanisms
We inculded different failsafe mechanisms to avoid mistakes.

Hardware failsafe:

Colorcoding the wires:
We used different colored tape to mmark wires which belong to the same component or mechanism. It reduces the amount of mistakes we make while wiriring the car back up. 
In our first competion one of the wires of our car became unplugged and it took us a while to locate where it had been before. Now we know where the wires belong and where to put them incase of an emergency.

![arduino_wiring](https://github.com/Nezar187/GSG_SmartiecarV2/assets/131177565/df454e80-426f-4515-aae1-7075e8a02669)

Warning light:
On the left side of our car we put the step down converter (5.0V). 
It has a light which turns of automticly and shuts the usb port when it recieves less than 7.5V. When that happens 
the servo won´t work. That is when we know that we have to switch the batteries. Ideally we switch it before that, but this lamp
indicates us when we have to incase we forget to switch it before.


Software failsafe:

Colorcoding the LCD:
Like in our previous car we use LCD screen to give us feedback from our programm. The only difference is that we now use an arduino and a rasperry pi. That is why we use 2 LCD screens istead of one. We differenciate between colorcodes for the opening race and for the obstacle race. 

Opening race (rasperry pi not in use):
- red = starting sequence
- yellow = ready to start -> wating for button (shwoing sensors)
- green = driving
- blue = curve

obstacle race (rasperry pi):
- red = autostart 
- then showing what it sees through the camera
- white = no pillar
- red = red pillar
- green = green pillar

obstacele race (arduino):
- red = starting sequence
- yellow = ready -> waiting for button 
- then showing what pillar color it is working on
- white = no pillar
- red = working on red pillar
- green = working on green pillar
- blue = curve
- purple = turn 




<a name="debugging-tools"></a>


### Debugging Tools 🔍

Debugging tools:
for python = visual studio code
for arduino = arduino IDE


<a name="team-photos"></a>


## Team Photos 📸

Meet the team behind this project in the [Team Photos section](./Teamphotos).


<a name="demonstration-videos"></a>


## Demonstration Videos 🎥

- [Video folder-Races](videos/video.md)




<a name="contributors"></a>


## Contributors 👥

- [Nezar187](https://github.com/Nezar187) [Photo](https://github.com/Nezar187/GSG_SmartiecarV2/assets/131177565/ce8f6c18-1ca7-4d61-b73c-b7d965e4d08b)
- [NoahPX44](https://github.com/NoahPX44) [Photo](https://github.com/Nezar187/GSG_SmartiecarV2/assets/131177565/ecd17aab-c33a-4dee-b5a0-b53c97471a76)
- [LuciusFisch](https://github.com/LuciusFisch) [Photo](https://github.com/Nezar187/GSG_SmartiecarV2/assets/131177565/cce8432b-53e6-4538-ac3e-9ce5f98c23fc)

[Team Photos and Portais](Teamphotos)

<a name="sources"></a>


## Resources
- Help with code Errors [Stackoverflow](https://stackoverflow.com/)
- Ackerman Steering Mechanism [Wikipedia](https://en.wikipedia.org/wiki/Ackermann_steering_geometry)
- [Totemmaker Build Instructions](https://totemmaker.net/wiki/robocar-chassis-building-instruction/)
- [Help with adafruit](https://learn.adafruit.com/)
- [Help with Open CV](https://learnopencv.com/)
- [GitHub CO Pilot](https://github.com/features/copilot)
- 

[Back to top](#top)
