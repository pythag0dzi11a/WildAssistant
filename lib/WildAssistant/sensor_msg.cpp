#include <Arduino.h>
#include <cJSON.h>
#include <WiFi.h>
#include "sensor_msg.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

/*
 * @brief 生成MQTT连接消息
 * @param client_id 客户端ID
 * @param type 设备类型
 * @param location 设备位置
 * @param connect_time 传感器上线时间（使用millis()获取，单位待定）
 * @return 连接消息字符串
 */
String gen_connect_broker_msg(String client_id, String type, String location, String connect_time)
{
    json msg;
    msg["sensor-client_id"] = client_id.c_str();
    msg["type"] = type.c_str();
    msg["location"] = location.c_str();
    msg["connect_time"] = connect_time.c_str();

    Serial.println(msg.dump().c_str());

    return msg.dump().c_str();
}

/*
 * @brief 生成MQTT发布消息
 * @param client_id 客户端ID
 * @param t 主题
 * @param time 信息生成时间（使用millis()获取，单位待定）
 * @return 发布消息字符串
 */
String gen_publish_msg(String client_id, String time, String data)
{
    json msg;
    msg["sensor-client_id"] = client_id.c_str();
    msg["payload"]["time"] = time.c_str();
    msg["payload"]["data"] = data.c_str();

    Serial.println(msg.dump().c_str());

    return msg.dump().c_str();
}

/*
 * @brief 生成MQTT客户端ID
 * @return 客户端ID字符串
 */
String get_client_id()
{
    String mac_address = WiFi.macAddress();
    String client_id_result = "sensor-" + mac_address;
    return client_id_result;
}
