#include <Servo.h>

//Set up the servos
Servo servo1;



//CLIMATE CONTROL SWITCHES

//FAN
int fanSpeed = 0;  //initial fan state

int fan1 = A1;
int fan2 = A2;
int fan3 = A3;
int fan4 = A4;
int fanCommon = A5;

//HEATING
int heatValve = 5; // servo control pin


//CIRCULATION
int faceSwitch = 6;
int faceFeetSwitch = 7;
int feetSwitch = 8;
int feetWindowsSwitch = 9;
int windowsSwitch = 10;

//AIRF0
int airInside = 11; //control inside airf0 or outside
int airOutside = 12;

//AC
int acSwitch = 13;

int sValue = 0; //this variable holds what we are currently reading from serial


void setup() { //call this once at the beginning
  pinMode(fan1, OUTPUT);
  pinMode(fan2, OUTPUT);
  pinMode(fan3, OUTPUT);
  pinMode(fan4, OUTPUT);

  pinMode(heatValve, OUTPUT);

  //climate setup
  pinMode(faceSwitch, OUTPUT);
  pinMode(feetSwitch, OUTPUT);
  pinMode(windowsSwitch, OUTPUT);

  //AC
  pinMode(acSwitch, OUTPUT);
  //airf0
  pinMode(airInside, OUTPUT);
  pinMode(airOutside, OUTPUT);

  servo1.attach(heatValve); //initialize servo
  Serial.begin(9600); //start up serial port

  //all these are off
  analogWrite(acSwitch, 255);
  analogWrite(airInside, 255);
  //air circulates from outside by default
  analogWrite(airOutside, 0);

  //turn all these off
  analogWrite(feetSwitch, 255);
  analogWrite(feetWindowsSwitch, 255);
  analogWrite(faceFeetSwitch, 255);
  analogWrite(windowsSwitch, 255);

  //turn this on
  analogWrite(faceSwitch, 0);

  //fan is off
  analogWrite(fan1, 255);
  analogWrite(fan2, 255);
  analogWrite(fan3, 255);
  analogWrite(fan4, 255);
  analogWrite(fanCommon, 255);
}
void loop() { //main loop
  if (Serial.available() > 0) { //if there is anything on the serial port, read it
    sValue = Serial.parseInt(); //store it in the sValue variable

  }



  if (sValue > 0) { //if we read something

    //Reset and stop servo
    if (sValue == 1 || sValue == 10) {
      servo1.write(10);//if we read a 1, stop
    }

    //MASTER SHUTDOWN - kill all services
    if (sValue == 999) {
      servo1.write(10);

      analogWrite(feetSwitch, 255);
      analogWrite(faceFeetSwitch, 255);
      analogWrite(feetSwitch, 255);
      analogWrite(feetWindowsSwitch, 255);
      analogWrite(windowsSwitch, 255);
      analogWrite(faceSwitch, 255);
      analogWrite(airInside, 255);
      analogWrite(airOutside, 255);
      analogWrite(acSwitch, 255);

      analogWrite(fan1, 255);
      analogWrite(fan2, 255);
      analogWrite(fan3, 255);
      analogWrite(fan4, 255);
      analogWrite(fanCommon, 255);

    }

    //SERVO CONTROL

    //range between 10-90 angle
    else if (sValue > 0 && sValue <= 90) {
      int angle = map(sValue, 0, 90, 0, 90);
      servo1.write(angle);
      delay(15); //wait
    }


    //FAN CONTROL
    if (sValue >= 300 && sValue <= 400) {

      switch (sValue) {
        case 300:
          analogWrite(acSwitch, 255); //shutoff AC if fan is off
          analogWrite(fan1, 255);
          analogWrite(fan2, 255);
          analogWrite(fan3, 255);
          analogWrite(fan4, 255);
          analogWrite(fanCommon, 255);
          break;

        case 325: //fan1
          analogWrite(fan2, 255);
          analogWrite(fan3, 255);
          analogWrite(fan4, 255);

          analogWrite(fanCommon, 0);
          analogWrite(fan1, 0);
          break;
        case 350: //fan2

          analogWrite(fan1, 255);
          analogWrite(fan3, 255);
          analogWrite(fan4, 255);

          analogWrite(fanCommon, 0);
          analogWrite(fan2, 0);

          break;
        case 375: //fan3
          analogWrite(fan1, 255);
          analogWrite(fan2, 255);
          analogWrite(fan4, 255);

          analogWrite(fanCommon, 0);
          analogWrite(fan3, 0);
          break;
        case 400: //fan4
          analogWrite(fan1, 255);
          analogWrite(fan2, 255);
          analogWrite(fan3, 255);

          analogWrite(fanCommon, 0);
          analogWrite(fan4, 0);
          break;
      }
      delay(500);
    }
    //set fan speed



    //SWITCHES CONTROL

    //s1 on/off 190/191
    //s2 on/off 192/193
    if (sValue >= 190 && sValue <= 195) { //stay out of servo range

      switch (sValue) {
        case 190: //face
          analogWrite(feetSwitch, 255);
          analogWrite(windowsSwitch, 255);
          analogWrite(faceFeetSwitch, 255);
          analogWrite(feetWindowsSwitch, 255);

          analogWrite(faceSwitch, 0);
          break;

        case 191: //face and feet
          analogWrite(feetSwitch, 255);
          analogWrite(windowsSwitch, 255);
          analogWrite(feetWindowsSwitch, 255);
          analogWrite(faceSwitch, 255);

          analogWrite(faceFeetSwitch, 0);
          break;

        case 192://feet
          analogWrite(windowsSwitch, 255);
          analogWrite(feetWindowsSwitch, 255);
          analogWrite(faceSwitch, 255);
          analogWrite(faceFeetSwitch, 255);

          analogWrite(feetSwitch, 0);
          break;

        case 193://feet and windows
          analogWrite(windowsSwitch, 255);
          analogWrite(faceSwitch, 255);
          analogWrite(feetSwitch, 255);
          analogWrite(faceFeetSwitch, 255);

          analogWrite(feetWindowsSwitch, 0);
          break;

        case 194://windows
          analogWrite(feetWindowsSwitch, 255);
          analogWrite(faceSwitch, 255);
          analogWrite(feetSwitch, 255);
          analogWrite(faceFeetSwitch, 255);


          analogWrite(windowsSwitch, 0);
          break;

        default: //some number like 181
          //all off
          analogWrite(feetWindowsSwitch, 255);
          analogWrite(faceSwitch, 255);
          analogWrite(feetSwitch, 255);
          analogWrite(faceFeetSwitch, 255);
          analogWrite(windowsSwitch, 255);
          break;
      }
    }

    //AIRF0 (inside - default)
    if (sValue == 196) {
      analogWrite(airInside, 0);
      analogWrite(airOutside, 255);
    }

    //AIRF0 (from outside)
    if (sValue == 197) {
      analogWrite(airOutside, 0);
      analogWrite(airInside, 255);
    }

    //AC ON
    if (sValue == 198) {
      analogWrite(acSwitch, 0);
    }

    //AC OFF
    if (sValue == 199) {
      analogWrite(acSwitch, 255);
    }

  }
  sValue = 0; //reset
}














