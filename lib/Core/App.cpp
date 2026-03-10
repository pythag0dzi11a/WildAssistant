#include "App.h"
#include <Arduino.h>
#include "LittleFS.h"
#include "../Config/Config.h"

AppT::AppT() {
    Serial.println("App constructor called");
}


void AppT::setup() {
    begin();
    xTaskCreatePinnedToCore(
        Task0,
        "Task0",
        1000,
        NULL,
        1,
        NULL,
        0);
}

void AppT::loop() {

}

void AppT::begin() {
    // 初始化引脚
    pinMode(Config.configDoc[""], OUTPUT);
    pinMode(Config.configDoc[""], INPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    digitalWrite(LED_BUILTIN, LOW);

    Serial.begin(115200);
    LittleFS.begin();
    Config.begin();
}


AppT::~AppT() {
    Serial.println("App destructor called");
}

AppT App;