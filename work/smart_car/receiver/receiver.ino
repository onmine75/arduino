/*
  Getting Started example sketch for nRF24L01+ radios
  This is a very basic example of how to send data from one node to another
  Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>
#include "RF24.h"

#include <Servo.h>
//////////////////////////////////
// RF
RF24 radio(9, 10);
byte addresses[][6] = {"1Node", "2Node"};
char buffer[1024];
long time;
///////////////////////////////////////////////
// Servo
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

///////////////////////////////////////////////
// DC Motor
const int AIA = 4;
const int AIB = 5;

const int BIA = 6;
const int BIB = 7;
//////////////////////////////////
// MsgFormat
#define AXIS byte

#define MSG_VER_JOYSTICK 1

struct JoyStickMsgFormat
{
  byte version;
  bool sel : 1; //jostick pressed/released
  bool left : 1;
  bool right : 1;
  bool up: 1;
  bool down: 1;
  bool opt1: 1;
  bool opt2: 1;
  AXIS x;
  AXIS y;
  short raw_x;
  short raw_y;
};
JoyStickMsgFormat g_joystickMsg;

void printJoystick()
{
  Serial.print("v:");
  Serial.print(g_joystickMsg.version);
  Serial.print(" sel:");
  Serial.print(g_joystickMsg.sel);
  Serial.print(" left:");
  Serial.print(g_joystickMsg.left);
  Serial.print(" right:");
  Serial.print(g_joystickMsg.right);
  Serial.print(" up:");
  Serial.print(g_joystickMsg.up);
  Serial.print(" down:");
  Serial.print(g_joystickMsg.down);
  Serial.print(" opt1:");
  Serial.print(g_joystickMsg.opt1);
  Serial.print(" opt2:");
  Serial.print(g_joystickMsg.opt2);
  Serial.print(" x:");
  Serial.print(g_joystickMsg.x, DEC);
  Serial.print(" y:");
  Serial.print(g_joystickMsg.y, DEC);
  Serial.print(" raw_x:");
  Serial.print(g_joystickMsg.raw_x);
  Serial.print(" raw_y:");
  Serial.print(g_joystickMsg.raw_y);

  Serial.println(" ");
}
///////////////////////////////////////////////

void setup_rf() {
  Serial.println("RECEIVE ROLE");
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe((uint64_t)addresses[1]);
  radio.openReadingPipe(1, (uint64_t)addresses[0]);
  radio.startListening();
}

void loop_rf() {
  // Now, continue listening
  radio.startListening();

  if (radio.available())
  {
    int size = radio.getPayloadSize();
    //radio.read( buffer, size );
    //    Serial.print("size =");
    //    Serial.print(size);
    //    Serial.print(", data=");
    //    Serial.println(buffer);
    radio.read( &g_joystickMsg, sizeof(g_joystickMsg) );
    printJoystick();
  }
}
///////////////////////////////////////////////
void setup_servo() {
  myservo.attach(3);  // attaches the servo on pin 9 to the servo object
}

void loop_servo() {
  switch (g_joystickMsg.x / 10)
  {
    case 0: servo_set(0); break;
    case 1: servo_set(30); break;
    case 2: servo_set(30); break;
    case 3: servo_set(30); break;
    case 4: servo_set(50); break;
    case 5: servo_set(50); break;
    case 6: servo_set(50); break;
    case 7: servo_set(70); break;
    case 8: servo_set(70); break;
    case 9: servo_set(90); break;
    case 10: servo_set(90); break;
    case 11: servo_set(100); break;
    case 12: servo_set(100); break;
    case 13: servo_set(130); break;
    case 14: servo_set(130); break;
    case 15: servo_set(130); break;
    case 16: servo_set(150); break;
    case 17: servo_set(160); break;
    case 18: servo_set(160); break;
    case 19: servo_set(180); break;
    case 20: servo_set(180); break;
  }

}
int old_angle;
void servo_set(int angle) {
  if (old_angle == angle)
    return;
  old_angle = angle;
  Serial.print("servo_set angle=");
  Serial.println(angle);
  myservo.write(angle);
  //delay(15);
}
///////////////////////////////////////////////
void setup_motor() {
  Serial.println("L9110S setup");

  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
  motor_stop();
}

void motor_forward()
{
  Serial.println("forward");
  digitalWrite(AIA, HIGH);
  digitalWrite(AIB, LOW);

  digitalWrite(BIA, HIGH);
  digitalWrite(BIB, LOW);

}
void motor_backward()
{
  Serial.println("backward");
  digitalWrite(AIA, LOW);
  digitalWrite(AIB, HIGH);

  digitalWrite(BIA, LOW);
  digitalWrite(BIB, HIGH);

}
void motor_stop()
{
  Serial.println("stop");
  digitalWrite(AIA, LOW);
  digitalWrite(AIB, LOW);

  digitalWrite(BIA, LOW);
  digitalWrite(BIB, LOW);

}
int motor_cmd_old;
int motor_cmd;
void loop_motor()
{
  if (g_joystickMsg.up) {
    motor_cmd = 1;
  } else if (g_joystickMsg.down) {
    motor_cmd = 2;
  } else {
    motor_cmd = 0;
  }
  if (motor_cmd_old == motor_cmd)
    return;
  motor_cmd_old = motor_cmd;

  if (motor_cmd == 1)
    motor_forward();
  else if (motor_cmd == 2)
    motor_backward();
  else
    motor_stop();
}
///////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  setup_rf();
  setup_servo();
  setup_motor();

  servo_set(90);
  motor_stop();
}
char value;
int count = 0;
void loop() {
  //  if (Serial.available()) {
  //    value = Serial.read();
  //    if (value >= '0' && value <= '9')
  //    {
  //      value -= '0';
  //      pos = map((int)value, 0, 9, 0, 180);
  //      Serial.print("value=");
  //      Serial.print(value, DEC);
  //      Serial.print(", pos=");
  //      Serial.println(pos);
  //      loop_servo(pos);
  //    }else
  //    {
  //      if (value == 'f')
  //      {
  //        forward();
  //      }else if(value == 'b')
  //      {
  //        backward();
  //      }else if(value == 's')
  //      {
  //        stop();
  //      }
  //    }
  //  }
  loop_rf();
  loop_servo();
  loop_motor();
}
