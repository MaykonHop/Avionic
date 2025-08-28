#ifndef MANAGEMENT_TRANSMISSION_H
#define MANAGEMENT_TRANSMISSION_H

#include <HardwareSerial.h>
#include "management_SD.h"

// Defições do LoRa
#define LORA_RX 27 // Pino 26 do ESP32 conectado ao TX do LoRa
#define LORA_TX 26 // Pino 27 do ESP32 conectado ao RX do LoRa
#define LORA_M0 25 // Pino 25 do ESP32 conectado ao M0 do LoRa
#define LORA_M1 33 // Pino 33 do ESP32 conectado ao M1 do LoRa

size_t LoraBroadcastTransmit(phobos_data_t* TransmitData, HardwareSerial *loraSerial);

size_t LoraBroadcastReceive(phobos_data_t* ReceiveData, HardwareSerial *loraSerial);

#endif