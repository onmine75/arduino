/*
  Getting Started example sketch for nRF24L01+ radios
  This is a very basic example of how to send data from one node to another
  Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>
#include "RF24.h"

// Set this radio as radio number 0 or 1
bool radioNumber = 1;
// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8
RF24 radio(9, 10);

byte addresses[][6] = {"1Node", "2Node"};

unsigned long wait_time = 0;
// Used to control whether this node is sending or receiving
bool role = 0;


void setup() {
  Serial.begin(9600);
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
char buffer[1024];
void loop() {
  // Now, continue listening
  radio.startListening();

  if (radio.available())
  {
    int size = radio.getPayloadSize();
    radio.read( buffer, size );
    Serial.print("size =");
    Serial.print(size);
    Serial.print(", data=");
    Serial.println(buffer);
  }
}
