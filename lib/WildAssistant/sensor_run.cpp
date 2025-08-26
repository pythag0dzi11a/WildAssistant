#include <Arduino.h>
#include <WiFi.h>
#include "sensor_run.h"
#include "sensor_functions.h"
#include "sensor_msg.h"

/*
 * @brief MQTT消息回调函数
 * @param topic 消息主题
 * @param payload 消息内容
 * @param length 消息长度
 */
void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);

    Serial.print("Message:");
    for (unsigned int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

/*
 * @brief 发布消息事件，发送的时候会保证连接网络，但是缺乏长时间测试，所以具体可能出什么问题暂未未知。
 * @param topic 消息主题(String)
 * @param msg 消息内容(String)
 */
void publish_msg_event(String topic, String msg)
{
    if (WiFi.status() == WL_CONNECTED)
    {
        if (client.connected())
        {
            client.publish(topic.c_str(), msg.c_str());
        }
        else
        {
            connectMQTTBroker();
        }
    }
    else
    {
        connectWiFi(ssid.c_str(), password.c_str());
    }
}

/*
 * @brief 连接WiFi
 * @param ssidInput WiFi SSID
 * @param passwordInput WiFi密码
 */
void connectWiFi(String ssidInput, String passwordInput)
{
    // WiFi.mode(WIFI_STA);
    WiFi.begin(ssidInput.c_str(), passwordInput.c_str());
    Serial.println("Connecting to the WiFi network");

    for (int connectCount = 0; connectCount < 15; connectCount++)
    {
        if (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }
        else if (connectCount == 14)
        {
            Serial.println("WiFi connection failed. Please check your settings and the signal.");
            break;
        }
        else
        {
            Serial.println("Connected to the WiFi network");
            break;
        }
    }
}

// 连接MQTT Broker
void connectMQTTBroker()
{
    client.setServer(mqtt_broker.c_str(), mqtt_port);
    client.setCallback(callback);

    while (!client.connected())
    {
        String client_id = get_client_id();
        Serial.printf("\nThe client %s connects to the public MQTT broker\n", client_id.c_str());

        if (client.connect(client_id.c_str(), mqtt_username.c_str(), mqtt_password.c_str()))
        {
            Serial.println("Public EMQX MQTT broker connected");
        }
        else
        {
            Serial.println("failed with state");
            Serial.println(client.state());
            delay(2000);
        }
    }

    int gen_start_time = millis() / 1000;
    String publish_msg = gen_connect_broker_msg(get_client_id(), String("temperature"), String("testLocation"), String(gen_start_time));

    client.publish(topic.c_str(), publish_msg.c_str());
    client.subscribe(topic.c_str());
}
