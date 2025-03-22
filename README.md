# 🎾 Tennis Ball Tracking with Servo Control 🚀

This project combines Python and Arduino to track a tennis ball in real-time and control a mechanical platform using two servo motors. The Python program detects the tennis ball in a video stream, sends its coordinates to the Arduino, which then adjusts the position of the servos to follow the ball's movement.

## 🎥 Demo Video:
[Watch the demo on YouTube](https://youtu.be/4kyPQEncLbc?si=QymId3UWWP7ilqp2)

---

## 🤖 How It Works:

### 1. **Python Program**:
- Captures video from a webcam or video file.
- Processes each frame and detects the tennis ball by its green color using OpenCV.
- Sends the **X** and **Y** coordinates of the ball's center to the Arduino via serial communication.

### 2. **Arduino Program**:
- Receives the coordinates from the Python program over serial communication.
- Adjusts the servo motors to position the platform and follow the ball's movement.

---

## 📝 Notes:
- **Color Detection**: The default color thresholds are set for a green tennis ball. You may need to adjust the **HSV values** if you're tracking a ball of a different color.
    - **HSV Lower Bound**: (29, 86, 6)
    - **HSV Upper Bound**: (64, 255, 255)
- **COM Port**: Make sure to adjust the **COM port** in the Python code for serial communication with the Arduino (e.g., `'COM3'`).
- **Servo Control**: The servo motors will only move when the ball is detected and tracked.

---

## 🛠️ Project Components:
- **Python**: Used to process the video stream, detect the tennis ball, and send coordinates to the Arduino via serial communication.
- **Arduino**: Controls two servo motors (X and Y axes) based on the coordinates received from the Python program.
- **OpenCV**: Provides image processing and computer vision tools for detecting the ball in the video feed.
- **Servo Motors**: Adjust the platform's position based on the ball's detected position.

---

## 📋 Requirements:

### Hardware:
- **Arduino board** (e.g., Arduino Uno)
- **2 servo motors** (for X and Y axis control)
- **Camera** (webcam or video file input)
- **USB cable** (to connect the Arduino to your computer)

### Software:
- **Python 3.x**
- **OpenCV** (for video processing and object detection)
- **Imutils** (for video manipulation)
- **PySerial** (for serial communication between Python and Arduino)
- **Arduino IDE** (to upload code to the Arduino)

---

## ⚙️ Setup:

1. **Arduino Code**:
   - Upload the provided Arduino code to your Arduino board. The Arduino will control two servo motors based on the X and Y coordinates received from the Python program. The servo motors will adjust the position of a platform (or similar device) to follow the tennis ball.

2. **Python Code**:
   - Install the required Python libraries:
     ```bash
     pip install opencv-python imutils numpy pyserial
     ```
   - Run the Python script to start the tennis ball tracking program. You can either use a webcam or specify a video file for processing:
     ```bash
     python ball_tracking.py --video path_to_video_file
     ```

3. **Wiring**:
   - Connect the servo motors to the appropriate pins on the Arduino board (e.g., pins 9 and 10 for X and Y axes).
   - Connect the Arduino to your computer via USB to establish serial communication.

---

## 🏃 Usage:
1. The Python program processes the video input and detects the tennis ball by color.
2. The coordinates of the detected ball are sent to the Arduino via serial communication.
3. The Arduino adjusts the servo motors to track the ball's movement.

To stop the program, press **'q'** while the video feed is open.

---

## 🖼️ Image Processing Overview:
The image processing pipeline is based on color-based ball detection using OpenCV. The process follows these steps:

1. **Video Input**: The program takes input from a webcam or a video file.
2. **Preprocessing**: The video frame is resized and blurred to reduce noise.
3. **Color Detection**: The frame is converted to the HSV color space, and a binary mask is created based on the predefined green color of the tennis ball.
4. **Noise Removal**: Morphological operations (erosion and dilation) are applied to clean the mask and improve ball detection.
5. **Contour Detection**: The contours of the mask are found, and the largest contour is identified as the tennis ball. The center and radius of the ball are calculated using `cv2.minEnclosingCircle`.
6. **Ball Tracking**: The detected ball's coordinates are sent to the Arduino, which adjusts the servos' positions to track the ball.

---

## ⚠️ Limitations:

1. **Cannot Track Multiple Green Balls**:
   - The current implementation is designed to track only one green ball at a time. If there are multiple green objects in the frame, it may fail to identify which one to track.

2. **Requires Updates for Different Ball Colors**:
   - The script is set up to track a green tennis ball. If you want to track a ball of a different color, you will need to update the color range in the HSV space within the Python script (specifically the `greenLower` and `greenUpper` variables).

3. **No Large Green Objects in the Frame**:
   - If there are other large green objects in the frame (such as plants or clothing), the algorithm may incorrectly detect those as the tennis ball, leading to tracking failures. The background and surrounding objects should not interfere with the detection of the ball.

---

## 📜 License:
This project is licensed under the **MIT License** - see the LICENSE file for details.

---
