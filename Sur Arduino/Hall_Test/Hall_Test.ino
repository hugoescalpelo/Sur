int data1 = 0;

void setup() {
  Serial.begin (115200);
  // put your setup code here, to run once:

}

void loop() {
  data1 = analogRead (A1);
  Serial.println (data1);
  delay (100);
  // put your main code here, to run repeatedly:

}
