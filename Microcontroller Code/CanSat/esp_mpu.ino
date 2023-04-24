double mpuAX, mpuAY, mpuAZ;
double mpuGX, mpuGY, mpuGZ;
double mpuTemp;

void recvMPUData()
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  mpuAX = a.acceleration.x;
  mpuAY = a.acceleration.y;
  mpuAZ = a.acceleration.z;

  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(mpuAX);
  Serial.print(", Y: ");
  Serial.print(mpuAY);
  Serial.print(", Z: ");
  Serial.print(mpuAZ);
  Serial.println(" m/s^2");

  mpuGX = g.gyro.x;
  mpuGY = g.gyro.y;
  mpuGZ = g.gyro.z;

  Serial.print("Rotation X: ");
  Serial.print(mpuGX);
  Serial.print(", Y: ");
  Serial.print(mpuGY);
  Serial.print(", Z: ");
  Serial.print(mpuGZ);
  Serial.println(" rad/s");

  mpuTemp = temp.temperature;
  Serial.print("Temperature: ");
  Serial.print(mpuTemp);
  Serial.println(" degC");
}