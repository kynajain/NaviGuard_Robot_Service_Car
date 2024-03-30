/* 

Motor Shield Version (L293D Motor Shield) of NaviGuard: Robot Service Car 
Physical Computing Project
 by Kyna Jain 


*/

// Importing NewPing library
#include <NewPing.h>
//Importing the Adafruit Motor Shield Library
#include <AFMotor.h>
// Importing the Servo Library
#include <Servo.h>

// Defining the ultrasonic sensor pins
#define trigPin 2
#define echoPin 13

#define speed 127 // Defining the motors' speed

// A value for the maximum distance the sensor can detect (in cm)
#define maxDistance 400
#define minDistance 50

// Creating a sonar object to use the NewPing library
NewPing sonar(trigPin, echoPin, maxDistance);

// Instantiating objects of the AF_DCMotor class
AF_DCMotor M1_LeftFront(1); // Defining motor on channel 1, with 1KHz default PWM
AF_DCMotor M2_LeftBack(2); // Defining motor on channel 2, with 1KHz default PWM
AF_DCMotor M3_RightFront(3); // Defining motor on channel 3, with 1KHz default PWM
AF_DCMotor M4_RightBack(4); // Defining motor on channel 4, with 1KHz default PWM

Servo myservo;  // Create servo object to control a servo
int pos = 90;    // Variable to store the initial servo position (straight ahead)

void setup() {
  Serial.begin( 9600 ); // setting up the serial monitor
  Serial.println("Attaching Servo");
  myservo.attach(10);  // Attaches the servo on pin 9 to the servo object

 // Setting the speed of the motors'
 M1_LeftFront.setSpeed(speed);
 M2_LeftBack.setSpeed(speed);
 M3_RightFront.setSpeed(speed);
 M4_RightBack.setSpeed(speed);

 // Making sure all motors are halted initially
 M1_LeftFront.run(RELEASE);
 M2_LeftBack.run(RELEASE);
 M3_RightFront.run(RELEASE);
 M4_RightBack.run(RELEASE);

}

void loop() {
  // Measure distance sensed in cm
  int distanceSensed = sonar.ping_cm();

  // Use the sonar.ping_cm() to return the distance sensed in cms, print in serial monitor
  Serial.println(distanceSensed);
  myservo.write(pos); // Ensuring the servo is facing straight ahead
  delay(100);

  // Turn if the distance sensed is less that 50cm
  if (distanceSensed < minDistance) {
//    moveStop();
    turnDirection();
  }

  // Move forward while distance is above the stopping distance
  else if (distanceSensed >= minDistance) {
 //   moveForward();
  }

}

void moveForward() { // Function to move forward
 M1_LeftFront.run(FORWARD);
 M2_LeftBack.run(FORWARD);
 M3_RightFront.run(FORWARD);
 M4_RightBack.run(FORWARD);
}

void moveBackward() { // Function to move backward
 M1_LeftFront.run(BACKWARD);
 M2_LeftBack.run(BACKWARD);
 M3_RightFront.run(BACKWARD);
 M4_RightBack.run(BACKWARD);
}

void moveStop() { // Function to stop
 M1_LeftFront.run(RELEASE);
 M2_LeftBack.run(RELEASE);
 M3_RightFront.run(RELEASE);
 M4_RightBack.run(RELEASE);
}

void moveRight() { // Function to turn right
 M1_LeftFront.run(FORWARD);
 M2_LeftBack.run(FORWARD);
 M3_RightFront.run(BACKWARD);
 M4_RightBack.run(BACKWARD);
}

void moveLeft() { // Function to turn left
 M1_LeftFront.run(BACKWARD);
 M2_LeftBack.run(BACKWARD);
 M3_RightFront.run(FORWARD);
 M4_RightBack.run(FORWARD);
}

void turnDirection() {
  // Check right
  myservo.write(0); // Set the angle to move the servo to the right
  delay(1000); // Delay to hold the position
  int distanceRight = sonar.ping_cm();

  // Check left
  myservo.write(180); // Set the angle to move the servo to the left
  delay(1000);
  int distanceLeft = sonar.ping_cm();

  if (distanceRight <= minDistance && distanceLeft <= minDistance) { // If both sides are blocked, move back
    moveBackward();
  }
  else if (distanceRight > minDistance && distanceRight <= maxDistance && distanceLeft > minDistance && distanceLeft <= maxDistance) { // If both distances are equal, then move right
    moveRight();
  }
  else if (distanceRight > distanceLeft) { // If right has more space than left, move right
    moveRight();
  }
  else if (distanceRight < distanceLeft) { // If left has more space than right, move left
    moveLeft();
  }

}
