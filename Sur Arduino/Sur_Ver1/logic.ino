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

  setMotor (COMPASS_MOTOR, LEFT_DIR, TIME_TESTEPS*3, ON);
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

  setMotor (COMPASS_MOTOR, RIGHT_DIR, TIME_TESTEPS*3, ON);
  testSteps = TEST_STEPS;
  while (testSteps > 0) {
    runAllTest ();
  }
  stopAll ();
  delay (IBWTT);
}


