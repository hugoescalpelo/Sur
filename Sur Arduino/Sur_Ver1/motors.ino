void setMotor (byte nMotor, bool bDir, int tStep, bool activeMotor) {
  //Set up inherited values for a motor
  dirMotor [nMotor] = bDir;
  stepMotorTime [nMotor] = tStep;
  runMotor [nMotor] = activeMotor;
  stepTimeTarget [nMotor] = tStep + micros ();
  printMotorInitials (nMotor);
}

void runAllTest ()
{
  timeNow = micros ();
  int i_run = LEFT_MOTOR;
  if (timeNow > stepTimeTarget [LEFT_MOTOR] && runMotor [LEFT_MOTOR]) {
    levelMotor [LEFT_MOTOR] = !levelMotor[LEFT_MOTOR];
    stepTimeTarget [LEFT_MOTOR] += stepMotorTime [LEFT_MOTOR];
    testSteps--;
  }
  if (timeNow > stepTimeTarget [RIGHT_MOTOR] && runMotor [RIGHT_MOTOR]) {
    levelMotor [RIGHT_MOTOR] = !levelMotor[RIGHT_MOTOR];
    stepTimeTarget [RIGHT_MOTOR] += stepMotorTime [RIGHT_MOTOR];
    testSteps--;
  }
  if (timeNow > stepTimeTarget [COMPASS_MOTOR] && runMotor [COMPASS_MOTOR]) {
    //levelMotor [COMPASS_MOTOR] = !levelMotor[COMPASS_MOTOR];
    compassDrive ();
    stepTimeTarget [COMPASS_MOTOR] += stepMotorTime [COMPASS_MOTOR];
    testSteps--;
  }

  driveAll ();
}

void driveAll () {
  digitalWrite (STEP_1, levelMotor [LEFT_MOTOR]&runMotor [LEFT_MOTOR]);
  digitalWrite (STEP_2, levelMotor [RIGHT_MOTOR]&runMotor [RIGHT_MOTOR]);
  compassStep ();
}

void stopAll () {
  runMotor [LEFT_MOTOR] = OFF;
  runMotor [RIGHT_MOTOR] = OFF;
  runMotor [COMPASS_MOTOR] = OFF;
}

void compassDrive () {
  if (dirMotor [COMPASS_MOTOR] == LEFT_DIR) {
    compassSequence++;
  }
  else {
    compassSequence--;
  }
  compassSequence = compassSequence % 4;
}

void compassStep () {

  digitalWrite (COMPASS_PIN [0], LOW);
  digitalWrite (COMPASS_PIN [1], LOW);
  digitalWrite (COMPASS_PIN [2], LOW);
  digitalWrite (COMPASS_PIN [3], LOW);

  digitalWrite (COMPASS_PIN [compassSequence], HIGH&runMotor [COMPASS_MOTOR]);
}
