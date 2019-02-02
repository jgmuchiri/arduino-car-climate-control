#include <Servo.h> 
 
Servo servoMotor;       // creates an instance of the servo object to control a servo
int servoPin = 3;       // Control pin for servo motor
 
void setup() {
  Serial.begin(9600);       // initialize serial communications
  servoMotor.attach(servoPin);  // attaches the servo on pin 2 to the servo object
} 
 
void loop()
{
  int analogValue = analogRead(A0); // read the analog input
  Serial.println(analogValue);      // print it
 
  // if your sensor's range is less than 0 to 1023, you'll need to
  // modify the map() function to use the values you discovered:
  int servoAngle = map(analogValue, 0, 1023, 0, 179);
 
  // move the servo using the angle from the sensor:
  servoMotor.write(servoAngle);
  //delay(20);
}
