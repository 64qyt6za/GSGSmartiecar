## Code Description Raspberry Pi


## Program Description

The Program captures video from a camera using OpenCV and performs color filtering to identify specific colors of interest in real-time. The program allows the user to set the parameters for the color filtering using trackbars and saves these parameters for future use.

### Color Filtering

The program supports color filtering for two colors: green and red. It creates trackbars that allow adjustment of the hue, saturation, and value (HSV) ranges for each color. The user can control the minimum and maximum values for hue, saturation, and value using the trackbars. By adjusting these trackbars, the user can set the desired color ranges for green and red.

### Video Capture

The program initializes the video capture using the default camera connected to the system. It searches for an available camera by iterating over a range of indices. Once a camera is found, the program prints a message indicating the index of the camera. If no camera is found, the program exits.

### Live Streaming

The program continuously captures frames from the camera and converts them from the default BGR color space to HSV color space using the `cv2.cvtColor


### Program structure
---
### Imports

The necessary libraries, OpenCV (`cv2`) and numPy (`numpy`), are imported at the beginning of the code.

### Video Resolution

The code sets the desired video resolution (`frameWidth` and `frameHeight`) in pixels.

### Empty Function

An empty function named `empty` is defined, which is used as a placeholder function for the trackbar creation.

### Loading Parameters from File

A function named `load_params_from_file` is defined to load trackbar positions from a file. This function takes a `filename`, `trackbar_name`, `window_name`, `index`, and `default_value`. It attempts to read the parameters from the file, splitting the lines using a delimiter (`=`) and converting the value to an integer. If the file is not found or the index is out of range, it sets the value to the provided `default_value`. The function then creates a trackbar using `cv2.createTrackbar()` and sets its position to the loaded value. Finally, it returns the loaded value.

### Trackbars and Windows Initialization

Trackbars and windows are created for two colors: green and red (`'G_HSV'` and `'R_HSV'`). For each color, trackbars are created using `cv2.createTrackbar()` for various parameters such as hue, saturation, and value. The created windows for these colors are resized using `cv2.resizeWindow()`.

### File Paths and Parameters Initialization

Temporary file paths (`file_path1` and `file_path2`) are defined. The file paths point to two text files (`'G_params.txt'` and `'R_params.txt'`) that store the trackbar positions of the green and red colors, respectively.

### Reading Trackbar Positions from Files

The code opens the text files (`'G_params.txt'` and `'R_params.txt'`) and calls the `load_params_from_file` function to read the trackbar positions for each color. The function is called with the corresponding trackbar names, window names, indices, and default values. These values represent the minimum and maximum hue, saturation, and value ranges for each color.

### Video Capture Initialization

The code initializes the video capture using `cv2.VideoCapture()`. It iterates over a range of 10 indices to find a camera that is accessible. If a camera is found, the loop breaks, and the message "Camera found at index {index}" is printed. If no camera is found, the message "No camera found." is printed, and the program is exited. The width and height of the video capture are set using `cap.set()` to match the desired resolution.

### Main Loop

The main loop captures frames from the video using `cap.read()`. The captured frame is converted from BGR to HSV color space using `cv2.cvtColor()`. The trackbar positions for the green color are retrieved using `cv2.getTrackbarPos()`. The lower and upper ranges for the green and red colors are created using `np.array()` based on the trackbar positions obtained.

### Applying Masks and Displaying Live Streams

The masks for the green and red colors are created using `cv2.inRange()` by applying the lower and upper ranges to the HSV image. The masks are displayed using `cv2.imshow()` on separate windows.

### Exiting the Program

The loop continues until the 'x' key is pressed. When the loop is exited, the trackbar positions for the green and red colors are saved to the corresponding text files. The parameters are concatenated into strings, and the files are written using `open()` in write mode. Finally, the video capture is released and the windows are closed using `cap.release()` and `cv2.destroyAllWindows()` respectively.