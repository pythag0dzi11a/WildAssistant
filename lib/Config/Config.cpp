//
// Created by Plane on 2026/3/7.
//

#include "Config.h"
#include "LittleFS.h"

bool ConfigT::readConfig(const char *configPath) {
    if (!LittleFS.exists(configPath)) {
        Serial.println("Config file doesn't exist");
        // 没有Config，创建一个默认Config。
    }

    File configFile = LittleFS.open("/config.json", "r");

    // 文件存在即解析Json并存入configDoc中，文件不存在则返回false。
    if (configFile) {
        // 使用ArduinoJson库解析Json文件并存入configDoc中。
        ArduinoJson::DeserializationError error = ArduinoJson::deserializeJson(configDoc, configFile);

        // 异常处理
        if (error) {
            Serial.println(F("deserializeJson() failed"));
            Serial.println(error.f_str());
            return false;
        }

        return true;
    } else {
        Serial.println("Error opening config file");
        return false;
    }
}

void ConfigT::begin(const char *configPath) {
    readConfig(configPath);
}

ConfigT::ConfigT() {
}

ConfigT::~ConfigT() {
    Serial.println("Config destructor called");
}

ConfigT Config;
