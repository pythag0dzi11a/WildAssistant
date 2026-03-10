#pragma once

class AppT
{
private:
    void begin();
    static void Task0(void *pvParameters);

public:
    AppT();
    ~AppT();
    void loop();
    void setup();
};

extern AppT App;
