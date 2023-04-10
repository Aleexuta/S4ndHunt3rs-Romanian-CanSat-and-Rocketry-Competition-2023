#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver;

const int pwmPin = 4; // PWM output pin
const int pwmFrequency = 1000; // PWM frequency in Hz
const int pwmResolution = 8; // PWM resolution in bits (8-bit for Arduino Nano)

void setup() {
  rf_driver.init();
  Serial.begin(9600);
  Serial.println("Hello");
}

void loop() {
  uint8_t buffer[8];
  uint8_t len = sizeof(buffer);
  if (rf_driver.recv(buffer, &len)){
    Serial.println("Done");
    analogWrite(pwmPin, 0);
    delay(2000);
    analogWrite(pwmPin, 255);
    delay(2000);
  }
}
