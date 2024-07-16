# Opening Race

## Table of Contents

1. [Program Overview](#program-overview)
2. [Installation & Setup](#installation--setup)
3. [Features](#features)
4. [Core Logic](#core-logic)
5. [Functions Breakdown](#functions-breakdown)
6. [Libraries and Dependencies](#libraries-and-dependencies)
7. [Detailed Variables](#detailed-variables)
8. [Additional Elements](#additional-elements)

---

### Program Overview

This Arduino script is a sophisticated control system designed to manipulate a servo motor's speed and position while providing real-time feedback through an RGB LCD screen. This multi-functional script is ideal for interactive setups requiring both motor control and visual feedback.

---

### Installation & Setup

**Hardware Requirements:**

- Arduino Board
- Servo Motor
- RGB LCD Display
- Push Button

**Software Requirements:**

- Arduino IDE with the following libraries installed:
  - `Servo`
  - `Wire`
  - Custom `rgb_lcd` library
  - Our Custom libararies

---

### Features

- **Dynamic Speed Control**: Multiple speed settings to adapt to different operational conditions.
- **User Interaction**: Button-based interface for triggering specific actions.
- **Visual Feedback**: Real-time updates displayed on an RGB LCD screen.

---

### Core Logic

The `loop()` function serves as the backbone of the application, orchestrating:

1. **Servo Control**: Utilizes a series of speed variables to manage the servo motor's position and speed.
2. **Button Monitoring**: Listens for button presses to activate certain features or settings.
3. **LCD Updates**: Manipulates the RGB LCD display to reflect the system's current state.

---

### Functions Breakdown

#### `void setup()`

- **Purpose**: Initialization of hardware components.
- **Operations**:
  - Configures the servo motor to its initial position.
  - Initializes the RGB LCD with a specific backlight color.
  - Sets up the button input on a specific Arduino pin.

#### `void loop()`

- **Purpose**: Main execution body for continuous operations.
- **Operations**:
  - Adjusts the servo motor's position and speed based on conditions.
  - Monitors button state for input.
  - Updates the RGB LCD display based on system state.

---

### Libraries and Dependencies

- **`#include <Servo.h>`**: Essential for controlling the servo motor's parameters such as position and speed.
- **`#include <Wire.h>`**: Enables I2C communication, specifically between the Arduino and the RGB LCD screen.
- **`#include "rgb_lcd.h"`**: Custom library tailored for the RGB LCD display, used for setting text and backlight color.

---

### Detailed Variables

- **Speed Control Variables**:
  - `NormalSpeed`: Default speed for the servo motor during regular operations.
  - `SlowSpeed`: Reduced speed under specific conditions.
  - `CurveSpeed`: Adapted speed when the motor needs to navigate curves.
  - `StartSpeed`: Speed setting when the system is first initiated.
  
- **User Input Variables**:
  - `Button`: Designates which pin on the Arduino board will be used for button input.
  
- **RGB Color Variables**:
  - `colorRed`, `colorGreen`, `colorBlue`: Determine the RGB values for the LCD display's backlight.

---

### Additional Elements

- **ASCII Art**: Incorporated within the code to improve readability and aesthetics.

---


# Obstacle Race

## Table of Contents

1. [Program Overview](#program-overview)
2. [Installation & Setup](#installation--setup)
3. [Features](#features)
4. [Core Logic](#core-logic)
5. [Functions Breakdown](#functions-breakdown)
6. [Libraries and Dependencies](#libraries-and-dependencies)
7. [Detailed Variables](#detailed-variables)
8. [Additional Elements](#additional-elements)

---

### Program Overview

This Arduino script, named `main_obstacles.ino`, is designed to manage a servo motor and provide real-time feedback via an RGB LCD screen. The program has added complexity as it appears to deal with obstacle detection and navigation, making it ideal for robotic applications.

---

### Installation & Setup

**Hardware Requirements:**

- Arduino Board
- Servo Motor
- RGB LCD Display
- Push Button
- Distance Sensors

**Software Requirements:**

- Arduino IDE with the following libraries installed:
  - `Servo`
  - `Wire`
  - Custom `rgb_lcd` library

---

### Features

- **Dynamic Speed and Positioning**: Control of servo motor based on sensor inputs.
- **User Interaction**: Button-based interface for specific controls.
- **Visual Feedback**: Real-time updates displayed on an RGB LCD screen.
- **Obstacle Detection**: Appears to handle distance sensors for obstacle navigation.

---

### Core Logic

The `loop()` function orchestrates the following key functionalities:

1. **Servo Control**: Utilizes speed and positioning variables to manage the servo motor dynamically.
2. **Button Monitoring**: Checks for button presses to activate or deactivate certain features.
3. **LCD Updates**: Keeps the RGB LCD display updated with the real-time statuses.
4. **Distance Monitoring**: Likely uses distance sensors to navigate obstacles.

---

### Functions Breakdown

#### `void setup()`

- **Purpose**: To initialize the hardware components.
- **Operations**:
  - Sets up the distance sensors.
  - Initializes the servo motor to its starting position.
  - Configures the RGB LCD display.

#### `void loop()`

- **Purpose**: Main operational loop.
- **Operations**:
  - Monitors distance sensors for obstacles.
  - Controls the servo motor's speed and positioning.
  - Checks for button inputs.
  - Updates the RGB LCD display.

---

### Libraries and Dependencies

- **`#include <Servo.h>`**: Essential for servo motor operations.
- **`#include <Wire.h>`**: Enables I2C communication, likely for the RGB LCD screen.
- **`#include "rgb_lcd.h"`**: Custom library for controlling the RGB LCD screen.

---

### Detailed Variables

- **User Input**: 
  - `Button`: Pin number on the Arduino board for the button input.
  
- **Display Colors**: 
  - `colorRed`, `colorGreen`, `colorBlue`: RGB values for the LCD backlight.
  
- **Sensor Data**:
  - `Distance_Front`, `Distance_Left`, `Distance_Right`: Likely hold sensor readings for obstacle detection.

- **Control Variables**:
  - `angle`, `danger`, `correction`: Appear to be used for servo control and navigation.

---

### Additional Elements

- **ASCII Art**: Used for enhancing code readability.

---