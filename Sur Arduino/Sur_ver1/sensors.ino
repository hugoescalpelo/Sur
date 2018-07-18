bool readAll () {
  timeNow = micros ();
  if (timeNow - sensorTime > SENSOR_SAMPLE_TIME) {
    lecture2 = lecture1;
    lecture1 = analogRead (PIN_S1);
    sensorTime += SENSOR_SAMPLE_TIME;
    //printSensors ();
  }  
}




