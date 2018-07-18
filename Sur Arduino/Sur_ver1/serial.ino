void printMotorInitials (byte s_m) {
  Serial.print ("Motor ");
  Serial.print (s_m);
  Serial.print (" dirMotor ");
  Serial.print (dirMotor [s_m]);
  Serial.print (" stepTime ");
  Serial.print (stepMotorTime [s_m]);
  Serial.print (" run ");
  Serial.print (runMotor [s_m]);
  Serial.print (" timeTarget ");
  Serial.println (stepTimeTarget [s_m]);
}

void printSensors () {
  Serial.print ("S1 ");
  Serial.print (lecture1);
  Serial.print (" S2 ");
  Serial.println (lecture2);
}

void printCompassPins ()
{

}

void printReceivedBTValues () {
  Serial.println ();
  Serial.print ("R ");
  Serial.println (rValueBT);
  Serial.println ();

  delay (100);
  Serial2.print ("R: ");
  Serial2.print (rValueBT);
  delay (100);
}

void printMenu () {
  Serial.println ("Menu");
  Serial.println ("0 Menu");
  Serial.println ("1 test motors");
  Serial.println ("2 begin sensor");
  Serial.println ("3 check if sensor calibrated");
  Serial.println ("4 calibrate compass disk");
  Serial.println ("5 run");
  Serial.println ("6 tense");
  Serial.println ("7 loose");
  delay (100);
}

void printMenuBT () {
  Serial2.println ("Menu");
  Serial2.println ("0 Menu");
  Serial2.println ("1 test motors");
  Serial2.println ("2 begin sensor");
  Serial2.println ("3 check if sensor calibrated");
  Serial2.println ("4 calibrate compass disk");
  Serial2.println ("5 run");
  Serial2.println ("6 tense");
  Serial2.println ("7 loose");
  delay (100);
}

