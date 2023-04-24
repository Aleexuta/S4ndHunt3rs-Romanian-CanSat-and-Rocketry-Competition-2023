float ahtValue;  //to store T/RH result
double ahtTemp;
double ahtHum;


void recvAHTData() {
  ahtValue = aht10.readTemperature();  //read 6-bytes via I2C, takes 80 milliseconds

  debug_print("Temperature...: ");

  if (ahtValue != AHTXX_ERROR)  //AHTXX_ERROR = 255, library returns 255 if error occurs
  {
    ahtTemp = ahtValue;

    debug_print(ahtValue);
    debug_print(" +-0.3C");

  } else {
    printStatus();  //print temperature command status

    if (aht10.softReset() == true)
    {
      debug_println("reset success");  //as the last chance to make it alive

    }
    else
      debug_println("reset failed");
  }

  delay(2000);  //measurement with high frequency leads to heating of the sensor, see NOTE

  ahtValue = aht10.readHumidity();  //read another 6-bytes via I2C, takes 80 milliseconds


  debug_print("Humidity......: ");


  if (ahtValue != AHTXX_ERROR)  //AHTXX_ERROR = 255, library returns 255 if error occurs
  {
    ahtHum = ahtValue;

    debug_print(ahtValue);
    debug_println(" +-2%");

  } else {
    printStatus();  //print humidity command status
  }

  delay(2000);  //measurement with high frequency leads to heating of the sensor, see NOTE
}

void ahtSetup(){

  while (aht10.begin() != true)  //for ESP-01 use aht10.begin(0, 2);
  {
    debug_print("AHT1x not connected or fail to load calibration coefficient");  //(F()) save string to flash & keeps dynamic memory free
    delay(5000);
  }
}

void printStatus() {
  switch (aht10.getStatus()) {
    case AHTXX_NO_ERROR:
      debug_print("no error");
      break;

    case AHTXX_BUSY_ERROR:
      debug_print("sensor busy, increase polling time");
      break;

    case AHTXX_ACK_ERROR:
      debug_print("sensor didn't return ACK, not connected, broken, long wires (reduce speed), bus locked by slave (increase stretch limit)");
      break;

    case AHTXX_DATA_ERROR:
      debug_print("received data smaller than expected, not connected, broken, long wires (reduce speed), bus locked by slave (increase stretch limit)");
      break;

    case AHTXX_CRC8_ERROR:
      debug_print("computed CRC8 not match received CRC8, this feature supported only by AHT2x sensors");
      break;

    default:
      debug_print("unknown status");
      break;
  }
  debug_println("");
}