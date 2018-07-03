void beginOrientationSensor () {
  if (!bno.begin ()) {
    Serial.println ("Check Sensor BNO055");
  }
  delay (1000);

  int8_t temp = bno.getTemp ();
  Serial.print ("Temperature ");
  Serial.print (temp);
  Serial.println ("°C");

  bno.setExtCrystalUse (true);

  AOSensorTime = millis () + BNO055_SAMPLERATE_DELAY_MS;

  Serial.println ("Sensor started. Calibrate");
}

void readAbsoluteOrientationSensor () {
  timeNow = millis ();
  if (timeNow > AOSensorTime) {
    //Get values
    imu::Vector <3> euler = bno.getVector (Adafruit_BNO055::VECTOR_EULER);

    Serial.print ("X: ");
    Serial.print (euler.x ());
    Serial.print ("\t\t");

    //Calibration routine
    uint8_t system, gyro, accel, mag = 0;
    bno.getCalibration (&system, &gyro, &accel, &mag);
    Serial.print ("Mag= ");
    Serial.print (mag, DEC);

    AOSensorTime += BNO055_SAMPLERATE_DELAY_MS;
  }
}

