#include <TinyGPS++.h>
#include "esp_config.h"

TinyGPSPlus gps;

void setup(){
  Serial.begin(115200);
  Serial1.begin(9600);
}

void loop(){
  recvGPSData();

  //Serial.println("Test");

  debug_print("Hello");
  delay(500);
}