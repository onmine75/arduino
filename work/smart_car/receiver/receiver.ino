#include <VirtualWire.h>

#include <SPI.h>
#include "RF24.h"                                                                       

#include <SoftwareServo.h>


const int AIA = 5;
const int AIB = 6;

const int BIA = 7;  // PWM
const int BIB = 8;  // PWM

byte addresses[][6] = {"1Node", "2Node"};

const byte PIN_BUTTON_SELECT = 8;

const byte PIN_BUTTON_F = 7;
const byte PIN_BUTTON_E = 6;

const byte PIN_BUTTON_RIGHT = 3;
const byte PIN_BUTTON_UP = 2;
const byte PIN_BUTTON_DOWN = 4;
const byte PIN_BUTTON_LEFT = 5;

const byte PIN_ANALOG_X = 0;
const byte PIN_ANALOG_Y = 1;

byte speed = 255;  // change this (0-255) to control the speed of the motors
unsigned long time;

// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8
RF24 radio(9, 10);
///////////////////////////////////////////////
SoftwareServo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
///////////////////////////////////////////////
void forward(byte speed)
{
  Serial.print("forward speed=");
  Serial.println(speed);
  analogWrite(AIA, speed);
  digitalWrite(AIB, LOW);

  analogWrite(BIA, speed);
  digitalWrite(BIB, LOW);

}
void backward(byte speed)
{
  Serial.print("backward speed=");
  Serial.println(speed);
  digitalWrite(AIA, LOW);
  analogWrite(AIB, speed);

  digitalWrite(BIA, LOW);
  analogWrite(BIB, speed);

}
void stop()
{
  Serial.println("stop");
  digitalWrite(AIA, LOW);
  digitalWrite(AIB, LOW);

  digitalWrite(BIA, LOW);
  digitalWrite(BIB, LOW);

}

///
///////////////////////////////////////////////
void setup_l9110s()
{
  Serial.println("vw_rx_start");
  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  stop();

}
/*
  Getting Started example sketch for nRF24L01+ radios
  This is a very basic example of how to send data from one node to another
  Updated: Dec 2014 by TMRh20
*/
void setup_NRF24L01() {
  Serial.println("RECEIVE ROLE");

  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);

  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openWritingPipe((uint64_t)addresses[1]);
  radio.openReadingPipe(1, (uint64_t)addresses[0]);

  // Start the radio listening for data
  radio.startListening();
}
void setup()
{
  Serial.begin(9600);

  //setup_l9110s();
  setup_NRF24L01();

    myservo.attach(3);  // attaches the servo on pin 9 to the servo object
}
unsigned char buffer[32];
void loop() {
  // Now, continue listening
  radio.startListening();

  if (radio.available())
  {
    radio.read( buffer, 32 );
    for (int i = 0; i <= 9; i++)
    {
      Serial.print(buffer[i], HEX);
      Serial.print(" ");
    }
    Serial.println(" ");

    if (buffer[PIN_BUTTON_UP] == 1) {
      stop();
    } else {
      forward(255);
    }
    if (buffer[PIN_BUTTON_RIGHT] == 1){
      Serial.println("server 180");
      myservo.write(180);
      delay(15);
      SoftwareServo::refresh();
    }else
    {
      Serial.println("server 0");
      myservo.write(0);
      delay(15);
      SoftwareServo::refresh();
    }

  }
}
