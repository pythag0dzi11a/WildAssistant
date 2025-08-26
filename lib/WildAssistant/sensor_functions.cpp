#include <Arduino.h>
#include "sensor_functions.h"

/*
 * @brief 获取光线传感器的值
 * @param lightPin 光线传感器连接的引脚
 * @return 光线强度的百分比，范围从0到100
 */
short getLight(int lightPin)
{
    int light = analogRead(lightPin);

    int finalLight = map(light, 2500, 4500, 0, 100);

    return (100 - finalLight);
}

/*
 * @brief 获取湿度传感器的值
 * @return 湿度的百分比，范围从0到100
 */
short getHumidity()
{
    int humidity1 = 0, humidity2 = 0, result;
    long firstTime = millis();

    digitalWrite(ENABLE_SENSOR, HIGH);
    humidity1 = map(analogRead(ANALOG_PIN), 0, 4096, 0, 100);
    return 100 - humidity1;

    /*if (millis() - firstTime > 500)
    {
        humidity2 = map(analogRead(ANALOG_PIN),0,4096,0,100);
        if (humidity1 - humidity2 < 2)
        {
            return (humidity1 + humidity2)/2;
        }else{
            return getHumidity();
        }
    }*/
}
