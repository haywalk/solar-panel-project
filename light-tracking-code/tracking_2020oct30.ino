/*
 * Sun-following solar panel prototype source code
 * Hayden Walker, 30 October 2020
 */

#include <Servo.h> // Include the Arduino servo library

Servo myservo; // Create a new servo object

/*
 * Define constants
 */
#define servoPin 9 // Define 9 as being the servo pin
#define startPosition 30 // Set the start position
#define maxPosition 110 // Set maximum angle
#define margin 30 // Set sensitivity


void setup() {
  myservo.attach(servoPin); // Attach the servo to pin 9
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
  if ( (valueRight - valueLeft >= margin) and (currentAng > startPosition) ) {
    currentAng -= 1; // Move right
  }
  // Check if left side has more light
  else if ( (valueLeft - valueRight >= margin) and (currentAng < maxPosition) ) {
    currentAng += 1; // Move left
  }

  myservo.write(currentAng); // Move the servo to its new position
  delay(100); // Wait 100ms

  // Recurse and make the new angle the current one
  adjust(currentAng);
}
