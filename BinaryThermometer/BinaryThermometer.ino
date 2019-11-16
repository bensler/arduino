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
int dimFactor = 1;

// the setup function runs once when you press reset or power the board
void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);       // use the serial port
  sensors.begin();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void showTemperature(float celsius, int dimFactor) {
  int roundedCelsius = round(celsius);
  CRGB baseColor;

  if (celsius <= 0) {
    baseColor = COLOR_BLUE;
    roundedCelsius = -1 * roundedCelsius;
  } else { // number > 0
    baseColor = COLOR_RED;
  }
  showNumber(
    roundedCelsius,
    CRGB(baseColor).fadeToBlackBy((MAX_DIM - dimFactor) * DIM_STEP),
    CRGB(baseColor).fadeToBlackBy(255 - dimFactor)
  );
}

void showNumber(int number, CRGB brightColor, CRGB dimColor) {
  for (int i = 0; i < NUM_LEDS; i++) {
    int lastBit = number % 2;
    int index = inverted ? (NUM_LEDS - i - 1) : i;

    leds[index] = (lastBit ? brightColor : dimColor);
    number = number >> 1;
  }
  FastLED.show();
}

int calcDimFactor(int buttonState) {
  if (buttonState == 1) {
    dimFactor = (dimFactor >= NUM_LEDS) ? 1 : (dimFactor + 1);
  }
  return dimFactor;
}

void loop() {
  Serial.println();

  calcDimFactor(digitalRead(BUTTON_PIN));
  sensors.requestTemperatures();
  showTemperature(sensors.getTempCByIndex(0), dimFactor);

  Serial.print(sensors.getTempCByIndex(0));
  Serial.println("°C");

}
