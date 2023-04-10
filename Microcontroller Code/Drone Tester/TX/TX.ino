#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver;
#define BUTTON_PIN 2
int counter = 0;

void setup() {
  rf_driver.init();
  Serial.begin(9600);
  Serial.println("Hello TX");
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == HIGH) {
    Serial.print("TX ");
    Serial.println(counter++);
    char msg[1] = "1";
    rf_driver.send((uint8_t)* msg, 1);
    rf_driver.waitPacketSent();
    delay(100);
  }
  buttonState = LOW;
}
