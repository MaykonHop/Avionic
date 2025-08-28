#include "management_transmission.h"

size_t LoraBroadcastTransmit(phobos_data_t *TransmitData, HardwareSerial *loraSerial) {
    size_t sent = loraSerial->write((uint8_t*)TransmitData, sizeof(*TransmitData));
    return sent;
}

size_t LoraBroadcastReceive(phobos_data_t *ReceiveData, HardwareSerial *loraSerial) {
    loraSerial->readBytes((uint8_t*)ReceiveData,sizeof(*ReceiveData));
    return sizeof(*ReceiveData);
}