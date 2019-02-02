#include <Servo.h>


Servo myServo;

void setup() { 
 myServo.attach(9);
}


void loop() {
  int sensor = analogRead(A0);
  int angle= map(sensor, 0,1024, 0, 90);
  myServo.write(angle);
  delay(20);
}
