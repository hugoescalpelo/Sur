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
    buffBT = rValueBT.toInt ();
    if (buffBT == 1501) {
      Serial2.println ("Welcome");
      delay (1000);
      handShake = 1;
    }
  }
}

void clean () {
  rValueBT = 'null';//A null value to prevent missreadings
  buffBT= 200; //An off the limits value to prevent missfunction
}

