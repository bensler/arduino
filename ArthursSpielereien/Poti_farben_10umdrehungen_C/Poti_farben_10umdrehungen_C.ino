#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels;
float faktor;
uint32_t Color0 = pixels.Color(1, 0, 1);
uint32_t Color1 = pixels.Color(2, 0, 3);
uint32_t Color2 = pixels.Color(1, 0, 4);
uint32_t Color3 = pixels.Color(0, 1, 6);
uint32_t Color4 = pixels.Color(1, 6, 4);
uint32_t Color5 = pixels.Color(1, 9, 1);
uint32_t Color6 = pixels.Color(5, 7, 1);
uint32_t Color7 = pixels.Color(7, 4, 0);
uint32_t Color8 = pixels.Color(8, 2, 0);
uint32_t Color9 = pixels.Color(5, 0, 0);
uint32_t Color10 = pixels.Color(2, 0, 0);
//Regenbogenfarbspektrum nachempfunden

void setup() {
  pixels = Adafruit_NeoPixel(24, 6, NEO_GRB + NEO_KHZ800);
  faktor = (255.0 / 1023.0);
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
    pixels.setPixelColor(i, (i <= index) ? Color1 : Color0); 
  }
  if (index >= 24){
  for (int i=24; i < 48; i++) {
    pixels.setPixelColor(i-24, (i <= index) ? Color2 : Color1); 
  }
  }
  if (index >= 48){
  for (int i=48; i < 72; i++) {
    pixels.setPixelColor(i-48, (i <= index) ? Color3 : Color2); 
  }
  }
  if (index >= 72){
  for (int i=72; i < 96; i++) {
    pixels.setPixelColor(i-72, (i <= index) ? Color4 : Color3); 
  }
  }
  if (index >= 96){
  for (int i=96; i < 120; i++) {
    pixels.setPixelColor(i-96, (i <= index) ? Color5 : Color4); 
  }
  }
  if (index >= 120){
  for (int i=120; i < 144; i++) {
    pixels.setPixelColor(i-120, (i <= index) ? Color6 : Color5); 
  }
  }
  if (index >= 144){
  for (int i=144; i < 168; i++) {
    pixels.setPixelColor(i-144, (i <= index) ? Color7 : Color6); 
  }
  }
  if (index >= 168){
  for (int i=168; i < 192; i++) {
    pixels.setPixelColor(i-168, (i <= index) ? Color8 : Color7); 
  }
  }
  if (index >= 192){
  for (int i=192; i < 216; i++) {
    pixels.setPixelColor(i-192, (i <= index) ? Color9 : Color8); 
  }
  }
    if (index >= 216){
  for (int i=216; i < 240; i++) {
    pixels.setPixelColor(i-216, (i <= index) ? Color10 : Color9); 
  }
  }
  
  pixels.show();
}
