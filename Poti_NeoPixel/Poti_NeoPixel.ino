#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels;
float faktor;
uint32_t onColor = pixels.Color(9, 9, 0);
uint32_t offColor = pixels.Color(0, 0, 4);

void setup() {
  pixels = Adafruit_NeoPixel(24, 6, NEO_GRB + NEO_KHZ800);
  faktor = (23.0 / 1023.0);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValueSilber = analogRead(A1);
  
  show((int)((faktor * sensorValueSilber) + 0.5));
  // print out the value you read:
  delay(10);        // delay in between reads for stability
}

void show(int index) {
  for (int i = 0; i < 24; i++) {
    pixels.setPixelColor(i, (i <= index) ? onColor : offColor); 
  }
  pixels.show();
}
