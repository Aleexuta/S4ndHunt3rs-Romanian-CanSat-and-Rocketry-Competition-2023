#include <TinyGPS++.h>
#include <Wire.h>
#include <AHTxx.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>
#include <LoRa.h>
#include <MQ135.h>

#include "esp_config.h"

#define ss 5
#define rst 14
#define dio0 2

#define MQ_PIN 35

AHTxx aht10(AHTXX_ADDRESS_X38, AHT1x_SENSOR);
TinyGPSPlus gps;
Adafruit_BMP280 bmp;
Adafruit_MPU6050 mpu;
MQ135 mq135_sensor(MQ_PIN);

extern double ahtTemp;
extern double ahtHum;
extern double bmpTemp;
extern double bmpPres;
extern double bmpAlt;
extern double mpuAX, mpuAY, mpuAZ;
extern double mpuGX, mpuGY, mpuGZ;
extern double mpuTemp;
extern double gpsLat;
extern double gpsLong;
extern double gpsSpeed;
extern double gpsAlt;
extern double mqData;
extern uint32_t packetCounter;

void setup() {

#if DEBUG
  // Serial communication to PC for debugging
  Serial.begin(115200);
#endif
  // Serial communication to ESP CAM and GPS
  Serial2.begin(9600);
  Wire.begin();

  loraSetup();
  ahtSetup();
  bmpSetup();
  mpuSetup();

}

void loop() {

  recvGPSData();
  recvAHTData();
  recvBMPData();
  recvMPUData();
  recvMQData();

  sendLoraData();
}