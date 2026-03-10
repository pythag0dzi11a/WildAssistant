#ifndef SENSOR_RUN_H
#define SENSOR_RUN_H

#include <PubSubClient.h>
#include "platform.h"

extern PubSubClient client;
extern String ssid;
extern String password;
extern String mqtt_broker;
extern const int mqtt_port;
extern String mqtt_username;
extern String mqtt_password;
extern String topic;

void callback(char *topic, byte *payload, unsigned int length);
void connectWiFi(String ssidInput, String passwordInput);
void connectMQTTBroker();
void publish_msg_event(String topic, String msg);

#endif
