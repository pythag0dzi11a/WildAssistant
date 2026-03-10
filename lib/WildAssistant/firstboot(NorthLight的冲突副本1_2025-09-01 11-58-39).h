#ifndef FIRSTBOOT_H
#define FIRSTBOOT_H

#include <Arduino.h>
#include <LittleFS.h>
// #include <WebServer.h>

extern String ssid;
extern String password;
extern bool isConfigured;

void replaceJSON(const char *ModifiedData, const char *FilePath);
void handleRoot();
void handleConnect();
void firstBoot(String AP_NAME, String AP_PASS);
short isFirstBoot();
String read_configuration();

#endif // FIRSTBOOT_H
