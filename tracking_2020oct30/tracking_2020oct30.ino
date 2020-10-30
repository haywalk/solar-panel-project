/*
 * Sun-following solar panel prototype source code
 * Hayden Walker, 30 October 2020
 */

#include <Servo.h>

Servo myservo; // Create a new servo object
#define servoPin 9 // Define 9 as being the servo pin

void setup() {
  myservo.attach(servoPin); // Attach the servo to pin 9
  int startPosition = 30; // Set the start position
  myservo.write(startPosition); // Start with the servo at the start position
}

void loop() {
  adjust(startPosition); // Start adjusting from the starting position
}

void adjust(int currentAng){
  // Get sensor readings
  int valueRight = analogRead(A0); 
  int valueLeft = analogRead(A1);

  // Check if right has more light
  if ( (valueRight - valueLeft >= 30) and (currentAng > 0) ) {
    currentAng -= 1;
  }
  // Check if left side has more light
  else if ( (valueLeft - valueRight >= 30) and (currentAng < 130) ) {
    currentAng += 1;
  }

  // Move the servo to its new position
  myservo.write(currentAng);

  // Wait 100ms
  delay(100);

  // Recurse and set the new angle as the current one
  adjust(currentAng);
}
