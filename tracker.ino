#include <Servo.h>  // Include the Servo library to control servo motors

// Create Servo objects to control the X and Y axes
Servo servoX;  
Servo servoY;

// Define initial positions for the servo motors
int posX = 90; // X-axis initial position (centered at 90 degrees)
int posY = 90; // Y-axis initial position (centered at 90 degrees)

void setup() {
  // Attach the servo motors to the respective pins
  servoX.attach(9);  // Attach the servo motor controlling the X-axis to pin 9
  servoY.attach(10); // Attach the servo motor controlling the Y-axis to pin 10
  
  Serial.begin(9600);  // Start serial communication at 9600 baud rate
  
  // Set initial positions for both servos to center them
  servoX.write(posX);  
  servoY.write(posY);  
}

void loop() {
  // Check if there is data available to read from the serial port
  if (Serial.available() > 0) {
    // Read the incoming data until a newline character is encountered
    String data = Serial.readStringUntil('\n'); 
    
    // Find the index of the comma (separating X and Y values)
    int commaIndex = data.indexOf(','); 
    
    // If a comma is found, proceed to extract X and Y coordinates
    if (commaIndex > 0) {
      // Extract the X value (left part of the data string)
      String xString = data.substring(0, commaIndex); 
      
      // Extract the Y value (right part of the data string)
      String yString = data.substring(commaIndex + 1); 
      
      // Convert the extracted strings to integers
      int x = xString.toInt();
      int y = yString.toInt();

      // Control the X-axis movement based on the received X value
      // Assume 640 is the center point for X-axis (centered at 90 degrees)
      if (x < 580) {
        // If X is smaller than 580, move the servo to the left
        posX = constrain(posX + 1, 0, 180);  // Ensure posX stays within the range 0-180
      } else if (x > 700) {
        // If X is greater than 700, move the servo to the right
        posX = constrain(posX - 1, 0, 180);  // Ensure posX stays within the range 0-180
      }

      // Control the Y-axis movement based on the received Y value
      // Assume 360 is the center point for Y-axis (centered at 90 degrees)
      if (y > 420) {
        // If Y is greater than 420, move the servo downward
        posY = constrain(posY - 1, 0, 180);  // Ensure posY stays within the range 0-180
      } else if (y < 300) {
        // If Y is less than 300, move the servo upward
        posY = constrain(posY + 1, 0, 180);  // Ensure posY stays within the range 0-180
      }

      // Apply the updated positions to the servos
      servoX.write(posX);  // Set the X servo to the new position
      servoY.write(posY);  // Set the Y servo to the new position
    }
  }
}
