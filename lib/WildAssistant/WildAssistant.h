#ifndef WILDASSISTANT_H
#define WILDASSISTANT_H

#include <Arduino.h>
#include <LittleFS.h>
#if USE_ESP8266
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#endif //ESP8266

#if USE_ESP32
#include <cJSON.h>
#include <PubSubClient.h>
#include <WiFiClient.h>
#endif //ESP32

short WildAssistant_getLight(int lightPin);
short WildAssistant_isFirstBoot(); // 我觉得这个函数的命名很不优雅，它返回的相当于一个状态码。但是我不想改了。

#endif //WILDASSISTANT_H
