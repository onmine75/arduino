#include <VirtualWire.h>
unsigned long time;
void setup()
{
  Serial.begin(9600);

  vw_set_ptt_inverted(true); // Required for DR3100
  vw_set_rx_pin(12);
  vw_setup(4000);  // Bits per sec
  vw_rx_start();       // Start the receiver PLL running
  Serial.println("vw_rx_start");
}
void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    time = millis();
    //prints time since program started
    Serial.print(time);
    Serial.print(", ");
    for (int index = 0; index < buflen; index++){
      Serial.print("0x");
      Serial.print(buf[index], HEX);
    }
    Serial.println("..end");
  }
}
