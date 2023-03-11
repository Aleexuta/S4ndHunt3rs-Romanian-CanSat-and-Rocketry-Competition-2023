#include <TinyGPS++.h>
#include <Wire.h>
#include <AHTxx.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "esp_config.h"

AHTxx aht10(AHTXX_ADDRESS_X38, AHT1x_SENSOR);  //sensor address, sensor type
TinyGPSPlus gps;
Adafruit_BMP280 bmp;
Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
  Wire.begin();

  while (aht10.begin() != true)  //for ESP-01 use aht10.begin(0, 2);
  {
    Serial.println(F("AHT1x not connected or fail to load calibration coefficient"));  //(F()) save string to flash & keeps dynamic memory free

    delay(5000);
  }
  //i2cScanner();
  if (!bmp.begin(BMP280_ADDRESS_ALT)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                     "try a different address!"));
    while (1) delay(10);
  }
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_FORCED,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
   mpu.setGyroRange(MPU6050_RANGE_500_DEG);
   mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
   mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  

  //Serial.println("Test");

  //debug_print("Hello");
  //delay(500);

  recvGPSData();
  recvAHTData();
  recvBMPData();
  recvMPUData();
  //i2cScanner();
  //Serial.println("");
  //Serial.println("");
  //Serial.println("");
}

void i2cScanner() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000);  // wait 5 seconds for next scan
}