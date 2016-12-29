/*
  Getting Started example sketch for nRF24L01+ radios
  This is a very basic example of how to send data from one node to another
  Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>
#include "RF24.h"
#include "printf.h"

// Set this radio as radio number 0(receiv) or 1(send)
bool radioNumber = 1;
// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8
RF24 radio(9, 10);

const uint64_t addresses[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };


// Used to control whether this node is sending or receiving
bool role = 0;

void setup() {
  Serial.begin(9600);
  printf_begin();

  Serial.println(F("RF24/examples/GettingStarted"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);

  // Open a writing and reading pipe on each radio, with opposite addresses
  if (radioNumber) {
    Serial.println("send mode!!");
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1, addresses[0]);
  } else {
    Serial.println("receive mode!!");
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1, addresses[1]);
  }

  // Start the radio listening for data
  radio.startListening();

  delay(1000);
  radio.printDetails();
}

void loop() {

  // Ping Out Role
  if (role == 1) {
    Serial.println("send mode");
    // First, stop listening so we can talk.
    radio.stopListening();
    Serial.println(F("Now sending"));

    // Take the time, and send it.  This will block until complete
    unsigned long time = micros();
    if (!radio.write( &time, sizeof(unsigned long) )) {
      Serial.println(F("failed"));
    }

    // Now, continue listening
    radio.startListening();

    // Set up a timeout period, get the current microseconds
    unsigned long started_waiting_at = micros();
    // Set up a variable to indicate if a response was received or not
    boolean timeout = false;

    // While nothing is received
    while ( ! radio.available() ) {
      // If waited longer than 200ms, indicate timeout and exit while loop
      if (micros() - started_waiting_at > 200000 ) {
        timeout = true;
        break;
      }
    }

    // Describe the results
    if ( timeout ) {
      Serial.println(F("Failed, response timed out."));
    } else {
      // Grab the response, compare, and send to debugging spew
      unsigned long got_time;
      radio.read( &got_time, sizeof(unsigned long) );
      unsigned long time = micros();

      // Spew it
      Serial.print(F("Sent "));
      Serial.print(time);
      Serial.print(F(", Got response "));
      Serial.print(got_time);
      Serial.print(F(", Round-trip delay "));
      Serial.print(time - got_time);
      Serial.println(F(" microseconds"));
    }

    // Try again 1s later
    delay(1000);
  }


  // Pong Back Role
  if ( role == 0 ) {
    // Variable for the received timestamp
    unsigned long got_time;

    if ( radio.available()) {
      // While there is data ready
      while (radio.available()) {
        // Get the payload
        radio.read( &got_time, sizeof(unsigned long) );
      }
      // First, stop listening so we can talk
      radio.stopListening();
      // Send the final one back.
      radio.write( &got_time, sizeof(unsigned long) );
      // Now, resume listening so we catch the next packets.
      radio.startListening();
      Serial.print(F("Sent response "));
      Serial.println(got_time);
    }else
    {
      Serial.println("receive mode, but not avaiable");
      delay(1000);
    }
  }

  // Change Roles via Serial Commands
  if ( Serial.available() ) {
    char c = toupper(Serial.read());
    if ( c == 'T' && role == 0 ) {
      Serial.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
      // Become the primary transmitter (ping out)
      role = 1;
      
    } else {
      if ( c == 'R' && role == 1 ) {
        Serial.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));
        // Become the primary receiver (pong back)
        role = 0;
        radio.startListening();
      }
    }
  }
}

