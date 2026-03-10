#include <Arduino.h>
#include <cJSON.h>

void setup()
{

    String out;
    Serial.begin(115200);

    cJSON *seed = cJSON_CreateObject();
    cJSON *item = cJSON_CreateString("data");
    cJSON_AddItemToObject(seed, "Humidiy", item);

    out  = cJSON_Print(seed);

    cJSON_Delete(seed);
    while (1)
    {
        Serial.println(out);
        delay(1000);
    }


}

void loop()
{

}
