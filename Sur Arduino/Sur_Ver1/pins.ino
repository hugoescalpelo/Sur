void setPinModes () {
  //Motor left
  pinMode (DIR_1, OUTPUT);
  pinMode (STEP_1, OUTPUT);
  //Motor Right
  pinMode (DIR_2, OUTPUT);
  pinMode (STEP_2, OUTPUT);
  //Motor Compass
  pinMode (COMPASS_PIN [0], OUTPUT);
  pinMode (COMPASS_PIN [1], OUTPUT);
  pinMode (COMPASS_PIN [2], OUTPUT);
  pinMode (COMPASS_PIN [3], OUTPUT);
}

