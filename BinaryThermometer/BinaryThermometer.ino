#include <FastLED.h>

#include <OneWire.h>
#include <DallasTemperature.h>

#define LED_PIN     7
#define NUM_LEDS    7

const int inverted = 1;

int MAX_NUMBER = (1 << NUM_LEDS) - 1;

CRGB leds[NUM_LEDS];

#define ONE_WIRE_BUS 5

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

// the setup function runs once when you press reset or power the board
void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);       // use the serial port
  sensors.begin();

  Serial.println(sensors.getDS18Count());
}

void showTemperature(float celsius, int dimFactor) {
  int roundedCelsius = round(celsius);
  CRGB brightRed  = CRGB(25 * dimFactor, 0,  0);
  CRGB dimRed     = CRGB( dimFactor, 0,  0);
  CRGB brightBlue = CRGB( 0, 0, 25 * dimFactor);
  CRGB dimBlue    = CRGB( 0, 0,  dimFactor);
  CRGB brightColor;
  CRGB dimColor;

  if (celsius <= 0) {
    brightColor = brightBlue;
    dimColor = dimBlue;
    roundedCelsius = -1 * roundedCelsius;
  } else { // number > 0
    brightColor = brightRed;
    dimColor = dimRed;
  }
  showNumber(roundedCelsius, brightColor, dimColor);
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

int calcDimFactor(float analogRead, int maxValue) {
  return round((analogRead / (float) maxValue) * (float)10);
}

void loop() {
  int poti = analogRead(A0);
  int dimFactor = calcDimFactor(poti, 1024);
  Serial.println(dimFactor);

  sensors.requestTemperatures();
  showTemperature(sensors.getTempCByIndex(0), dimFactor);

  Serial.print(sensors.getTempCByIndex(0));
  Serial.println("°C");
}
