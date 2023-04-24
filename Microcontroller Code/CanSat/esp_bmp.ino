double bmpTemp;
double bmpPres;
double bmpAlt;

void recvBMPData()
{
  if (bmp.takeForcedMeasurement()) {
    // can now print out the new measurements
    Serial.print(F("Temperature = "));
    bmpTemp = bmp.readTemperature();
    Serial.print(bmpTemp);
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    bmpPres = bmp.readPressure();
    Serial.print(bmpPres);
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    bmpAlt = bmp.readAltitude(1013.25);
    Serial.print(bmpAlt); /* Adjusted to local forecast! */
    Serial.println(" m");

    Serial.println();
    delay(2000);
  } else {
    Serial.println("Forced measurement failed!");
  }
}