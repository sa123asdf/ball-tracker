# Import necessary packages
from collections import deque
from imutils.video import VideoStream
import numpy as np
import argparse
import cv2
import imutils
import time
import serial

# Serial port settings for Arduino
arduino = serial.Serial('COM3', 9600)  # Set the correct COM port for your Arduino
time.sleep(2)  # Wait for the Arduino to initialize

# Constructing the argument parser for command line arguments
ap = argparse.ArgumentParser()
ap.add_argument("-v", "--video", help="path to the (optional) video file")  # Optional video file path
ap.add_argument("-b", "--buffer", type=int, default=64, help="max buffer size")  # Maximum buffer size for storing ball position history
ap.add_argument("-s", "--skip_frames", type=int, default=2, help="skip every n frames to reduce data rate")  # Skip frames to reduce processing load
args = vars(ap.parse_args())  # Parse the arguments

# Define the HSV color range for detecting the green tennis ball
greenLower = (29, 86, 6)  # Lower bound of green in HSV
greenUpper = (64, 255, 255)  # Upper bound of green in HSV
pts = deque(maxlen=args["buffer"])  # Queue to store the positions of the ball

# If a video path is provided, open the video file, else use the webcam
if not args.get("video", False):
    vs = VideoStream(src=0).start()  # Open webcam (src=0 for default camera)
else:
    vs = cv2.VideoCapture(args["video"])  # Open video file if a path is provided

# Allow the camera or video file to warm up
time.sleep(2.0)

frame_count = 0  # Initialize frame count

# Start a loop to process each frame
while True:
    # Grab the current frame from the video stream or webcam
    frame = vs.read()
    frame = frame[1] if args.get("video", False) else frame  # If video, get the second item (frame), else use the first item

    # If no frame was grabbed, it means the end of the video is reached
    if frame is None:
        break

    # Increment the frame counter
    frame_count += 1

    # Resize, blur the image, and convert it to the HSV color space
    frame = imutils.resize(frame, width=1280)  # Resize frame for faster processing
    blurred = cv2.GaussianBlur(frame, (11, 11), 0)  # Apply Gaussian blur to reduce noise
    hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)  # Convert the frame to HSV color space

    # Create a mask to detect green color (tennis ball), then dilate and erode to remove small blobs
    mask = cv2.inRange(hsv, greenLower, greenUpper)  # Threshold the image for green color
    mask = cv2.erode(mask, None, iterations=2)  # Erode to remove small noise
    mask = cv2.dilate(mask, None, iterations=2)  # Dilate to emphasize the detected ball

    # Find contours in the mask
    cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    cnts = imutils.grab_contours(cnts)  # Extract contours from the mask
    center = None  # Initialize the center of the ball

    # Proceed if at least one contour is found
    if len(cnts) > 0:
        # Find the largest contour, which is assumed to be the tennis ball
        c = max(cnts, key=cv2.contourArea)
        ((x, y), radius) = cv2.minEnclosingCircle(c)  # Get the bounding circle of the contour
        M = cv2.moments(c)  # Calculate moments of the contour

        if M["m00"] != 0:  # Check if the contour has a non-zero area
            center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))  # Calculate the centroid

            # Only proceed if the radius of the ball is large enough
            if radius > 30:
                # Draw the circle and centroid on the frame
                cv2.circle(frame, (int(x), int(y)), int(radius), (0, 255, 255), 2)  # Draw circle
                cv2.circle(frame, center, 5, (0, 0, 255), -1)  # Draw centroid

                # Send the coordinates to Arduino every 'skip_frames' frames
                if frame_count % args["skip_frames"] == 0:
                    arduino.write(f"{int(x)},{int(y)}\n".encode())  # Send the coordinates as a string

    # Update the points queue with the current position of the ball
    pts.appendleft(center)

    # Loop through the list of tracked points and draw lines between them to visualize the movement
    for i in range(1, len(pts)):
        if pts[i - 1] is None or pts[i] is None:
            continue

        # Draw connecting lines between points
        thickness = int(np.sqrt(args["buffer"] / float(i + 1)) * 2.5)  # Vary the thickness of the line
        cv2.line(frame, pts[i - 1], pts[i], (0, 0, 255), thickness)  # Draw the line

    # Display the processed frame
    cv2.imshow("Frame", frame)

    # If the 'q' key is pressed, break out of the loop
    key = cv2.waitKey(1) & 0xFF
    if key == ord("q"):
        break

# Cleanup: stop the video stream, release resources, and close all windows
if not args.get("video", False):
    vs.stop()  # Stop the webcam stream
else:
    vs.release()  # Release the video capture object

# Close all OpenCV windows
cv2.destroyAllWindows()

# Close the Arduino serial connection
arduino.close()
