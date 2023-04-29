double mqData;
extern double ahtTemp;
extern double ahtHum;

float rzero;
float correctedRZero;
float resistance;
float ppm;
double correctedPPM;

void mqCalibrate()
{
  rzero = mq135_sensor.getRZero();
  correctedRZero = mq135_sensor.getCorrectedRZero(ahtTemp, ahtHum);
  resistance = mq135_sensor.getResistance();
  ppm = mq135_sensor.getPPM();
  correctedPPM = (double)mq135_sensor.getCorrectedPPM(ahtTemp, ahtHum);

}

void recvMQData()
{
  mqCalibrate();

  debug_print("MQ135 RZero: ");
  debug_print(rzero);
  debug_print("\t Corrected RZero: ");
  debug_print(correctedRZero);
  debug_print("\t Resistance: ");
  debug_print(resistance);
  debug_print("\t PPM: ");
  debug_print(ppm);
  debug_print("\t Corrected PPM: ");
  debug_print(correctedPPM);
  debug_println("ppm");
  mqData = correctedPPM;

}