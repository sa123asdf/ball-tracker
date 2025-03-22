#include <Servo.h>  // Include the Servo library to control the servo motor

Servo myservo;  // Create a Servo object to control a single servo motor

int pos = 0;    // Define the initial position of the servo motor (0 degrees)

void setup() {
  // Attach the servo motor to a specific pin (pin 9 in this case)
  myservo.attach(9);  // The signal pin of the servo motor is connected to Arduino's D9 pin
}

void loop() {
  // Move the servo from 0 degrees to 180 degrees
  for (pos = 0; pos <= 180; pos += 1) {  // Increment position from 0 to 180 degrees
    myservo.write(pos);  // Command the servo to move to the current position
    delay(15);  // Delay for 15 milliseconds to allow smooth movement
  }

  // Move the servo from 180 degrees back to 0 degrees
  for (pos = 180; pos >= 0; pos -= 1) {  // Decrement position from 180 to 0 degrees
    myservo.write(pos);  // Command the servo to move to the current position
    delay(15);  // Delay for 15 milliseconds to allow smooth movement
  }
}
