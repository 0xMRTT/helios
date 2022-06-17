#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <Ethernet.h>

const int SENSOR_PIN = 13; 

OneWire oneWire(SENSOR_PIN);         
DallasTemperature tempSensor(&oneWire); 

float tempCelsius;    

byte mac[] = {
               0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
             };

IPAddress ip(192, 168, 0, 177);
EthernetServer server(80);

void setup() {
  Serial.begin(9600);
  tempSensor.begin();
  Ethernet.begin(mac, ip);
  Serial.println("Initializing");
  Serial.print("Your IP Adress is ");
  Serial.println(Ethernet.localIP( ) );
}

void loop() {
  tempSensor.requestTemperatures();             // send the command to get temperatures
  tempCelsius = tempSensor.getTempCByIndex(0);  // read temperature in Celsius

  Serial.print("Temperature: ");
  Serial.print(tempCelsius);    // print the temperature in Celsius
  Serial.print("°C");

  EthernetClient webpage = server.available();
  if (webpage) 
    {
      Serial.println("new webpage");
      boolean currentLineIsBlank = true;
      while (webpage.connected ( ) ) 
        {
          if (webpage.available ( ) ) 
            {
              char character = webpage.read ( );
              Serial.write(character);
              if (character == '\n' && currentLineIsBlank) 
                {
                  webpage.println ("HTTP/1.1 200 OK");
                  webpage.println ("Content-Type: text/html");
                  webpage.println ("Connection: close");
                  webpage.println ("Refresh: 5");
                  webpage.println ( );
                  webpage.println ("<!DOCTYPE HTML>");
                  webpage.println ("<html>");
                  webpage.print ("<Title>Temp </Title>");
                  webpage.print ("<h1>Temperature </h1>");
                  webpage.print ("<h4>");
                  webpage.print (tempCelsius);
                  webpage.print ("°C</h4>");
                  webpage.println ("</html>");
                  break;
                }
                 
                if ( character == '\n') 
                  {
                    currentLineIsBlank = true;
                  } 
                else if (character != '\r') 
                  {
                    currentLineIsBlank = false;
            }
        }
    }
    delay(1);
    webpage.stop();
    Serial.println("webpage disconnected");

}
}