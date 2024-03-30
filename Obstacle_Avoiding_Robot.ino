/* 

NaviGuard: Robot Service Car 
Physical Computing Project
 by Kyna Jain 

*/

// Import NewPing library
#include <NewPing.h>
// Import Servo Library
#include <Servo.h>

#define trigPin 12
#define echoPin 13 

// Define a value for the maximum distance the sensor can detect
#define maxDistance 400
// Define a value for the min distance the sensor can detect
#define minDistance 50

int distance = 100; // Create a variable to store the distance value

Servo myservo;  // Create servo object to control a servo
int pos = 90;    // Variable to store the initial servo position (straight ahead)

// L298N Motor Control Pins Configuration
const int M1_LeftFront = 8; // Pin number for the left back wheel control
const int M1_LeftBack = 9; // Pin number for the left back wheel control
const int M2_RightForward = 11; // Pin number for the right back wheel control
const int M2_RightBackward = 10; // Pin number for the right back wheel control
const int M3_LeftFront = 5; // Pin number for the left front wheel control
const int M3_LeftBack = 4; // Pin number for the left front wheel control
const int M4_RightForward = 6; // Pin number for the right front wheel control
const int M4_RightBackward = 7; // Pin number for the right front wheel control

void setup() {
  // Setting up motor control pins as OUTPUT
  pinMode(M1_LeftFront, OUTPUT);
  pinMode(M1_LeftBack, OUTPUT);
  pinMode(M2_RightForward, OUTPUT);
  pinMode(M2_RightBackward, OUTPUT);
  pinMode(M3_LeftFront, OUTPUT);
  pinMode(M3_LeftBack, OUTPUT);
  pinMode(M4_RightForward, OUTPUT);
  pinMode(M4_RightBackward, OUTPUT);

  pinMode(trigPin, OUTPUT); // Configure trigPin to send the trigger signal to the ultrasonic sensor
  pinMode(echoPin, INPUT); // Configure echoPin to receive the echo signal from the ultrasonic sensor

  Serial.begin(9600); // Setting up the serial monitor
  myservo.attach(3);  // Attaching the servo on pin 3 to the servo object

}

void loop() {
  // Capture the distance value from the sensor
  distance = distanceSensed();
  // Print the distance value in the serial monitor
  Serial.println(distance);
  delay(100);
  // Ensure the servo is facing straight ahead (pos = 90)
  myservo.write(pos); 
  delay(100);

  // Turn if the distance sensed is less that 50cm
  if (distance < minDistance) {
    stop();
    // Turn either left, right or move backwards
    turnDirection(); 
  }

  // Move forward while distance is above the stopping distance
  else if (distance >= minDistance) {
    moveForward();
  }

}

// Function to move forward
void moveForward() { 
 digitalWrite(M1_LeftFront, HIGH);
 digitalWrite(M1_LeftBack, LOW);
 digitalWrite(M2_RightForward, HIGH);
 digitalWrite(M2_RightBackward, LOW);
 digitalWrite(M3_LeftFront, HIGH);
 digitalWrite(M3_LeftBack, LOW);
 digitalWrite(M4_RightForward, HIGH);
 digitalWrite(M4_RightBackward, LOW);
 
}

// Function to move backward
void moveBackward() { 
 digitalWrite(M1_LeftFront, LOW);
 digitalWrite(M1_LeftBack, HIGH);
 digitalWrite(M2_RightForward, LOW);
 digitalWrite(M2_RightBackward, HIGH);
 digitalWrite(M3_LeftFront, LOW);
 digitalWrite(M3_LeftBack, HIGH);
 digitalWrite(M4_RightForward, LOW);
 digitalWrite(M4_RightBackward, HIGH);
 
}

// Function to stop
void stop() { 
 digitalWrite(M1_LeftFront, LOW);
 digitalWrite(M1_LeftBack, LOW);
 digitalWrite(M2_RightForward, LOW);
 digitalWrite(M2_RightBackward, LOW);
 digitalWrite(M3_LeftFront, LOW);
 digitalWrite(M3_LeftBack, LOW);
 digitalWrite(M4_RightForward, LOW);
 digitalWrite(M4_RightBackward, LOW);
 
}

// Function to turn right
void moveRight() { 
 digitalWrite(M1_LeftFront, HIGH);
 digitalWrite(M1_LeftBack, HIGH);
 digitalWrite(M2_RightForward, LOW);
 digitalWrite(M2_RightBackward, LOW);
 digitalWrite(M3_LeftFront, HIGH);
 digitalWrite(M3_LeftBack, HIGH);
 digitalWrite(M4_RightForward, LOW);
 digitalWrite(M4_RightBackward, LOW);
}

// Function to turn left
void moveLeft() { 
 digitalWrite(M1_LeftFront, LOW);
 digitalWrite(M1_LeftBack, LOW);
 digitalWrite(M2_RightForward, HIGH);
 digitalWrite(M2_RightBackward, HIGH);
 digitalWrite(M3_LeftFront, LOW);
 digitalWrite(M3_LeftBack, LOW);
 digitalWrite(M4_RightForward, HIGH);
 digitalWrite(M4_RightBackward, HIGH);
}

/* Logic to calculate distance referenced from given link: 
https://www.instructables.com/Controlling-a-Servo-With-an-Ultrasonic-Sensor-Usin/*/

int distanceSensed(){
  // Measure distance sensed in cm
  long duration, distance;
  // Set the trigger pin to low to ensure a clean pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Send a 10 microsecond high pulse to the trigger pin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  // Set the trigger pin back to low
  digitalWrite(trigPin, LOW);
  // Measure the duration of the pulse received on the echo pin
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance in cm using the duration and speed of sound
  distance = (duration/2) / 29.1; 
  // Return the distance value in cm
  return distance; 
}

void turnDirection() {
  // Check right
  myservo.write(0); // Set the angle to move the servo to the right
  delay(1000); // Delay to hold the position
  int distanceRight = distanceSensed();

  // Check left
  myservo.write(180); // Set the angle to move the servo to the left
  delay(1000);
  int distanceLeft = distanceSensed();

  // If both sides are blocked, move backward
  if (distanceRight <= minDistance && distanceLeft <= minDistance) { 
    moveBackward();
  }

  // If both distances are within the acceptable range, move right
  else if (distanceRight > minDistance && distanceRight <= maxDistance && distanceLeft > minDistance && distanceLeft <= maxDistance) { 
    moveRight();
  }

  // If the right side has more space than the left, move right
  else if (distanceRight > distanceLeft) { 
    moveRight();
  }

  // If the left side has more space than the right, move left
  else if (distanceRight < distanceLeft) { 
    moveLeft();
  }

}



