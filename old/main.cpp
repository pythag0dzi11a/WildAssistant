#include <Arduino.h>
// #include <PubSubClient.h>
#include "platform.h"
#include <LittleFS.h>
#include <cJSON.h>
#include "firstboot.h"
#include "sensor_run.h"
#include "sensor_functions.h"
#include "sensor_msg.h"
#include "nlohmann/json.hpp"

// 引脚定义
#define ENABLE_SENSOR 1
#define ANALOG_PIN 3 // 要用的时候再赋能

#define INTERVAL 10 // 这是检测间隔，单位为秒

// 选择使用的模块，0是不使用，1是使用
#define USE_ESP8266 0
#define USE_ESP32 1

// AP模式设置
String AP_NAME = "pythagodzilla";
String AP_PASS = "pythagodzilla";

// WiFi初始化
String ssid = "";
String password = "";

// MQTT初始设置
String mqtt_broker = "pythagodzilla.pw";
String topic = "liuLake/SoilHumiditySensor";
String mqtt_username = "pythagodzilla";
String mqtt_password = "jtbx2mtblj";
const int mqtt_port = 1883;

using json = nlohmann::json;
WiFiClient espClient;
PubSubClient client(espClient);

// setup函数
void setup()
{


    switch (isFirstBoot())
    {
    case 0:
        break;

    case 1:
        firstBoot(AP_NAME.c_str(), AP_PASS.c_str());
        break;

    case 3:
        Serial.println("Error in reading configure.json");
        break;

    default:
        Serial.println("What the ? are you doing? ");
        break;
    }

    connectWiFi(ssid.c_str(), password.c_str());
    delay(100);

    Serial.println("WiFi status:" + (char)WiFi.status()); // 不确定先留着看

    connectMQTTBroker();
}

// loop函数
void loop()
{
    static long pastTime = 0;
    // int humidity = 0;
    // char strHumidity[16];
    String finalData, humidityData;

    if ((millis() - pastTime) / 1000 > INTERVAL)
    {
        humidityData = String(getHumidity());

        String msg = gen_publish_msg(get_client_id(), String(millis() / 1000), humidityData);

        publish_msg_event(topic.c_str(), msg.c_str());

        pastTime = millis();
    }
}
