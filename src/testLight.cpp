#include <Arduino.h>
#include <WildAssistant.h>

#define dataPin 12

void setup()
{
    Serial.begin(115200);
    pinMode(dataPin, INPUT);
}

void loop()
{
    int light = WildAssistant_getLight(dataPin);
    //Serial.println(analogRead(dataPin));
    Serial.println(light);
    delay(1000);
}
