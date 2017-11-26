#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels;
float faktor;
uint32_t Color1 = pixels.Color(12, 12, 0);
uint32_t Color2 = pixels.Color(12, 8, 0);
uint32_t Color3 = pixels.Color(12, 4, 0);
uint32_t Color4 = pixels.Color(12, 0, 0);
uint32_t Color5 = pixels.Color(10, 0, 6);
uint32_t Color6 = pixels.Color(0, 0, 4);

void setup() {
  pixels = Adafruit_NeoPixel(24, 6, NEO_GRB + NEO_KHZ800);
  faktor = (143.0 / 1023.0);
  pixels.begin(); // This initializes the NeoPixel library.
}

// the loop routine runs over and over again forever:
void loop() {
  show((int)((faktor * analogRead(A1)) + 0.5));
  // print out the value you read:
  delay(10);        // delay in between reads for stability
}

void show(int index) {
  for (int i = 0; i < 24; i++) {
    pixels.setPixelColor(i, (i <= index) ? Color1 : Color6); 
  }
  if (index >= 24) {
    for (int i=24; i < 48; i++) {
      pixels.setPixelColor(i-24, (i <= index) ? Color2 : Color1); 
    }
  }
  if (index >= 48) {
    for (int i=48; i < 72; i++) {
      pixels.setPixelColor(i-48, (i <= index) ? Color3 : Color2); 
    }
  }
  if (index >= 72) {
    for (int i=72; i < 96; i++) {
      pixels.setPixelColor(i-72, (i <= index) ? Color4 : Color3); 
    }
  }
  if (index >= 96) {
    for (int i=96; i < 120; i++) {
      pixels.setPixelColor(i-96, (i <= index) ? Color5 : Color4); 
    }
  }
  if (index >= 120) {
    for (int i=120; i < 144; i++) {
      pixels.setPixelColor(i-120, (i <= index) ? Color6 : Color5); 
    }
  }
  
  pixels.show();
}
