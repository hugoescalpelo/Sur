void setInitialConditions () {
  digitalWrite (DIR_1, LOW);
  digitalWrite (STEP_1, LOW);
  digitalWrite (DIR_2, LOW);
  digitalWrite (STEP_2, LOW);
  digitalWrite (COMPASS_PIN [0], LOW);
  digitalWrite (COMPASS_PIN [1], LOW);
  digitalWrite (COMPASS_PIN [2], LOW);
  digitalWrite (COMPASS_PIN [3], LOW);
  sensorTime = millis () + SENSOR_SAMPLE_TIME;
  lecture1 = 0;
  lecture2 = 1000;
  runSample = micros ();
}

void testSequence () {
  setMotor (LEFT_MOTOR, COUNTER_CLOCKWISE, TIME_TESTEPS, ON);
  testSteps = TEST_STEPS;
  while (testSteps > 0) {
    runAllTest ();
  }
  stopAll ();
  delay (IBWTT);

  setMotor (RIGHT_MOTOR, COUNTER_CLOCKWISE, TIME_TESTEPS, ON);
  testSteps = TEST_STEPS;
  while (testSteps > 0) {
    runAllTest ();
  }
  stopAll ();
  delay (IBWTT);

  setMotor (COMPASS_MOTOR, COUNTER_CLOCKWISE, TIME_TESTEPS * 2, ON);
  testSteps = TEST_STEPS;
  while (testSteps > 0) {
    runAllTest ();
  }
  stopAll ();
  delay (IBWTT);

  setMotor (LEFT_MOTOR, CLOCKWISE, TIME_TESTEPS, ON);
  testSteps = TEST_STEPS;
  while (testSteps > 0) {
    runAllTest ();
  }
  stopAll ();
  delay (IBWTT);

  setMotor (RIGHT_MOTOR, CLOCKWISE, TIME_TESTEPS, ON);
  testSteps = TEST_STEPS;
  while (testSteps > 0) {
    runAllTest ();
  }
  stopAll ();
  delay (IBWTT);

  setMotor (COMPASS_MOTOR, CLOCKWISE, TIME_TESTEPS * 2, ON);
  testSteps = TEST_STEPS;
  while (testSteps > 0) {
    runAllTest ();
  }
  stopAll ();
  delay (IBWTT);
}

void setWorkingConditions () {
  workingCompassTimeStep = WORK_TIME_STEP_COMPASS;
  workingMotorTimeStep = WORK_TIME_STEP;
}

void calibrateCompassDisc () {
  stopAll ();
  setMotor (COMPASS_MOTOR, COUNTER_CLOCKWISE, LOOKING_MAGNET_STEP_TIME, ON);
  bool c_f = 0;
  Serial.println ("Looking for magnet");
  readAll ();
  readAll ();
  while (c_f != 1) {
    runAll ();
    readAll ();
    if (lecture1 < 700 && lecture2 > 600) {
      c_f = 1;
    }
  }
  //printSensors ();
  Serial.println ("Magnet B found");
  c_f = 0;
  while (c_f != 1) {
    runAll ();
    readAll ();
    if (lecture1 > 700 && lecture2 < 600) {
      c_f = 1;
    }
  }
  //printSensors ();
  Serial.println ("Magnet A Found. Looking for steps period");

  c_f = 0;
  lastCalibrationCounter = stepRegistry [COMPASS_MOTOR];
  Serial.print ("StepRegistry a ");
  Serial.println (stepRegistry [COMPASS_MOTOR]);

  //printSensors ();

  //  while (calibrationCounter < HALL_DEBOUNCE) {
  //    lecture1 = analogRead (PIN_S1);
  //    runAll ();
  //  }

  while (c_f != 1) {
    runAll ();
    readAll ();
    if (lecture1 < 700 && lecture2 > 600) {
      c_f = 1;
    }
  }
  //printSensors ();
  Serial.println ("Magnet B found");
  c_f = 0;
  while (c_f != 1) {
    runAll ();
    readAll ();
    if (lecture1 > 700 && lecture2 < 600) {
      c_f = 1;
    }
  }
  //printSensors ();
  Serial.print ("StepRegistry b ");
  Serial.println (stepRegistry [COMPASS_MOTOR]);
  calibrationCounter = stepRegistry [COMPASS_MOTOR] - lastCalibrationCounter;
  Serial.print ("Steps per 360 degrees: ");
  Serial.println (calibrationCounter);

  setMotor (COMPASS_MOTOR, CLOCKWISE, WORK_TIME_STEP_COMPASS, ON);
  while (stepRegistry [COMPASS_MOTOR] != lastCalibrationCounter) {

    runAll ();
  }
  Serial.print ("StepRegistry b ");
  Serial.println (stepRegistry [COMPASS_MOTOR]);

  calibrationCounter = abs (calibrationCounter);
  stepsPerDegree = calibrationCounter / 360;

  needlePosition = 210;
  int initialDeviation = SOUTH_DEGREES - needlePosition;

  if (initialDeviation < 0) {
    setMotor (COMPASS_MOTOR, COUNTER_CLOCKWISE, LOOKING_MAGNET_STEP_TIME, ON);
    lastCalibrationCounter = stepRegistry [COMPASS_MOTOR] + (initialDeviation * stepsPerDegree);
  }
  else {
    setMotor (COMPASS_MOTOR, CLOCKWISE, LOOKING_MAGNET_STEP_TIME, ON);
  }

  while (stepRegistry [COMPASS_MOTOR] != lastCalibrationCounter) {

    runAll ();
  }
  needlePosition = 180;
  homeNeedle = stepRegistry [COMPASS_MOTOR];
  printNeedleStart ();
  delay (3000);


}

void searchSouth () {
  bool stopSearch = 0;
  while (stopSearch == 0) {
    readBT ();
    if (rValueBT.toInt () == 59) {
      stopSearch = 1;
    }
    else {
      if (timeNow > runSample) {
        readAbsoluteOrientationSensor ();
        shortestWayToSouth ();
        motorDirective ();
        compassFetch ();
        speedGradient ();
        //printNeedle ();
        runSample =  runSample + RUN_SAMPLE;
      }
      runAll ();
    }
  }
}

void shortestWayToSouth () {
  diffference = 180 - heading;
  diferenccce = heading - needlePosition;
  //////////////////////////////////////////change < if compass turns weird change first <
  if (diferenccce > 0 && diferenccce < 180) {
    compassDirection = COUNTER_CLOCKWISE;
  }
  else if (diferenccce > 181 && diferenccce -360) {
    compassDirection = CLOCKWISE;
  }
  else if (diferenccce < 0 && diferenccce > -180) {
    compassDirection = CLOCKWISE;
  }
  else if (diferenccce < -181 && diferenccce > -360) {
    compassDirection = COUNTER_CLOCKWISE;
  }
degreesLeft = abs (diffference);
}

void compassFetch () {
  needlePosition = abs ((180 + ((homeNeedle - stepRegistry [COMPASS_MOTOR]) / stepsPerDegree)) % 360);
  compassDegreesLeft = abs (needlePosition - heading);
}

void speedGradient () {
  workingMotorTimeStep = map (degreesLeft, -1, 361, 12000, 6000);
  workingCompassTimeStep = map (abs (diferenccce), -1, 361, 12000, 3000);  
}

