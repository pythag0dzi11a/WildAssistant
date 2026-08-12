#include <Arduino.h>
#include "BLEDevice.h"
#include "BLE2902.h"

#define SERVICE_UUID "0000ffe0-0000-1000-8000-00805f9b34fb"
#define CHAR_COMMAND_UUID "0000ffe1-0000-1000-8000-00805f9b34fb"
#define CHAR_DATA_UUID "0000ffe2-0000-1000-8000-00805f9b34fb"

BLEServer *pServer = nullptr;
BLECharacteristic *pDataChar = nullptr;
bool deviceConnected = false;
uint32_t counter = 0;

class ServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer *s) {
        deviceConnected = true;
        Serial.println("Connected to device");
    };

    void onDisconnect(BLEServer *s) {
        deviceConnected = false;
        Serial.println("Disconnected from device");
        s->getAdvertising()->start();
    };
};

class CommandCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *c) {
        std::string v = c->getValue();
        Serial.printf("Received command: %s\n", v.c_str());
    };
};

void setup() {
    Serial.begin(115200);
    BLEDevice::init("ESP32_BLE");
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new ServerCallbacks());
    BLEService *pService = pServer->createService(SERVICE_UUID);
    BLECharacteristic *pCmdChar = pService->createCharacteristic(CHAR_COMMAND_UUID, BLECharacteristic::PROPERTY_WRITE);
    pCmdChar->setCallbacks(new CommandCallbacks());
    pDataChar = pService->createCharacteristic(CHAR_DATA_UUID, BLECharacteristic::PROPERTY_READ);
    pDataChar->addDescriptor(new BLE2902());
    pDataChar->setValue("0");
    pService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    BLEDevice::startAdvertising();
    Serial.println("Waiting for a client connection to notify...");
}

void loop() {
    if (deviceConnected) {
        counter++;
        pDataChar->setValue(std::to_string(counter));
        pDataChar->notify();
        Serial.printf("Notified value: %d\n", counter);
        delay(1000);
    }
}
