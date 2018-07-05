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
  Serial.println (lecture1);
}

