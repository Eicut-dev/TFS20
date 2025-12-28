#include <TFS20.h>

/* This project was developed by EiCUT. */

#include "TFS20.h"

#define BAUDRATE 115200

// Use Serial1 for module (Pin 0 RX, Pin 1 TX)
TFS20 lidar(Serial1);

void setup() {
  Serial.begin(BAUDRATE);
  lidar.begin(BAUDRATE);

  Serial.println("TFS20 test start...");

  if (!lidar.checkModule(500)) {
    Serial.println("ERROR: Module not responding");
    while (1);
  }

  Serial.println("Module OK");
  lidar.startContinuous();
  Serial.println("Continuous mode started");
}

void loop() {
  uint16_t distance, strength, tempRaw;

  if (lidar.readData(distance, strength, tempRaw)) {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" | Strength: ");
    Serial.print(strength);
    Serial.print(" | Temp raw: ");
    Serial.println(tempRaw);
  }
}
