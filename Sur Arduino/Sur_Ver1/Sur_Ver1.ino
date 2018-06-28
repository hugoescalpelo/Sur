/*
 * Ivan Abreu Studio.
 * 
 * 15/06/2018
 * 
 * This code controls a set of 3 stepper motors, 2 of them are
 * used to turn the head of the system host, the last one to
 * turn the needle of a big compass.
 * 
 * The target of this pieces is force the host to always see
 * to south and express it with a big model of a compass.
 * 
 * Changelog:
 * V0.1 First development
 * 
 * Team
 * Iván Abreu Ochoa
 * Malitzin Cortes
 * Beto Olguin
 * Hugo Vargas
 * 
 */

//Libraries

//Objects

//Constants
const int dir1 = 4;
const int step1 = 5;
const int dir2 = 6;
const int step2 = 7;
const int dir3 = 8;
const int step3 = 9;

//Variables
double timeNow (); //Tracks actual time in micros

void setup() 
{
  Serial.begin (2000000);//Serial monitor communication
  Serial.println ("Setting up");

  Serial2.begin (9600);//Bluetooth communication
  Serial2.println ("BT running on port tx/rx 2");

  setModes ();//Set the pin inputs and outputs
  setInitialConditions ();//Set the starting state of pins and things

  testSequence ();
  positionSensorBegin ();
  

  Serial2.println ("Test sequence finished");
  Serial.println ("Test sequence finished");

}

void loop() 
{
  timeNow = micros (); //Keep track of time instant
  runAll (); //An asynchronous sequens that checks the bit bang state of every stepper
  checkSerial ();//Look up for configuration changes and reports to serial monitor
  checkBluetooth ();//Look up for configuration changes and reports to Bluetooth
  // put your main code here, to run repeatedly:

}
