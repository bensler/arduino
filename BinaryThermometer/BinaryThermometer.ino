#include <FastLED.h>

#include <OneWire.h>
#include <DallasTemperature.h>

#define LED_PIN     7
#define BUTTON_PIN  2
#define NUM_LEDS    7

const int inverted = 1;

int MAX_NUMBER = (1 << NUM_LEDS) - 1;

CRGB COLOR_RED   = CRGB(255,   0,   0);
CRGB COLOR_BLUE  = CRGB(  0,   0, 255);
CRGB COLOR_GREEN = CRGB(  0, 255,   0);
CRGB leds[NUM_LEDS];

#define ONE_WIRE_BUS 5

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

const int MAX_DIM  = NUM_LEDS + 1;
const int DIM_STEP = 256 / MAX_DIM;
int brightness = 1;
// to detect if button is newly pressed -> don't alter brightness, just display it
int lastButtonState = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  sensors.begin();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void showTemperature(float celsius, int brightness) {
  int roundedCelsius = round(celsius);
  CRGB baseColor;

  if (celsius <= 0) {
    baseColor = COLOR_BLUE;
    roundedCelsius = -1 * roundedCelsius;
  } else { // number > 0
    baseColor = COLOR_RED;
  }
  showNumberBinary(
    roundedCelsius, getBrightColor(baseColor), getDimColor(baseColor)
  );
}

void showNumberBinary(int number, CRGB brightColor, CRGB dimColor) {
  for (int i = 0; i < NUM_LEDS; i++) {
    int lastBit = number % 2;
    int index = inverted ? (NUM_LEDS - i - 1) : i;

    leds[index] = (lastBit ? brightColor : dimColor);
    number = number >> 1;
  }
}

void showNumberBar(int number, CRGB brightColor, CRGB dimColor) {
  for (int i = 0; i < NUM_LEDS; i++) {
    int index = inverted ? (NUM_LEDS - i - 1) : i;

    leds[index] = ((i < number) ? brightColor : dimColor);
  }
}

CRGB getBrightColor(CRGB baseColor) {
  return CRGB(baseColor).fadeToBlackBy((MAX_DIM - brightness) * DIM_STEP);
}

CRGB getDimColor(CRGB baseColor) {
  return CRGB(baseColor).fadeToBlackBy(255 - brightness);
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == 1) {
    if (lastButtonState == 1) {
      brightness = (brightness >= NUM_LEDS) ? 1 : (brightness + 1);
    }
    showNumberBar(
      brightness, getBrightColor(COLOR_GREEN), getDimColor(COLOR_GREEN)
    );
  } else {
    sensors.requestTemperatures();
    showTemperature(sensors.getTempCByIndex(0), brightness);
  }
  lastButtonState = buttonState;

  FastLED.show();
  delay(1000);
}
