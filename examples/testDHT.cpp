#include<Arduino.h>
#include<DHT.h>

#define dataPin 41
DHT dht(dataPin, DHT11);

void setup()
{
    Serial.begin(9600);
    dht.begin();
}

void loop()
{
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" *C");
    delay(2000);
}
