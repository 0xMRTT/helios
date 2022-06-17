#include <OneWire.h>
#include <DallasTemperature.h>

const int SENSOR_PIN = 13; /

OneWire oneWire(SENSOR_PIN);         
DallasTemperature tempSensor(&oneWire); 

float tempCelsius;    

void setup() {
  Serial.begin(9600);
  tempSensor.begin();
  Serial.println("Initializing");
}

void loop() {
  tempSensor.requestTemperatures();             // send the command to get temperatures
  tempCelsius = tempSensor.getTempCByIndex(0);  // read temperature in Celsius

  Serial.print("Temperature: ");
  Serial.print(tempCelsius);    // print the temperature in Celsius
  Serial.print("°C");

  delay(500);

}
