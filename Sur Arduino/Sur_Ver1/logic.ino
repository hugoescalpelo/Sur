void setInitialConditions (){
  digitalWrite (DIR_1, LOW);
  digitalWrite (STEP_1, LOW);
  digitalWrite (DIR_2, LOW);
  digitalWrite (STEP_2, LOW);
}

void testSequence (){
  setMotor (LEFT_MOTOR, LEFT_DIR, TIME_TESTEPS, ON);
  testSteps = TEST_STEPS;
  while (testSteps > 0){
    runAllTest ();
  }
  stopAll ();
  delay (1000);

  setMotor (RIGHT_MOTOR, LEFT_DIR, TIME_TESTEPS, ON);
  testSteps = TEST_STEPS;
  while (testSteps > 0){
    runAllTest ();
  }
  stopAll ();
  delay (1000);

  
}

