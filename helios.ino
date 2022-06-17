#include <OneWire.h>
#include <DallasTemperature.h>

const int SENSOR_PIN = 13; /

OneWire oneWire(SENSOR_PIN);         
DallasTemperature tempSensor(&oneWire); 

float tempCelsius;    

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing");
}

void loop() {
  // put your main code here, to run repeatedly:

}
