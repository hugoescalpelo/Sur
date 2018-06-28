void setInitialConditions ()
{
  digitalWrite (dir1, LOW);
  digitalWrite (dir2, LOW);
  digitalWrite (dir3, LOW);
  digitalWrite (step1, LOW);
  digitalWrite (step2, LOW);
  digitalWrite (step3, LOW);
}

void testSequence ()
{
  setMotor (1, 0, 2000);//Set motor conditions: [motor number],[Left 1 - Right 0], [microseconds per step]
  activateMotor (1, 0, 0);//Flag a motor as active 1, inactive 0
  while (testSteps > 0)//Count steps
  {
    runAll ();//run all sequence
    testSteps--;//Decrease steps
  }
  setMotor (1, 1, 2000);
  activateMotor (1, 0, 0);
  while (testSteps > 0)
  {
    runAll ();
    testSteps--;
  }
}

