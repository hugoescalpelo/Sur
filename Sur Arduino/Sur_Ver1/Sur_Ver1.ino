/*
   Ivan Abreu Studio.

   19/07/2018

   This code controls a set of 3 stepper motors, 2 of them are
   used to turn the head of the system host, the last one to
   turn the needle of a big compass.

   The target of this pieces is force the host to always see
   to south and express it with a big model of a compass.

   Changelog:
   V0.1 First development
   V0.2.1 Test sequence for L motor
   V0.2.2 Test for 3 motors single direction
   V0.3 Merge Absolute orientation sensor code
   V0.4 ShortestWay Added
   V0.5 Continuous Movement Added
   V0.6 Sensor compass calibration added
   V0.6.1 Compass Servo sequence fixed
   V0.6.2 Change direction sequence Added
   V0.6.3 Pull and push mirror movement in reducer steppers added
   V0.6.4 Bluetooth communication
   V0.7 Bluetooth Control
   V0.7.1 Bluetooth addons & Sensore lecture tested
   V0.7.2 Sensor sequence tested
   V0.7.3 Steps per degrees value added
   V0.7.4 Compass calibration tested
   V0.8 Compass & reducers behaviour tested. MPA reached
   V0.8.1 Gradient speed added
   V0.8.2 Loose-Tense sequence tested
   

   Team
   Iván Abreu Ochoa
   Malitzin Cortes
   Beto Olguin
   Hugo Vargas

*/

//Libraries
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

//Constants
const byte DIR_1 = 4;
const byte STEP_1 = 5;
const byte DIR_2 = 6;
const byte STEP_2 = 7;
const byte COMPASS_PIN [] = {8, 9, 10, 11};
const byte LEFT_MOTOR = 0;
const byte RIGHT_MOTOR = 1;
const byte COMPASS_MOTOR = 2;
const bool COUNTER_CLOCKWISE = 1;
const bool CLOCKWISE = 0;
const long TIME_TESTEPS = 1500;
const bool ON = 1;
const bool OFF = 0;
const long TEST_STEPS = 1500;
const int IBWTT = 250;//In Between Wait Test Time
const long WORK_TIME_STEP_COMPASS = 3000; //uSeconds
const long WORK_TIME_STEP = 4000; //uSeconds
const byte BASE_TH = 5; //Degrees
const int PIN_S1 = A2;
const int PIN_S2 = A3;
const int HALL_DEBOUNCE = 100;
const long SENSOR_SAMPLE_TIME = 200000;
const long LOOKING_MAGNET_STEP_TIME = 11000;
const int SOUTH_DEGREES = 180;
const long RUN_SAMPLE = 50000;
const long TENSE_LOOSE = 200;
const long LOOSE_TENSE_TIME_STEP = 8000;

#define BNO055_SAMPLERATE_DELAY_MS (100)

//Objects
Adafruit_BNO055 bno = Adafruit_BNO055();

//Variables
bool dirMotor [] = {0, 0, 0};
long stepMotorTime [] = {TIME_TESTEPS, TIME_TESTEPS, TIME_TESTEPS};
bool runMotor [] = {0, 0, 0};
long stepTimeTarget [] = {0, 0, 0};
long timeNow;
bool levelMotor [] = {0, 0, 0};
long testSteps;
byte compassSequence = 0;

long AOSensorTime;
int heading;
int diffference;
bool compassDirection;
int degreesLeft;
long workingCompassTimeStep, workingMotorTimeStep;
long workingDirLeft, workingDirRight;
byte threshold = BASE_TH;
bool closeEnoughCompass, closeEnoughLeft, closeEnoughRight;
int  calibrationCounter;
int lecture1, lecture2;
long stepRegistry [] = {0, 0, 0};
long lastCalibrationCounter;
byte i_sensorRing = 0;
long sensorTime;
bool handShake = 0;
String rValueBT;
int buffBT;
int buffMag;
int stepsPerDegree;
long runSample;
int needlePosition;
int homeNeedle;
int compassDegreesLeft;
int diferenccce;


void setup() {
  // Serial Monitor communication
  Serial.begin (2000000);
  Serial.println ("Setting up");

  Serial2.begin (9600);
  Serial2.println ("BT Started");

  setPinModes ();
  setInitialConditions ();

  //Serial.println ("Test Started");
  //testSequence ();
  //Serial.println ("Test Finished");

  //Wait for a recongizable number, only initialize when the
  //expected number is received

  Serial.println ("Waiting Handshake");
  delay (100);
  Serial2.println ("Enter Handshake");
  delay (100);
  waitHandShake ();
  Serial.println ("Hanshake Received");

  setWorkingConditions ();

  printMenu ();
  clean ();
}

void loop() {

  //Bluetooth configuration service. A menu accesable theough serial BT
  //that determines on-off functions mainly. Also let you choose a
  //manual calibration, test sequence and independently confivurations
  //of working parameters...

  readBT ();
  buffBT = rValueBT.toInt ();
  switch (buffBT) {
    case 0:
      printMenu ();
      clean ();
      break;
    case 1:
      Serial.println ("Test sequence in progreess");
      Serial2.println ("Test sequence in progress");
      testSequence ();
      clean ();
      Serial.println ("Test sequence done");
      Serial2.println ("Test Sequence Done");
      break;
    case 2:
      Serial.println ("Begin Orientation Sensor");
      Serial2.println ("Begin Orientation Sensor");
      beginOrientationSensor ();
      clean ();
      Serial.println ("Absolute Orientation Sensor started");
      Serial2.println ("Absolute Orientation Sensor started");
      break;
    case 3:
      Serial.println ("Calibrating Absolute Orientation Sensor");
      Serial2.println ("Calibrating Absolute Orientation Sensor");
      runUntilCalibrate ();
      Serial.println (buffMag);
      clean ();
      Serial.println ("Compass Absolute Orientation Sensor calibrated");
      Serial2.println ("Compass Absolute Orientation Sensor calibrated");
      break;
    case 4:
    Serial.println ("Calibrating compass");
    Serial2.println ("Calibrating compass");
      calibrateCompassDisc ();
      clean ();
      Serial.println ("Compass calibrated");
      Serial2.println ("Compass calibrated");
      break;
    case 5:
    Serial.println ("Running");
    Serial2.println ("Running");
      searchSouth ();
      clean ();
      Serial.println (";)");
      Serial2.println (";)");
      break;
    case 6:
    Serial.println ("Tense");
    Serial.println ("Tense");
      tense ();
      clean ();
      break;
    case 7:
    Serial.println ("Loose");
    Serial2.println ("Loose");
      loose ();
      clean ();
      break;
      //    default:
      //      Serial2.println ("Try Again");
      //      printMenu ();
      //      break;
  }
}
