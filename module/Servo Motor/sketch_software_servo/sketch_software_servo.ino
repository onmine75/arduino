#include <SoftwareServo.h>

SoftwareServo myservo;  // create servo object to control a servo

int val1;
int servoAngle = 0; 
void setup()
{
  Serial.begin(9600);
  myservo.attach(3);  // attaches the servo on pin 2 to the servo object
}
void servo_angle(int val1)
{
  Serial.print("val1=");
  Serial.print(val1);
  Serial.println(" ");
  myservo.write(val1);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there

  SoftwareServo::refresh();
}
void loop()
{
  servo_angle(0);      // Turn SG90 servo Left to 45 degrees
  delay(1000);          // Wait 1 second
  servo_angle(45);      // Turn SG90 servo Left to 45 degrees
  delay(1000);          // Wait 1 second
  servo_angle(90);      // Turn SG90 servo back to 90 degrees (center position)
  delay(1000);          // Wait 1 second
  servo_angle(135);     // Turn SG90 servo Right to 135 degrees
  delay(1000);          // Wait 1 second
  servo_angle(179);      // Turn SG90 servo back to 90 degrees (center position)
  delay(1000);

  //end control the servo's direction and the position of the motor


  //control the servo's speed

  //if you change the delay value (from example change 50 to 10), the speed of the servo changes
  for (servoAngle = 0; servoAngle < 180; servoAngle+=10) //move the micro servo from 0 degrees to 180 degrees
  {
    servo_angle(servoAngle);
    delay(50);
  }

  for (servoAngle = 180; servoAngle > 0; servoAngle-=10) //now move back the micro servo from 0 degrees to 180 degrees
  {
    servo_angle(servoAngle);
    delay(10);
  }
}

