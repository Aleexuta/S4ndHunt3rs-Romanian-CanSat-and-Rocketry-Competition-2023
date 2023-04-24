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

void bmpSetup()
{
  
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
}