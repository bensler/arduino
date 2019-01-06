#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            10

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      24

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 50; // delay for half a second
int clock = 0;

uint32_t highlight = pixels.Color(10, 0, 0);
int patternWidth = 5;
int highlighted = 0;

int maxBackgroundSaturation = 10;
int backgroundUpDown = 1; // 1 .. dim up, -1 .. dim down
int backgroundSaturation = 0;

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
  for (int i = 0; i < NUMPIXELS; i++) {
    uint32_t background = pixels.Color(backgroundSaturation, backgroundSaturation, 0);
    pixels.setPixelColor(i, (((i % patternWidth) == highlighted) ? highlight : background));
  }
  pixels.show(); // This sends the updated pixel color to the hardware.

  if ((clock % 2) == 0) { // move red dots only every 2nd clock tic, half speed of background flashing
    highlighted++;
    highlighted = (highlighted >= patternWidth) ? 0 : highlighted;
  }

  backgroundSaturation += backgroundUpDown;
  if (backgroundSaturation >= maxBackgroundSaturation) {
    backgroundUpDown = -1;
  }
  if (backgroundSaturation <= 0) {
    backgroundUpDown = 1;
  }

  clock++;
  delay(delayval); // Delay for a period of time (in milliseconds).
}
