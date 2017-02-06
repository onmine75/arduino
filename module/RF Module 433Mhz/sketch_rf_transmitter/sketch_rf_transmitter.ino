#include <VirtualWire.h>
char *controller;
unsigned long time;
void setup() {
  Serial.begin(9600);

  vw_set_ptt_inverted(true); //
  vw_set_tx_pin(12);
  vw_setup(4000);// speed of data transfer Kbps
}

void loop() {
  time = millis();
  //prints time since program started
  Serial.print(time);
  Serial.print(", ");
  vw_send((uint8_t *)controller, strlen(controller));
  vw_wait_tx(); // Wait until the whole message is gone

  Serial.println(controller);
  delay(2000);
  time = millis();
  //prints time since program started
  Serial.print(time);
  Serial.print(", ");
  controller = "0"  ;
  vw_send((uint8_t *)controller, strlen(controller));
  vw_wait_tx(); // Wait until the whole message is gone
  Serial.println(controller);
  delay(2000);

}
