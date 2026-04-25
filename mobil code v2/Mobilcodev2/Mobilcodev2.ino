#include <AFMotor.h>  


#define MAX_SPEED 200
#define HALF_SPEED 100

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

boolean goesForward = false;


void setup() {
  Serial.begin(9600);
}

void loop() {
moveForward();
delay(1000);
moveStop();

}


void moveStop() {
  Serial.println("Stopping motors.");
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  goesForward = false;
}

void moveForward() {
  if (!goesForward) {
    Serial.println("Moving forward.");
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
  Serial.println("Moving backward.");
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
  Serial.println("Turning right.");
  motor1.setSpeed(120);      
  motor2.setSpeed(40);
  motor3.setSpeed(35);      
  motor4.setSpeed(120);
  motor1.run(FORWARD); 
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(1000);
  setMaxSpeed();
}

void turnLeft() {
  Serial.println("Turning left.");
  motor1.setSpeed(HALF_SPEED);      
  motor2.setSpeed(MAX_SPEED);
  motor3.setSpeed(MAX_SPEED);      
  motor4.setSpeed(HALF_SPEED);
  motor1.run(FORWARD); 
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(1000);
  setMaxSpeed();
}

void setMaxSpeed() {
  motor1.setSpeed(MAX_SPEED);
  motor2.setSpeed(MAX_SPEED);
  motor3.setSpeed(MAX_SPEED);
  motor4.setSpeed(MAX_SPEED);
  Serial.println("Setting all motors to maximum speed.");
}
