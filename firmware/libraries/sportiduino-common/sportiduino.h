#ifndef SPORTIDUINO_H
#define SPORTIDUINO_H

#include <Arduino.h>
#include "rfid.h"

#define START_STATION_NUM         240
#define FINISH_STATION_NUM        245
#define CHECK_STATION_NUM         248
#define CLEAR_STATION_NUM         249

#define MASTER_CARD_GET_INFO        249
#define MASTER_CARD_SET_TIME        250
#define MASTER_CARD_SET_NUMBER      251
#define MASTER_CARD_SLEEP           252
#define MASTER_CARD_READ_DUMP       253
#define MASTER_CARD_CONFIG          254

#define SERIAL_PACKET_SIZE        32

/**
 * Writes data with a majority backup in three cells of EEPROM
 */
void majEepromWrite (uint16_t adr, uint8_t val);

/**
 * Reads data with a majority backup from EEPROM
 */
uint8_t majEepromRead(uint16_t adr);

/**
 * Turn on led and buzzer for given ms n times
 * @param freq the frequency of your buzzer if you have solded the buzzer without a generator else 0
 */
void beep_w(const uint8_t ledPin, const uint8_t buzPin, uint16_t freq, uint16_t ms, uint8_t n);

bool uint32ToByteArray(uint32_t value, byte *byteArray);
uint32_t byteArrayToUint32(byte *byteArray);

class SerialProtocol {
public:
    void init(uint8_t _startByte);
    void start(uint8_t code);
    void add(uint8_t dataByte);
    void send();
    int8_t read(uint8_t *code, uint8_t *buffer, uint8_t *dataSize);

private:
    uint8_t checkSum(uint8_t *buffer, uint8_t dataSize);

    uint8_t startByte = 0;
    uint8_t serialBuffer[SERIAL_PACKET_SIZE];
    uint8_t serialDataPos = 3;
    uint8_t serialPacketCount = 0;
};

#endif
