float ahtValue;  //to store T/RH result

void recvAHTData() {
  ahtValue = aht10.readTemperature();
  Serial.println();

  ahtValue = aht10.readTemperature();  //read 6-bytes via I2C, takes 80 milliseconds

  Serial.print(F("Temperature...: "));

  if (ahtValue != AHTXX_ERROR)  //AHTXX_ERROR = 255, library returns 255 if error occurs
  {
    Serial.print(ahtValue);
    Serial.println(F(" +-0.3C"));
  } else {
    printStatus();  //print temperature command status

    if (aht10.softReset() == true) Serial.println(F("reset success"));  //as the last chance to make it alive
    else Serial.println(F("reset failed"));
  }

  delay(2000);  //measurement with high frequency leads to heating of the sensor, see NOTE

  ahtValue = aht10.readHumidity();  //read another 6-bytes via I2C, takes 80 milliseconds

  Serial.print(F("Humidity......: "));

  if (ahtValue != AHTXX_ERROR)  //AHTXX_ERROR = 255, library returns 255 if error occurs
  {
    Serial.print(ahtValue);
    Serial.println(F(" +-2%"));
  } else {
    printStatus();  //print humidity command status
  }

  delay(2000);  //measurement with high frequency leads to heating of the sensor, see NOTE
}

void printStatus()
{
  switch (aht10.getStatus())
  {
    case AHTXX_NO_ERROR:
      Serial.println(F("no error"));
      break;

    case AHTXX_BUSY_ERROR:
      Serial.println(F("sensor busy, increase polling time"));
      break;

    case AHTXX_ACK_ERROR:
      Serial.println(F("sensor didn't return ACK, not connected, broken, long wires (reduce speed), bus locked by slave (increase stretch limit)"));
      break;

    case AHTXX_DATA_ERROR:
      Serial.println(F("received data smaller than expected, not connected, broken, long wires (reduce speed), bus locked by slave (increase stretch limit)"));
      break;

    case AHTXX_CRC8_ERROR:
      Serial.println(F("computed CRC8 not match received CRC8, this feature supported only by AHT2x sensors"));
      break;

    default:
      Serial.println(F("unknown status"));    
      break;
  }
}