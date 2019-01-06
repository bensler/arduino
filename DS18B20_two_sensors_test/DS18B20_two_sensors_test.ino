#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 5

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

void setup(void) {
  Serial.begin(9600);
  sensors.begin();
}

void loop(void) { 
  sensors.requestTemperatures(); 
  float celcius1 = sensors.getTempCByIndex(0);
  float celcius2 = sensors.getTempCByIndex(1);
  Serial.print(celcius1);
  Serial.print("°C  -  ");
  Serial.print(celcius2);
  Serial.println("°C");
  delay(1000);
}
