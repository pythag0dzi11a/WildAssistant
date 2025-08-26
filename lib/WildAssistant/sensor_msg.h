#ifndef SENSOR_MSG_H
#define SENSOR_MSG_H

#include <Arduino.h>

String get_client_id();
String gen_publish_msg(String client_id, String time, String data);
String gen_connect_broker_msg(String client_id, String type, String location, String connect_time);

#endif // SENSOR_MSG_H
