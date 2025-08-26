#ifndef PLATFORM_H
#define PLATFORM_H

#include <PubSubClient.h>

#if USE_ESP8266
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
ESP8266WebServer server(80);
#endif // ESP8266

#if USE_ESP32
#include <cJSON.h>
#include <WiFiClient.h>
#include <WebServer.h>
WebServer server(80);
#endif // ESP32

#endif // PLATFORM_H
