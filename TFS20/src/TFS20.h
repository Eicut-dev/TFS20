/* This project was developed by EiCUT. */


#ifndef TFS20_H
#define TFS20_H

#include <Arduino.h>

class TFS20 {
public:
  TFS20(HardwareSerial &uart);

  void begin(uint32_t baudrate);
  bool checkModule(uint32_t timeoutMs);
  void startContinuous();

  bool readData(uint16_t &distance, uint16_t &strength, uint16_t &tempRaw);

private:
  HardwareSerial &serial;

  uint8_t calcChecksum(uint8_t *data, uint8_t len);
};

#endif
