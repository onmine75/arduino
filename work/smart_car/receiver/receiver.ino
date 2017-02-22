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
    radio.read( &time, 4 );
    Serial.println(time);
  }
}
///////////////////////////////////////////////
void setup_servo() {
  myservo.attach(3);  // attaches the servo on pin 9 to the servo object
}

void loop_servo(int angle) {
  Serial.print("loop_servo angle=");
  Serial.println(angle);
  myservo.write(angle);
  delay(15);
}
///////////////////////////////////////////////
void setup_motor() {
  Serial.println("L9110S setup");

  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
  stop();
}

void forward()
{
  Serial.println("forward");
  digitalWrite(AIA, HIGH);
  digitalWrite(AIB, LOW);

  digitalWrite(BIA, HIGH);
  digitalWrite(BIB, LOW);

}
void backward()
{
  Serial.println("backward");
  digitalWrite(AIA, LOW);
  digitalWrite(AIB, HIGH);

  digitalWrite(BIA, LOW);
  digitalWrite(BIB, HIGH);

}
void stop()
{
  Serial.println("stop");
  digitalWrite(AIA, LOW);
  digitalWrite(AIB, LOW);

  digitalWrite(BIA, LOW);
  digitalWrite(BIB, LOW);

}

///////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  setup_rf();
  setup_servo();
  setup_motor();
  
  loop_servo(90);
  stop();
}
char value;
int count = 0;
void loop() {
  if (Serial.available()) {
    value = Serial.read();
    if (value >= '0' && value <= '9')
    {
      value -= '0';
      pos = map((int)value, 0, 9, 0, 180);
      Serial.print("value=");
      Serial.print(value, DEC);
      Serial.print(", pos=");
      Serial.println(pos);
      loop_servo(pos);
    }else
    {
      if (value == 'f')
      {
        forward();
      }else if(value == 'b')
      {
        backward();
      }else if(value == 's')
      {
        stop();
      }
    }
  }
  loop_rf();
  //loop_servo();
}
