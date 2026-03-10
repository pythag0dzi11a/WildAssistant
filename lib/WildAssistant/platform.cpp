#include <WebServer.h>
#include <platform.h>

#if USE_ESP8266
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

ESP8266WebServer server(80);
#endif // ESP8266

#if USE_ESP32
#include <WebServer.h>
#include <WiFiClient.h>
#include <cJSON.h>

WebServer server(80);
#endif // ESP32
