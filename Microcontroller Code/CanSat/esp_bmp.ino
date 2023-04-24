double bmpTemp;
double bmpPres;
double bmpAlt;

void recvBMPData()
{
  if (bmp.takeForcedMeasurement()) {
    // can now print out the new measurements
    debug_print("Temperature = ");
    bmpTemp = bmp.readTemperature();
    debug_print(bmpTemp);
    debug_println(" *C");

    debug_print("Pressure = ");
    bmpPres = bmp.readPressure();
    Serial.print(bmpPres);
    debug_println(" Pa");

    debug_print("Approx altitude = ");
    bmpAlt = bmp.readAltitude(1013.25);
    debug_print(bmpAlt); /* Adjusted to local forecast! */
    debug_println(" m");
    
    delay(2000);
  } else {
    debug_println("Forced measurement failed!");
  }
}