/*
  Getting Started example sketch for nRF24L01+ radios
  This is a very basic example of how to send data from one node to another
  Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>
#include "RF24.h"
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
  Serial.print(sizeof(long));
  Serial.print(", data=");
  Serial.println(time);
  radio.write( &time, sizeof(long) );
}
///////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  setup_rf();
}
void loop() {
  loop_rf();
}

