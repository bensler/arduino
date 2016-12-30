// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(36, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
  uint32_t rot = pixels.Color(64, 0, 0);
  uint32_t schwarz = pixels.Color(0, 0, 0);
  
  for ( int i = 0; i < 12; i++) {
    setSegment(i, rot);
  }
  for ( int i = 0; i < 12; i++) {
    setSegment(i, schwarz);
  }
}

void setSegment(int index, uint32_t farbe) {  
  pixels.setPixelColor(2 * index, farbe); 
  pixels.setPixelColor((2 * index) + 1, farbe); 
  pixels.setPixelColor(24 + index, farbe); 

  pixels.show();
  delay(1000); // Delay for a period of time (in milliseconds).
}

