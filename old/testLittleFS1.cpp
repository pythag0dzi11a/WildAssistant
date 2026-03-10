#include <LittleFS.h>
#include <cJSON.h>

int code;

void setup()
{

    Serial.begin(115200);
    LittleFS.begin();

    if (LittleFS.exists("/configure.json"))
    {
        Serial.println("File exists");
        /* code */
    }
    else
    {
        Serial.println("File does not exist");
    }
}

void loop()
{

    String ConfigureData, ConfigureData2;

    if (LittleFS.exists("/configure.json"))
    {
        Serial.println("File exists");
        /* code */
    }
    else
    {
        Serial.println("File does not exist");
    }

    delay(1000);

    File configureFile = LittleFS.open("/configure.json", "r");
    if (!configureFile)
    {
        Serial.println("Failed to open file for reading");
        return;
    }

    while (configureFile.available())
    {
        ConfigureData += (char)configureFile.read();
    }

    configureFile.close();

    Serial.println(ConfigureData);

    cJSON *cJSONData = cJSON_Parse(ConfigureData.c_str());
    if (cJSONData == NULL)
    {
        Serial.println("Configure File Parse FAILED! ");
        Serial.println("3");
    }

    cJSON *FIRSTBOOT = cJSON_GetObjectItem(cJSONData, "FIRSTBOOT");
    if (cJSON_IsBool(FIRSTBOOT))
    {
        Serial.println(FIRSTBOOT->valueint);
    }
    else
    {
        Serial.println("Configure File ERROR! Recreating configure File! ");
        Serial.println("3");
    }

    cJSON_SetBoolValue(cJSON_GetObjectItem(cJSON_Parse("/configure.json"), "FIRSTBOOT"), false);

    Serial.println("Now change the value of FIRSTBOOT:");

    if (cJSON_IsBool(FIRSTBOOT))
    {
        cJSON_SetBoolValue(FIRSTBOOT, false); // 设置为 false
    }

    char *modified_json = cJSON_PrintUnformatted(cJSONData);
    // 然后保存到LittleFS

    Serial.print(modified_json);
    Serial.println("..................");
    delay(2000);
}
