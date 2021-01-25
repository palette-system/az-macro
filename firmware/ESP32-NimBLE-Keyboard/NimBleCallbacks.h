#ifndef ESP32_BLE_KEYBOARD_NIMBLE_CALLBACKS_H
#define ESP32_BLE_KEYBOARD_NIMBLE_CALLBACKS_H

#include <NimBLEServer.h>
#include <NimBLEDevice.h>
#include "HIDKeyboardTypes.h"
#include "HIDTypes.h"



class CharacteristicCallbacks: public NimBLECharacteristicCallbacks {
  public:
	CharacteristicCallbacks();
    void onRead(NimBLECharacteristic* pCharacteristic);
    void onWrite(NimBLECharacteristic* pCharacteristic);
    void onNotify(NimBLECharacteristic* pCharacteristic);
    void onStatus(NimBLECharacteristic* pCharacteristic, Status status, int code);
    void onSubscribe(NimBLECharacteristic* pCharacteristic, ble_gap_conn_desc* desc, uint16_t subValue);
};


class DescriptorCallbacks : public NimBLEDescriptorCallbacks {
  public:
	DescriptorCallbacks();
    void onWrite(NimBLEDescriptor* pDescriptor);
    void onRead(NimBLEDescriptor* pDescriptor);
};


#endif // ESP32_BLE_KEYBOARD_NIMBLE_CALLBACKS_H
