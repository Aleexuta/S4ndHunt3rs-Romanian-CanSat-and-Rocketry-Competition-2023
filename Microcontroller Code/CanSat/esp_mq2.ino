double mqData;

void recvMQData()
{
  mqData = analogRead(MQ_PIN);
  debug_print("Voltage mq-2: ");
  debug_println(mqData);
}