#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "printf.h"
#define CE_PIN 9
#define CSN_PIN 10

const uint64_t pipe = 0xE8E8F0F0E1LL;

RF24 radio(CE_PIN, CSN_PIN);

int valarray[2];

void setup()
{
  Serial.begin(9600);
  printf_begin();
  delay(1000);
  Serial.println("Nrf24L01 Receiver Starting");
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
  delay(1000);
  radio.printDetails();
}

void loop()
{
  if ( radio.available() ) {
    while (true) {
      radio.read( (void*)valarray, sizeof(valarray) );
      Serial.print("X = ");
      Serial.print(valarray[0]);
      Serial.print(" Y = ");
      Serial.println(valarray[1]);
    }
  } else {
    Serial.println("No radio available");
    delay(1000);
  }

}
