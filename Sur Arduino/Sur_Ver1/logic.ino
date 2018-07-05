void setInitialConditions () {
  digitalWrite (DIR_1, LOW);
  digitalWrite (STEP_1, LOW);
  digitalWrite (DIR_2, LOW);
  digitalWrite (STEP_2, LOW);
  digitalWrite (COMPASS_PIN [0], LOW);
  digitalWrite (COMPASS_PIN [1], LOW);
  digitalWrite (COMPASS_PIN [2], LOW);
  digitalWrite (COMPASS_PIN [3], LOW);
}

void testSequence () {
  setMotor (LEFT_MOTOR, LEFT_DIR, TIME_TESTEPS, ON);
  testSteps = TEST_STEPS;
  while (testSteps > 0) {
    runAllTest ();
  }
  stopAll ();
  delay (IBWTT);

  setMotor (RIGHT_MOTOR, LEFT_DIR, TIME_TESTEPS, ON);
  testSteps = TEST_STEPS;
  while (testSteps > 0) {
    runAllTest ();
  }
  stopAll ();
  delay (IBWTT);

  setMotor (COMPASS_MOTOR, LEFT_DIR, TIME_TESTEPS*4, ON);
  testSteps = TEST_STEPS;
  while (testSteps > 0) {
    runAllTest ();
  }
  stopAll ();
  delay (IBWTT);

  setMotor (LEFT_MOTOR, RIGHT_DIR, TIME_TESTEPS, ON);
  testSteps = TEST_STEPS;
  while (testSteps > 0) {
    runAllTest ();
  }
  stopAll ();
  delay (IBWTT);

  setMotor (RIGHT_MOTOR, RIGHT_DIR, TIME_TESTEPS, ON);
  testSteps = TEST_STEPS;
  while (testSteps > 0) {
    runAllTest ();
  }
  stopAll ();
  delay (IBWTT);

  setMotor (COMPASS_MOTOR, RIGHT_DIR, TIME_TESTEPS*4, ON);
  testSteps = TEST_STEPS;
  while (testSteps > 0) {
    runAllTest ();
  }
  stopAll ();
  delay (IBWTT);
}

void shortestWayToSouth () {
  diffference = 180 - heading;
  if (diffference < 0) {
    compassDirection = RIGHT_DIR;
  }
  else {
    compassDirection = LEFT_DIR;
  }
  degreesLeft = abs (diffference);
}

void setWorkingConditions () {
  workingCompassTimeStep = WORK_TIME_STEP_COMPASS;
  workingMotorTimeStep = WORK_TIME_STEP;
}

void calibrateCompassDisc () {
  stopAll ();
  setMotor (COMPASS_MOTOR, RIGHT_DIR, TIME_TESTEPS*4, ON);
  bool c_f = 0;
  Serial.println ("Looking for magnet");
  while (c_f != 1) {
    readAll ();
    runAll ();
    if (lecture1 > DETECT_S1) {
      c_f = 1;
    }
  }
  c_f = 0;
  lastCalibrationCounter = stepRegistry [COMPASS_MOTOR];
  while (calibrationCounter < HALL_DEBOUNCE) {
    lecture1 = analogRead (PIN_S1);
    runAll ();
    calibrationCounter++;//Check step counter, to add only at steps (remember the asynchronous mode)
  }
  while (c_f != 0) {
    readAll ();
    runAll ();
    calibrationCounter++;
    if (lecture1 > DETECT_S1) {
      c_f = 1;
    }
  }
  latestCalibrationCounter = stepRegistry [COMPASS_MOTOR];
  calibrationCounter = latestCalibrationCounter - lastCalibrationCounter;
  lastCalibrationCounter = stepRegistry [COMPASS_MOTOR];
  setMotor (COMPASS_MOTOR, LEFT_DIR, TIME_TESTEPS*4, ON);
  int i_compass = 0;
  while (latestCalibrationCounter - lastCalibrationCounter < calibrationCounter) {
    runAll ();
    latestCalibrationCounter = stepRegistry [COMPASS_MOTOR];
    
  }
}

