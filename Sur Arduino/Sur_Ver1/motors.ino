void setMotor (byte nMotor, bool bDir, long tStep, bool activeMotor) {
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
  digitalWrite (DIR_1, dirMotor [LEFT_MOTOR]);
  digitalWrite (DIR_2, dirMotor [LEFT_MOTOR]);
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
  bool passArray [] = {0, 0, 0, 0};
  passArray [compassSequence] = ON;
  //  digitalWrite (COMPASS_PIN [0], LOW);
  //  digitalWrite (COMPASS_PIN [1], LOW);
  //  digitalWrite (COMPASS_PIN [2], LOW);
  //  digitalWrite (COMPASS_PIN [3], LOW);
  //  digitalWrite (COMPASS_PIN [compassSequence], HIGH & runMotor [COMPASS_MOTOR]);

  digitalWrite (COMPASS_PIN [0], passArray [0]);
  digitalWrite (COMPASS_PIN [1], passArray [1]);
  digitalWrite (COMPASS_PIN [2], passArray [2]);
  digitalWrite (COMPASS_PIN [3], passArray [3]);
}

void motorDirective () {
  if (degreesLeft < threshold ) {
    closeEnoughLeft = OFF;
    closeEnoughRight = OFF;
    closeEnoughCompass = ON;
  }
  else if (degreesLeft > threshold && diffference > 0) {
    closeEnoughLeft = ON;
    closeEnoughRight = ON;
    closeEnoughCompass = ON;
    workingDirLeft = LEFT_DIR;
    workingDirRight = RIGHT_DIR;
  }
  else if (degreesLeft > threshold && diffference < 0) {
    closeEnoughLeft = ON;
    closeEnoughRight = ON;
    closeEnoughCompass = ON;
    workingDirLeft = RIGHT_DIR;
    workingDirRight = LEFT_DIR;
  }

  setMotor (LEFT_MOTOR, workingDirLeft, workingMotorTimeStep, closeEnoughLeft);
  setMotor (RIGHT_MOTOR, workingDirRight, workingMotorTimeStep, closeEnoughRight);
  setMotor (COMPASS_MOTOR, compassDirection, workingCompassTimeStep, closeEnoughCompass);
}

void runAll ()
{
  timeNow = micros ();
  int i_run = LEFT_MOTOR;
  if (timeNow > stepTimeTarget [LEFT_MOTOR] && runMotor [LEFT_MOTOR]) {
    levelMotor [LEFT_MOTOR] = !levelMotor[LEFT_MOTOR];
    stepTimeTarget [LEFT_MOTOR] += stepMotorTime [LEFT_MOTOR];
    stepRegistry [LEFT_MOTOR]++;
  }
  if (timeNow > stepTimeTarget [RIGHT_MOTOR] && runMotor [RIGHT_MOTOR]) {
    levelMotor [RIGHT_MOTOR] = !levelMotor[RIGHT_MOTOR];
    stepTimeTarget [RIGHT_MOTOR] += stepMotorTime [RIGHT_MOTOR];
    stepRegistry [RIGHT_MOTOR]++;
  }
  if (timeNow > stepTimeTarget [COMPASS_MOTOR] && runMotor [COMPASS_MOTOR]) {
    //levelMotor [COMPASS_MOTOR] = !levelMotor[COMPASS_MOTOR];
    compassDrive ();
    stepTimeTarget [COMPASS_MOTOR] += stepMotorTime [COMPASS_MOTOR];
    stepRegistry [COMPASS_MOTOR]++;
  }

  driveAll ();
}
