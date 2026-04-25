#include <AFMotor.h>  
#include <NewPing.h>

#define TRIG_PIN_FRONT A0 // Front center sensor
#define ECHO_PIN_FRONT A1 
#define TRIG_PIN_LEFT A2  // Front left sensor
#define ECHO_PIN_LEFT A3
#define TRIG_PIN_RIGHT A4 // Front right sensor
#define ECHO_PIN_RIGHT A5

#define MAX_DISTANCE 200
#define MAX_SPEED 140

NewPing sonarFront(TRIG_PIN_FRONT, ECHO_PIN_FRONT, MAX_DISTANCE);
NewPing sonarLeft(TRIG_PIN_LEFT, ECHO_PIN_LEFT, MAX_DISTANCE);
NewPing sonarRight(TRIG_PIN_RIGHT, ECHO_PIN_RIGHT, MAX_DISTANCE);

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

boolean goesForward = false;
int distanceFront = 100, distanceLeft = 100, distanceRight = 100;

void setup() {
  Serial.begin(9600);
}

void loop() {
  distanceFront = readPing(sonarFront);
  distanceLeft = readPing(sonarLeft);
  distanceRight = readPing(sonarRight);

  // Debugging sensor values
  Serial.print("Front: ");
  Serial.print(distanceFront);
  Serial.print(" cm, Left: ");
  Serial.print(distanceLeft);
  Serial.print(" cm, Right: ");
  Serial.println(distanceRight);

  // Navigation logic
  if (distanceLeft <= 50 && distanceRight <= 50 && distanceFront <= 50) {
    moveBackward(); // All sensors detect an object, go backward
    delay(2000);    // Reverse for 2 seconds
    moveStop();
  } 
  else if (distanceLeft <= 50 && distanceRight <= 50) {
    moveForward(); // Left and right sensors detect objects, go straight
  } 
  else if (distanceLeft <= 50) {
    turnRight(); // Left sensor detects object, turn right
  } 
  else if (distanceRight <= 50) {
    turnLeft(); // Right sensor detects object, turn left
  } 
  else if (distanceFront <= 50) {
    // If center detects object, choose direction with more space
    if (distanceLeft > distanceRight) {
      turnLeft(); // More space on the left
    } else {
      turnRight(); // More space on the right
    }
  } 
  else {
    moveForward(); // No obstacle, move forward
  }

  delay(100); // Small delay between sensor readings
}

int readPing(NewPing &sonar) {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250; // If no ping detected, assume max distance
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void moveForward() {
  if (!goesForward) {
    goesForward = true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD); 
    motor4.run(FORWARD);     
    for (int speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
      delay(5);
    }
  }
}

void moveBackward() {
  goesForward = false;
  motor1.run(BACKWARD);      
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);  
  for (int speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}  

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);     
  delay(500);
  moveStop();
}

void turnLeft() {
  motor1.run(BACKWARD);     
  motor2.run(BACKWARD);  
  motor3.run(FORWARD);
  motor4.run(FORWARD);   
  delay(500);
  moveStop();
}