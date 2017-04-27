#include <Adafruit_NeoPixel.h>

#define LED_PIN            2

const int knockSensor1 = A0; // the piezo is connected to analog pin 0
const int threshold = 30;  // threshold value to decide when the detected sound is a knock or not

// these variables will change:
int sensorReading1 = 0;      // variable to store the value read from the sensor pin
int temp_sensorReading1 = -1;      // variable to store the value read from the sensor pin

int color_count = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);       // use the serial port
  strip.begin(); // This initializes the NeoPixel library.
}

void loop() {
  // read the sensor and store it in the variable sensorReading:
  temp_sensorReading1 = analogRead(knockSensor1);
  if ((temp_sensorReading1 == sensorReading1))
  {

  } else {
    Serial.print(temp_sensorReading1);
    Serial.print(", ");
    Serial.println(" ");
  }

  // if the sensor reading is greater than the threshold:
  if ((sensorReading1 == 0) && (temp_sensorReading1 >= threshold)) {
    // send the string "Knock!" back to the computer, followed by newline
    Serial.println("Knock!");
    color_count++;

    switch (color_count)
    {
      case 0:
        break;
      case 1:
        rainbow(10);
        colorWipe(strip.Color(255, 0, 0), 0);  // Red
        break;
      case 2:
        rainbow(10);
        colorWipe(strip.Color(0, 255, 0), 0);  // Green
        break;
      case 3:
        rainbow(10);
        colorWipe(strip.Color(0, 0, 255), 0);  // Blue
        break;
      case 4:
        rainbow(10);
        colorWipe(strip.Color(255, 255, 255), 0); // White
        break;
      default:
        color_count = 0;
        break;
    }
  }

  sensorReading1 = temp_sensorReading1;
  delay(100);  // delay to avoid overloading the serial port buffer
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  Serial.print("colorWipe ");
  Serial.print(c, HEX);
  Serial.println(" ");
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

