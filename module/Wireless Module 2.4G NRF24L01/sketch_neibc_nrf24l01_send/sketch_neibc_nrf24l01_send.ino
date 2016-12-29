#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "printf.h"

#define CE_PIN 9
#define CSN_PIN 10
#define JOYSTICK_X A0
#define JOYSTICK_Y A1

const uint64_t pipe = 0xE8E8F0F0E1LL;

RF24 radio(CE_PIN, CSN_PIN);
int valarray[2];

void setup()
{
  Serial.begin(9600);
  printf_begin();

  radio.begin();
  radio.openWritingPipe(pipe);

  radio.printDetails();
}

void loop()
{
  Serial.println("try send...");
  valarray[0] = 0;
  valarray[1] = 1000;
  radio.write( valarray, sizeof(valarray) );
  Serial.println("sent...");
  radio.printDetails();

}
