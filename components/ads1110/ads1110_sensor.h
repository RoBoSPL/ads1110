#include "esphome.h"
#include <Wire.h>

class ADS1110Sensor : public PollingComponent, public Sensor {
 public:
  ADS1110Sensor() : PollingComponent(1000) {}

  void setup() override {
    Wire.begin();
  }

  void update() override {
    Wire.requestFrom(0x48, 3);  // ADS1110 I2C address
    if (Wire.available() == 3) {
      uint8_t highbyte = Wire.read();
      uint8_t lowbyte = Wire.read();
      uint8_t configRegister = Wire.read();  // Read config register, but we can ignore it for now
      int16_t raw_value = (highbyte << 8) | lowbyte;
      float voltage = raw_value * 0.000125;  // Convert raw value to voltage
      publish_state(voltage);
    }
  }
};
