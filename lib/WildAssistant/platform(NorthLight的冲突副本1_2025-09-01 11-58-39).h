#ifndef PLATFORM_H
#define PLATFORM_H

#include <WebServer.h>

#if USE_ESP8266

extern ESP8266WebServer server;
#endif // ESP8266

#if USE_ESP32

extern WebServer server;
#endif // ESP32
#endif // PLATFORM_H
