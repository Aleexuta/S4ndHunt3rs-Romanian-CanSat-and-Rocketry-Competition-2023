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
  debug_print("Acceleration X: ");
  debug_print(mpuAX);
  debug_print(", Y: ");
  debug_print(mpuAY);
  debug_print(", Z: ");
  debug_print(mpuAZ);
  debug_println(" m/s^2");

  mpuGX = g.gyro.x;
  mpuGY = g.gyro.y;
  mpuGZ = g.gyro.z;

  debug_print("Rotation X: ");
  debug_print(mpuGX);
  debug_print(", Y: ");
  debug_print(mpuGY);
  debug_print(", Z: ");
  debug_print(mpuGZ);
  debug_println(" rad/s");

  mpuTemp = temp.temperature;
  debug_print("Temperature: ");
  debug_print(mpuTemp);
  debug_println(" degC");
}