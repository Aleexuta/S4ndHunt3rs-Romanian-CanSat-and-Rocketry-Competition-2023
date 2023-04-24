uint32_t packetCounter = 0;

void lora_setup()
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