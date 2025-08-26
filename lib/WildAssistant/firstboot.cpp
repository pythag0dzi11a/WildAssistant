#include <Arduino.h>
#include <WiFi.h>
#include <LittleFS.h>
#include <WebServer.h>
#include "cJSON.h"
#include "platform.h"
#include "firstboot.h"

// String ssid = "";
// String password = "";
bool isConfigured = false;

/*
 * @brief 替换指定文件的内容
 * @param ModifiedData 要写入文件的内容(const char*)
 * @param FilePath 文件路径(const char*)
 */
void replaceJSON(const char *ModifiedData, const char *FilePath)
{
    File configureFile = LittleFS.open(FilePath, "w");

    configureFile.print(ModifiedData);

    configureFile.close();
}

/*
 * @brief 处理根目录请求
 */
void handleRoot()
{
    String setWiFiHTMLData;
    LittleFS.begin();

    // 读取configure.json内容，并保存到configureData中。
    if (LittleFS.exists("/setWiFi.html"))
    {
        File metaSetWiFiHTMLData = LittleFS.open("/setWiFi.html", "r");

        if (metaSetWiFiHTMLData)
        {
            while (metaSetWiFiHTMLData.available())
            {
                setWiFiHTMLData += (char)metaSetWiFiHTMLData.read();
            }

            metaSetWiFiHTMLData.close();
        }
        else
        {
            Serial.println("File setWiFI.html Open FAILED! ");

            metaSetWiFiHTMLData.close();
        }

        metaSetWiFiHTMLData.close();
    }
    else
    {
        Serial.println("File setWiFi.html Doesn't EXISTS! ");
    }

    server.send(200, "text/html", setWiFiHTMLData.c_str());
}

/*
 * @brief 处理连接请求
 */
void handleConnect()
{
    if (server.method() == HTTP_POST)
    {
        ssid = server.arg("ssid");
        password = server.arg("password");

        Serial.println("SSID: " + ssid);
        Serial.println("Password: " + password);

        isConfigured = true;
    }
}

/*
 * @brief 执行首次启动配置
 * @param AP_NAME 访问点名称(String)
 * @param AP_PASS 访问点密码(String)
 */
void firstBoot(String AP_NAME, String AP_PASS)
{

    WiFi.mode(WIFI_AP_STA);

    WiFi.softAP(AP_NAME.c_str(), AP_PASS.c_str());

    server.on("/", handleRoot);
    server.on("/connect", HTTP_POST, handleConnect);
    server.begin();

    while (!isConfigured)
    {
        server.handleClient();
    }

    Serial.println("connectingSSID: " + ssid);
    Serial.println("connectingPassword: " + password);

    WiFi.begin(ssid.c_str(), password.c_str());

    for (int connectCount = 0; connectCount < 15; connectCount++)
    {
        if (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }
        else
        {
            break;
        }
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        server.send(200, "text/html", "<h1>Connected to WiFi</h1><p>IP Address: " + WiFi.localIP().toString() + "</p>");

        // 将第一次启动的信息写入configure.json
        LittleFS.begin();

        File configureJSON = LittleFS.open("/configure.json", "r");
        String configuration;

        while (configureJSON.available())
        {
            configuration += (char)configureJSON.read();
        }

        cJSON *root = cJSON_Parse(configuration.c_str());
        cJSON *FIRSTBOOT = cJSON_GetObjectItem(root, "FIRSTBOOT");

        cJSON_SetBoolValue(FIRSTBOOT, false);

        String ModifiedData = cJSON_Print(root);

        replaceJSON(ModifiedData.c_str(), "/configure.json");
    }
    else
    {
        server.send(200, "text/html", "<h1>Failed to connect to WiFi</h1><p>Please try again.</p>");
    }
}

/*
 * @brief 判断是否是第一次启动
 * @return 0: 不是第一次启动; 1: 是第一次启动; 3: 读取配置文件出错
 */
short isFirstBoot()
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
