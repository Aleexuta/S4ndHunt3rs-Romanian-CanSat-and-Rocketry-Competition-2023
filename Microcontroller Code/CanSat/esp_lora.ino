uint32_t packetCounter = 0;
uint8_t hash = 0xFF;

void loraSetup()
{
  
  debug_println("LoRa Initialising...");

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);

  while (!LoRa.begin(866E6)) {
    debug_print(".");
    delay(500);
  }

  LoRa.setSyncWord(0xF3);
  debug_println("LoRa Initializing OK!")
}

void sendLoraData()
{
  
  //Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(packetCounter++);
  LoRa.print(":");

  LoRa.print(ahtTemp, 2);
  LoRa.print(" ");
  LoRa.print(ahtHum, 2);
  LoRa.print(":");

  LoRa.print(bmpTemp, 2);
  LoRa.print(" ");
  LoRa.print(bmpPres, 2);
  LoRa.print(" ");
  LoRa.print(bmpAlt, 2);
  LoRa.print(":");

  LoRa.print(mpuAX, 2);
  LoRa.print(" ");
  LoRa.print(mpuAY, 2);
  LoRa.print(" ");
  LoRa.print(mpuAZ, 2);
  LoRa.print(" ");
  LoRa.print(mpuGX, 2);
  LoRa.print(" ");
  LoRa.print(mpuGY, 2);
  LoRa.print(" ");
  LoRa.print(mpuGZ, 2);
  LoRa.print(" ");
  LoRa.print(mpuTemp, 2);
  LoRa.print(":");

  LoRa.print(gpsLat, 6);
  LoRa.print(" ");
  LoRa.print(gpsLong, 6);
  LoRa.print(" ");
  LoRa.print(gpsSpeed, 2);
  LoRa.print(" ");
  LoRa.print(gpsAlt, 2);
  LoRa.print(":");

  LoRa.print(mqData, 2);
  LoRa.print(":");

  LoRa.print(hash);
  
  LoRa.endPacket();
}