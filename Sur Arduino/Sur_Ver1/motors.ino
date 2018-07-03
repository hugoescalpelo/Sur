void setMotor (byte nMotor, bool bDir, int tStep, bool activeMotor){
  //Set up inherited values for a motor
  dirMotor [nMotor] = bDir;
  stepMotorTime [nMotor] = tStep;
  runMotor [nMotor] = activeMotor;
  stepTimeTarget [nMotor] = tStep + micros ();
}

void runAllTest ()
{
  timeNow = micros ();
  int i_run = LEFT_MOTOR;
  if (timeNow > timeMotor [LEFT_MOTOR]){
    levelMotor [LEFT_MOTOR] = !levelMotor[LEFT_MOTOR];
    stepMotorTime [LEFT_MOTOR] += stepMotorTime [LEFT_MOTOR];
    testSteps--;
  }

  driveAll ();
}

void driveAll (){
  digitalWrite (STEP_1, levelMotor [LEFT_MOTOR]);
}

