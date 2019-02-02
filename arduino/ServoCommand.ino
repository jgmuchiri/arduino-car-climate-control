#include <Servo.h>

//Set up the servos
Servo servo1;


//CLIMATE CONTROL SWITCHES
int faceSwitch = 2;
int feetSwitch = 3;
int windowsSwitch = 4; //head level heating

//AC
int acSwitch = 5;

//AIRWFLOW
int airFlow = 6; //control inside airflow or outside

int debugPin = 7; // used for an led to test stuff
int heatValve = 9; // the first motor's port number
int usbnumber = 0; //this variable holds what we are currently reading from serial

//FAN
int fanPin = 10;

void setup() { //call this once at the beginning
  pinMode(heatValve, OUTPUT);
  pinMode(debugPin, OUTPUT);

  //climate setup
  pinMode(faceSwitch, OUTPUT);
  pinMode(feetSwitch, OUTPUT);
  pinMode(windowsSwitch, OUTPUT);

  //AC
  pinMode(acSwitch, OUTPUT);
  //airflow
  pinMode(airFlow, OUTPUT);
  //fan
  pinMode(fanPin, OUTPUT);

  servo1.attach(heatValve); //initialize servo
  Serial.begin(9600); //start up serial port
  
  analogWrite(fanPin,255); //initialize fan in off state
}

void loop() { //main loop
  if (Serial.available() > 0) { //if there is anything on the serial port, read it
    usbnumber = Serial.parseInt(); //store it in the usbnumber variable

  }


  if (usbnumber > 0) { //if we read something

    //Reset and stop servo
    if (usbnumber == 1 || usbnumber == 10) {
      servo1.write(10);//if we read a 1, stop
      analogWrite(debugPin, 0);
    }
    //MASTER SHUTDOWN - kill all services
    if (usbnumber == 999) {
      servo1.write(10);
      analogWrite(debugPin, 0);
      analogWrite(feetSwitch, 0);
      analogWrite(windowsSwitch, 0);
      analogWrite(faceSwitch, 0);
      analogWrite(airFlow, 0);
      analogWrite(acSwitch, 0);
      analogWrite(fanPin, 255);

    }

    //SERVO CONTROL

    //range between 10-90 angle
    else if (usbnumber > 0 && usbnumber <= 90) {
      
      int angle = map(usbnumber, 0, 1024, 0, 90);
      servo1.write(usbnumber);
      analogWrite(debugPin, 255);
      
      delay(500); //wait
    }
   

    //FAN CONTROL
    int fanSpeed = 0;
    //initial fan state
    
    
    if (usbnumber >= 300 && usbnumber <= 400) {
     
      switch (usbnumber) {
        case 300:
          analogWrite(fanPin,255);
          break;
        case 325:
          analogWrite(fanPin,0);
          break;
        case 350:
          analogWrite(fanPin,0);
          break;
        case 375:
          analogWrite(fanPin,0);
          break;
        case 400:
          analogWrite(fanPin,0);
          break;
        default:
          analogWrite(fanPin,255);
          break;
      }
       delay(500);
    }
    //set fan speed



    //SWITCHES CONTROL

    //s1 on/off 190/191
    //s2 on/off 192/193
    if (usbnumber > 180) { //stay out of servo range

      switch (usbnumber) {
        case 190: //face
          analogWrite(feetSwitch, 0);
          analogWrite(windowsSwitch, 0);
          analogWrite(faceSwitch, 255);
          break;

        case 191: //face and feet
          analogWrite(windowsSwitch, 0);
          analogWrite(faceSwitch, 255);
          analogWrite(feetSwitch, 255);
          break;

        case 192://feet
          analogWrite(windowsSwitch, 0);
          analogWrite(faceSwitch, 0);
          analogWrite(feetSwitch, 255);
          break;

        case 193://feet and windows
          analogWrite(faceSwitch, 0);
          analogWrite(feetSwitch, 255);
          analogWrite(windowsSwitch, 255);
          break;

        case 194://windows
          analogWrite(faceSwitch, 0);
          analogWrite(feetSwitch, 0);
          analogWrite(windowsSwitch, 255);
          break;

        default: //some number like 181
          //all off
          analogWrite(faceSwitch, 0);
          analogWrite(feetSwitch, 0);
          analogWrite(windowsSwitch, 0);
          break;
      }
    }

    //AIRFLOW (inside - default)
    if (usbnumber == 196) {
      analogWrite(airFlow, 255);
    }

    //AIRFLOW (from outside)
    if (usbnumber == 197) {
      analogWrite(airFlow, 0);
    }

    //AC ON
    if (usbnumber == 198) {
      analogWrite(acSwitch, 255);
    }

    //AC OFF
    if (usbnumber == 199) {
      analogWrite(acSwitch, 0);
    }

  }
  usbnumber = 0; //reset
}














