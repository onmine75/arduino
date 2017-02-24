/*
  Getting Started example sketch for nRF24L01+ radios
  This is a very basic example of how to send data from one node to another
  Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>
#include "RF24.h"
//////////////////////////////////
// Joystick
const byte PIN_BUTTON_SELECT = 8;
const byte PIN_BUTTON_F = 7;
const byte PIN_BUTTON_E = 6;
const byte PIN_BUTTON_RIGHT = 3;
const byte PIN_BUTTON_UP = 2;
const byte PIN_BUTTON_DOWN = 4;
const byte PIN_BUTTON_LEFT = 5;
const byte PIN_ANALOG_X = 0;
const byte PIN_ANALOG_Y = 1;

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
  bool opt1:1;
  bool opt2:1;
  AXIS x;
  AXIS y; 
  short raw_x;
  short raw_y;
};
JoyStickMsgFormat g_joystickMsg;

void printJoystick(bool ln)
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
  if (ln)
    Serial.println(" ");
}
//////////////////////////////////
// RF
// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8
RF24 radio(9, 10);
byte addresses[][6] = {"1Node", "2Node"};
unsigned long time;
String str_time;


///////////////////////////////////////

void setup_rf() {
  Serial.println("TRANSMIT ROLE");

  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe((uint64_t)addresses[0]);
  radio.openReadingPipe(1, (uint64_t)addresses[1]);
  // Start the radio listening for data
  radio.startListening();
}

void loop_rf() {
  radio.stopListening();
  time = millis();
  str_time = time;
  // Variable for the received timestamp
  Serial.print("send=");
  Serial.print(", size=");
  Serial.print(sizeof(g_joystickMsg));
  Serial.println(" ");
  radio.write( &g_joystickMsg, sizeof(g_joystickMsg) );
}
///////////////////////////////////////////////
void setup_joystick() {
  pinMode(PIN_BUTTON_RIGHT, INPUT);
  digitalWrite(PIN_BUTTON_RIGHT, HIGH);
  pinMode(PIN_BUTTON_LEFT, INPUT);
  digitalWrite(PIN_BUTTON_LEFT, HIGH);
  pinMode(PIN_BUTTON_UP, INPUT);
  digitalWrite(PIN_BUTTON_UP, HIGH);
  pinMode(PIN_BUTTON_DOWN, INPUT);
  digitalWrite(PIN_BUTTON_DOWN, HIGH);
  pinMode(PIN_BUTTON_SELECT, INPUT);
  digitalWrite(PIN_BUTTON_SELECT, HIGH);
  pinMode(PIN_BUTTON_E, INPUT);
  digitalWrite(PIN_BUTTON_E, HIGH);
  pinMode(PIN_BUTTON_F, INPUT);
  digitalWrite(PIN_BUTTON_F, HIGH);
}
short raw_x;
short raw_y;
bool sel;
bool left;
bool right;
bool up;
bool down;
bool opt1;
bool opt2;

void loop_joystick() {
  up = digitalRead(PIN_BUTTON_UP);
  right = digitalRead(PIN_BUTTON_RIGHT);
  down = digitalRead(PIN_BUTTON_DOWN);
  left = digitalRead(PIN_BUTTON_LEFT);
  sel = digitalRead(PIN_BUTTON_SELECT);
  opt1 = digitalRead(PIN_BUTTON_F);
  opt2 = digitalRead(PIN_BUTTON_E);
  raw_x = analogRead(PIN_ANALOG_X);
  raw_y = analogRead(PIN_ANALOG_Y);

  g_joystickMsg.version = MSG_VER_JOYSTICK;
  g_joystickMsg.up = up?0:1;
  g_joystickMsg.right = right?0:1;
  g_joystickMsg.down = down?0:1;
  g_joystickMsg.left = left?0:1;
  g_joystickMsg.sel = sel?0:1;
  g_joystickMsg.opt1 = opt1?0:1;
  g_joystickMsg.opt2 = opt2?0:1;
  g_joystickMsg.raw_x = raw_x;
  g_joystickMsg.raw_y = raw_y;
  g_joystickMsg.x = map(raw_x, 0, 700, 0, 200);
  g_joystickMsg.y = map(raw_y, 0, 700, 0, 200);
  printJoystick(false);
}
///////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  setup_rf();
  setup_joystick();
}
void loop() {
  loop_joystick();
  loop_rf();
}

