void readBT () {
  if (Serial2.available ()) {
    rValueBT = Serial2.readStringUntil ('\n');
    //printReceivedBTValues ();
  }

}

void waitHandShake () {
  //Wait for a recognizable value to keep going
  while (handShake == 0) {
    readBT ();
    buffGeneral = rValueBT.toInt ();
    if (buffGeneral == 1501) {
      testSequence ();
      handShake = 1;
    }
  }
}

void clean () {
  rValueBT = 'null';//A null value to prevent missreadings
  buffGeneral = 200; //An off the limits value to prevent missfunction
}

