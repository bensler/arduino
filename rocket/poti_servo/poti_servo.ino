#include <Servo.h> 
 
int potiPin   = 1;  // analog A1 pin used to connect the potentiometer
int servoPin  = 5;  // digital D5 pin used to connect the servo

Servo servo;        // create servo object to control a servo 

int lastServoVal = -1;

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
} 
 
void loop() {
  // map(int, int, int, int) function was not used here intentionally for educational purposes ;)
  int   potiVal = analogRead(potiPin);        // reads the value of the potentiometer (0 .. 1023) 
  float fPotiVal = ((float)potiVal) / 1023.0; // normalize to 0.0 .. 1.0
  int   servoVal = (int)(fPotiVal * 179.0);   // project to     0 .. 179
  
  Serial.print("val: ");
  Serial.print(servoVal);
  
  if (servoVal != lastServoVal) {
    Serial.print(" =>");                      // indicate servo command
    servo.write(servoVal);                    // sets the servo position
    lastServoVal = servoVal;
  }
  Serial.println();
  delay(100);
} 
