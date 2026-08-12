#include <Arduino.h>
#include <cJSON.h>
#include <LittleFS.h>

void setup(){
LittleFS.begin();
}

void loop(){
    String data;
    char *modifiedData;

    File file = LittleFS.open("/test.json","r");

    if (!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    while (file.available()){
        data += (char)file.read();
    }

    file.close();

    Serial.println(data);

    cJSON *cJSONData = cJSON_Parse(data.c_str());
    if (cJSONData == NULL){
        Serial.println("Configure File Parse FAILED! ");
        Serial.println("3");
    }

    cJSON *TEST = cJSON_GetObjectItem(cJSONData,"test");

    if (cJSON_IsBool(TEST))
        Serial.println(TEST -> valueint);

    Serial.println("Now change the value: ");

    TEST -> valueint = 0;

    modifiedData = cJSON_Print(cJSONData);

    Serial.println(modifiedData);

    delay(5000);
}
