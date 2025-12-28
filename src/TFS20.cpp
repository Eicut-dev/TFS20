/* This project was developed by EiCUT. */


#include "TFS20.h"

// Commands
static uint8_t CMD_CHECK[] = {0x5A, 0x04, 0x01, 0x5F};
static uint8_t CMD_START[] = {0x5A, 0x04, 0x02, 0x60};

TFS20::TFS20(HardwareSerial &uart) : serial(uart) {}

void TFS20::begin(uint32_t baudrate) {
  serial.begin(baudrate);
}

uint8_t TFS20::calcChecksum(uint8_t *data, uint8_t len) {
  uint16_t sum = 0;
  for (uint8_t i = 0; i < len; i++) {
    sum += data[i];
  }
  return (uint8_t)(sum & 0xFF);
}

bool TFS20::checkModule(uint32_t timeoutMs) {
  serial.write(CMD_CHECK, sizeof(CMD_CHECK));

  uint32_t start = millis();
  while (millis() - start < timeoutMs) {
    if (serial.available()) {
      return true;  // Any response is valid
    }
  }
  return false;
}

void TFS20::startContinuous() {
  while (serial.available()) serial.read(); // clear buffer
  serial.write(CMD_START, sizeof(CMD_START));
}

bool TFS20::readData(uint16_t &distance, uint16_t &strength, uint16_t &tempRaw) {
  uint8_t buf[9];

  if (serial.available() >= 9) {
    if (serial.read() == 0x59 && serial.read() == 0x59) {

      buf[0] = 0x59;
      buf[1] = 0x59;

      for (int i = 2; i < 9; i++) {
        buf[i] = serial.read();
      }

      // Check checksum
      if (calcChecksum(buf, 8) != buf[8]) {
        return false;
      }

      distance = buf[2] | (buf[3] << 8);
      strength = buf[4] | (buf[5] << 8);
      tempRaw  = buf[6] | (buf[7] << 8);

      // Strength validation
      if (strength >= 65535 || strength < 100) {
        return false;
      }

      return true;
    }
  }
  return false;
}
