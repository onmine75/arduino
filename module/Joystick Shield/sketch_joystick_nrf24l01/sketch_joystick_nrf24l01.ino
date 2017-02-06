#include <SPI.h>
#include "RF24.h"

RF24 radio(9, 10);
byte addresses[][6] = {"1Node", "2Node"};


// Select button is triggered when joystick is pressed
const byte PIN_BUTTON_SELECT = 8;

const byte PIN_BUTTON_F = 7;
const byte PIN_BUTTON_E = 6;

const byte PIN_BUTTON_RIGHT = 3;
const byte PIN_BUTTON_UP = 2;
const byte PIN_BUTTON_DOWN = 4;
const byte PIN_BUTTON_LEFT = 5;

const byte PIN_ANALOG_X = 0;
const byte PIN_ANALOG_Y = 1;

char buffer[9];
void setup_rf24()
{
    radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);

  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openWritingPipe((uint64_t)addresses[0]);
  radio.openReadingPipe(1, (uint64_t)addresses[1]);
  // Start the radio listening for data
  //radio.startListening();
}
void setup() {
  Serial.begin(9600);
  setup_rf24();
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

void loop() {
  buffer[PIN_BUTTON_UP] = digitalRead(PIN_BUTTON_UP);
  buffer[PIN_BUTTON_RIGHT] = digitalRead(PIN_BUTTON_RIGHT);
  buffer[PIN_BUTTON_DOWN] = digitalRead(PIN_BUTTON_DOWN);
  buffer[PIN_BUTTON_LEFT] = digitalRead(PIN_BUTTON_LEFT);
  buffer[PIN_BUTTON_SELECT] = digitalRead(PIN_BUTTON_SELECT);
  buffer[PIN_BUTTON_F] = digitalRead(PIN_BUTTON_F);
  buffer[PIN_BUTTON_E] = digitalRead(PIN_BUTTON_E);
  buffer[PIN_ANALOG_X] = analogRead(PIN_ANALOG_X);
  buffer[PIN_ANALOG_Y] = analogRead(PIN_ANALOG_Y);
  Serial.print("U:");
  Serial.print(buffer[PIN_BUTTON_UP], HEX);
  Serial.print(" ");

  Serial.print("R:");
  Serial.print(buffer[PIN_BUTTON_RIGHT], HEX);
  Serial.print(" ");

  Serial.print("D:");
  Serial.print(buffer[PIN_BUTTON_DOWN], HEX);
  Serial.print(" ");

  Serial.print("L:");
  Serial.print(buffer[PIN_BUTTON_LEFT], HEX);
  Serial.print(" ");


  Serial.print("S:");
  Serial.print(buffer[PIN_BUTTON_SELECT], HEX);
  Serial.print(" ");


  Serial.print("F:");
  Serial.print(buffer[PIN_BUTTON_F], HEX);
  Serial.print(" ");

  Serial.print("E:");
  Serial.print(buffer[PIN_BUTTON_E], HEX);
  Serial.print(" ");

  Serial.print("x:");
  Serial.print(buffer[PIN_ANALOG_X], HEX);
  Serial.print(" ");

  Serial.print("y:");
  Serial.print(buffer[PIN_ANALOG_Y], HEX);
  Serial.print(" ");
  Serial.println();

   radio.write( buffer, sizeof(buffer) );
}
