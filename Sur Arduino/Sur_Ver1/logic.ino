void setInitialConditions (){
  digitalWrite (DIR_1, LOW);
  digitalWrite (STEP_1, LOW);
}

void testSequence (){
  setMotor (LEFT_MOTOR, LEFT_DIR, TIME_TESTEPS, ON);
  int testSteps = TEST_STEPS;
  while (testSteps > 0){
    runAllTest ();
  }
}

