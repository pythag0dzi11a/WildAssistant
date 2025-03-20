#include <WildAssistant.h>
#include <cJSON.h>

// 这个函数用来获取光线传感器的值，并返回一个0-100的值。光线越强，数值越大。
short WildAssistant_getLight(int lightPin)
{
    int light = analogRead(lightPin);

    int finalLight = map(light, 2500, 4500, 0, 100);

    return (100 - finalLight);
}

// // 这个函数用来判断是否是第一次启动，并且返回0，1，或者3来判断状态。
short WildAssistant_isFirstBoot()
{
    String configureData;
    LittleFS.begin();

    // 读取configure.json内容，并保存到configureData中。
    if (LittleFS.exists("/configure.json"))
    {
        File metaConfigureData = LittleFS.open("/configure.json", "r");

        if (!metaConfigureData)
        {
            Serial.println("Failed To Open Configure File! ");
            return 3;
        }
        else
        {
            while (metaConfigureData.available())
            {
                configureData += (char)metaConfigureData.read();
            }

            metaConfigureData.close(); // 关闭文件

            Serial.println(configureData);
        }

        /*if ( metaConfigureData ){
            while ( metaConfigureData.available() ){
                configureData += metaConfigureData.read();
            }

            metaConfigureData.close();
        }else{
            Serial.println("Configure File Open FAILED! ");

            metaConfigureData.close();
        }*/
    }
    else
    {
        Serial.println("Configure File Doesn't EXISTS! ");
    }
    //

    // 使用cJSON解析configureData内容，并匹配FIRST_BOOT的值。
    cJSON *cJSONData = cJSON_Parse(configureData.c_str());
    if (cJSONData == NULL)
    {
        Serial.println("Configure File Parse FAILED! ");
        return 3;
    }

    cJSON *FIRSTBOOT = cJSON_GetObjectItem(cJSONData, "FIRSTBOOT");
    if (cJSON_IsBool(FIRSTBOOT))
    {
        return FIRSTBOOT->valueint;
    }
    else
    {
        Serial.println("Configure File ERROR! Recreating configure File! ");
        return 3;
    }

    cJSON_Delete(cJSONData);
}
