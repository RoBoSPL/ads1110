// custom_components/ads1110_sensor.h
#include "esphome.h"
#include <Wire.h>

class ADS1110Sensor : public PollingComponent, public Sensor {
 public:
  ADS1110Sensor() : PollingComponent(1000) {}

  void update() override {
    Wire.requestFrom(0x48, 3);
    if (Wire.available() == 3) {
      uint8_t highbyte = Wire.read();
      uint8_t lowbyte = Wire.read();
      uint8_t configRegister = Wire.read();
      int16_t raw_value = (highbyte << 8) | lowbyte;  // Fixed the parenthesis here
      float voltage = raw_value * 0.000125;
      publish_state(voltage);
    }
  }
};
