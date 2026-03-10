//
// Created by Plane on 2026/3/7.
//

#pragma once
#include "ArduinoJson.h"

class ConfigT {
private:
    bool readConfig(const char *configPath);

public:
    ArduinoJson::JsonDocument configDoc;

    ConfigT();

    ~ConfigT();

    void begin(const char *configPath = "/config.json");
};

extern ConfigT Config;
