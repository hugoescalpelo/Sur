byte readAll () {
  timeNow = micros ();
  if (timeNow - sensorTime > SENSOR_SAMPLE_TIME) {
    addSensorReading (analogRead (PIN_S1));
    checkEventRing ();
    sensorTime += SENSOR_SAMPLE_TIME;
  }
  printSensors ();
}

void addSensorReading (int val) {
  for (int i_r = RING_LENGTH - 1; i_r > 0; i_r--) {
    sensorRing [i_r] = sensorRing [i_r - 1];
  }
  sensorRing [0] = val;
}

void checkEventRing () {
  int ringLengthHelper = RING_LENGTH -1;
  int lectureA = 0;
  int lectureB = 0;
  byte response;
  for (int i_ch = 0; i_ch < ringLengthHelper; i_ch++) {
    lectureA = sensorRing [i_ch];
    lectureB = sensorRing [i_ch + 1];
    if (lectureA != lectureB) {
      markOne++;
      if (markOne == 1) {
        pointOne = i_ch;
      }
      else {
        pointTwo = i_ch;
      }
    }    
  }
  if (markOne == 0) {
    response = 0;
  }
  if (markOne == 1) {
    response = 1;
  }
  else if (markOne ==2)
  {
    isTrascient = (pointTwo - pointOne) * SENSOR_SAMPLE_TIME;
    if (isTrascient < TRASCIENT_TIME_UP && isTrascient > TRASCIENT_TIME_DOWN) {
      response = 2;
    }
  }
  if (lastResponse != response) {
    lastResponse = response;
    return (response);
  }
}

