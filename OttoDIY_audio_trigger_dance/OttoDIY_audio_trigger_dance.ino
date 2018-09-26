#include <Servo.h> 
#include "EasingLibrary.h"
#include <NewPing.h>

#define TRIGGER_PIN  11  //  4 on BoB board  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     12  // A0 on BoB board  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 15 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

SineEase Ease;

Servo RightHipServo;  // setup servo objects 
Servo LeftHipServo;
Servo RightAnkleServo;
Servo LeftAnkleServo;

int Right = 1;
int Left = 2;
int FootUp;  // for which foot is in the air
int StepDelay = 1500;  // pause between servo commands in uS; controls walking speed. 250 = very fast 2500 = good for testing 1500 = good walk
int Distance;  // ultrasonic pulse travel time in uS
int DistanceMax = 500;  // maximum ultrasonic flight time to trigger obstacle avoidance
int DistanceDance = 250;  // activates dance mode at power up
int DanceTrigger = 0;  // used to trigger dance mode loop
int AudioPin = 3;  // pin 3 used for audio detection
int RandomNumber;
// volatile long RandomNumber;  // used to determine which dance to do
int Duration = 199;  // time units in easing function, zero indexed
double easedPosition;  // adjustment value to servo between steps
int i; // counter used in for/next loops
int Pos;  // servo position in microseconds
int RightHipLeft = 1210;  // servo positions in uS. left refers to the direction the body turns in relation to the leg 
int RightHipMid = 1360;
int RightHipRight = 1510;
int LeftHipLeft = 1300;  
int LeftHipMid = 1450;
int LeftHipRight = 1600;
int RightAnkleUp = 1140;  // up refers to the outer edge of the foot that is being raised
int RightAnkleMid = 1340;
int RightAnkleDown = 1540;
int LeftAnkleUp = 1720;
int LeftAnkleMid = 1520;
int LeftAnkleDown = 1320;

int HipRange = 150;  // range in uS between servo travel endpoints
int AnkleRange = 200;


void setup() 
{ 
  RightHipServo.attach(9);  // set up pins for servos
  LeftHipServo.attach(2);
  RightAnkleServo.attach(1);
  LeftAnkleServo.attach(4);

  pinMode(AudioPin, INPUT); 
  
  // Serial.begin(9600);  // setup for terminal debug

  RightHipServo.writeMicroseconds(RightHipMid);  // center all servos
  LeftHipServo.writeMicroseconds(LeftHipMid);
  RightAnkleServo.writeMicroseconds(RightAnkleMid);
  LeftAnkleServo.writeMicroseconds(LeftAnkleMid);
    
  Ease.setDuration(Duration);  //  sets overall time units for easing function

  delay(5000);  // pause before the show
  
  GetDistance();  //check for hand in front of bot
  if (Distance < DistanceDance && Distance > 0) {
    for( i=0;i<=Duration;i++) {
      AnkleMove1(Right);
      delayMicroseconds(StepDelay);
    }
    for( i=0;i<=Duration;i++) {
      AnkleMove3(Right);
      delayMicroseconds(StepDelay);
    }
    DanceTrigger = 1;
    randomSeed(analogRead(2));  // start random number generator with value of floating analog pin 2
  }
  if (DanceTrigger == 1) {
    // attachInterrupt(1, Celebrate, RISING);  // pin 3
    // while (DanceTrigger = 1) {
    int PinCheck;
    SecondLoop:
    PinCheck = digitalRead(AudioPin);
    if (PinCheck == HIGH) {
        Celebrate();
    }
    goto SecondLoop;
    //} 
  }
  
  StartupLeanRight();    // first movement from startup; not used in normal walking routine
}
  

void loop() {  // main loop broken down into movement sequences and an obstacle navigations routine
  // starts in base position, left foot in the air
  LeftFootStepForward();  // begin walk forward loop
  LeftFootPutDown();  //sensor looking right
  RightFootStepToBase();  // base refers to base position; facing forward, one leg in the air, hips straight; this cycle it's rt leg up
  Navigate();  // sensor check, go-no go decisions, and maneuvering sequences
  RightFootStepForward();
  RightFootPutDown();  //sensor looking left
  LeftFootStepToBase();  //lt leg up
  Navigate();
}

void Celebrate() {
  RandomNumber = random(4);  // random number between 0 and 4-1
  switch (RandomNumber) {
    case 0:
      ShuffleStep();
      break;
    case 1:
      LeanAndFootWiggle();
      break;
    case 2:
      LeanAndLegTwist();
      break;
    case 3:
      BobTheBoB();
      break;
  }
}

/*************************************************************************************************************************
                                                      Movement Sequences                                                 *
**************************************************************************************************************************/

// movement sequences consist of one or many Individual Moves

void StartupLeanRight() {  // startup move
  for( i=0;i<=Duration;i++)    {
    AnkleMove1(Left);    
    AnkleMove2 (Right);
    delayMicroseconds (StepDelay);
  }
}
void StartupLeanLeft() {
  for( i=0;i<=Duration;i++)    {
    AnkleMove1(Right);  
    AnkleMove2 (Left);    
    delayMicroseconds (StepDelay);
  }
}
void RightFootStepToBase() {
  for( i=0;i<=Duration;i++)    {
    AnkleMove1(Right);    
    AnkleMove2 (Left);    
    HipMove2 (Right);
    HipMove2 (Left);    
    delayMicroseconds (StepDelay);
  }
  FootUp = Right;  // referenced during turning routine
}
void LeftFootStepToBase() {
  for( i=0;i<=Duration;i++)    {
    AnkleMove1(Left);    
    AnkleMove2 (Right);    
    HipMove4 (Right);    
    HipMove4 (Left);    
    delayMicroseconds (StepDelay);
  }
  FootUp = Left;  // referenced during turning routine
}
void RightFootStepForward() {
  for( i=0;i<=Duration;i++){
    HipMove3(Left);    
    HipMove3 (Right);    
    delayMicroseconds (StepDelay);
  }
}
void LeftFootStepForward() {
  for( i=0;i<=Duration;i++) {
    HipMove1(Right);    
    HipMove1 (Left);    
    delayMicroseconds (StepDelay);
  }
}
void RightFootPutDown() {
  for( i=0;i<=Duration;i++)    {
    AnkleMove3 (Right);
    AnkleMove4 (Left);    
    delayMicroseconds (StepDelay);
  }
}
void LeftFootPutDown() {
  for( i=0;i<=Duration;i++)    {
   AnkleMove4 (Right);   
   AnkleMove3 (Left);   
   delayMicroseconds (StepDelay);
  }
}
void BeginTurnRight() { // make following beginturnright
  for( i=0;i<=Duration;i++)    {
    HipMove3(Right);
    delayMicroseconds (StepDelay);
  }
}      
void BeginTurnLeft() {  // make following beginturnleft
  for( i=0;i<=Duration;i++)    {
    HipMove1(Left);
    delayMicroseconds(StepDelay);
  }
}
void PivotLeft() {  // make following pivotleft
  StartupLeanLeft();
  for( i=0;i<=Duration;i++)    {
    HipMove2(Left);    
    delayMicroseconds(StepDelay);  
  }
  RightFootPutDown();
}
void PivotRight() {  // make following pivotright
  StartupLeanRight();
  for( i=0;i<=Duration;i++)    {
    HipMove4(Right);     
    delayMicroseconds(StepDelay);  
  }
  LeftFootPutDown();
}
void TurnLeft() {
  StartupLeanRight();
  BeginTurnLeft();
  LeftFootPutDown();
  PivotLeft();
}
void TurnRight() {
  StartupLeanLeft();
  BeginTurnRight();
  RightFootPutDown();
  PivotRight();
}
void RightFootStepBackward() {
    for( i=0;i<=Duration;i++) {
    HipMove4(Right);
    HipMove4(Left);
      delayMicroseconds(StepDelay);
    }    
    for( i=0;i<=Duration;i++) {
    HipMove1(Right);
    HipMove1(Left);
      delayMicroseconds(StepDelay);
    }
}
void LeftFootStepBackward() {
    for( i=0;i<=Duration;i++) {
    HipMove2(Right);
    HipMove2(Left);
      delayMicroseconds(StepDelay);
    }
    for( i=0;i<=Duration;i++) {
    HipMove3(Right);
    HipMove3(Left);
      delayMicroseconds(StepDelay);
    }
  }
void RightAnkleWiggle() {
  for (int j=0;j<3;j++) {
    for( i=0;i<=Duration;i++) {
      AnkleMove3(Right);
      delayMicroseconds(StepDelay);
    }
    for( i=0;i<=Duration;i++) {
      AnkleMove2(Right);
      delayMicroseconds(StepDelay);
    }
    for( i=0;i<=Duration;i++) {
      AnkleMove4(Right);
      delayMicroseconds(StepDelay);
    }
    for( i=0;i<=Duration;i++) {
      AnkleMove1(Right);
      delayMicroseconds(StepDelay);
    }
  }  //  x2
}
void LeftAnkleWiggle() {
  for (int j=0;j<3;j++) {
    for ( i=0;i<=Duration;i++) {
      AnkleMove3(Left);
      delayMicroseconds(StepDelay);
    }
    for ( i=0;i<=Duration;i++) {
      AnkleMove2(Left);
      delayMicroseconds(StepDelay);
    }
    for ( i=0;i<=Duration;i++) {
      AnkleMove4(Left);
      delayMicroseconds(StepDelay);
    }
    for ( i=0;i<=Duration;i++) {
      AnkleMove1(Left);
      delayMicroseconds(StepDelay);
    }
  }  // x2
}
void RightLegTwist() {
  for( i=0;i<=Duration;i++) {
    HipMove3(Right);
    AnkleMove3(Right);
    delayMicroseconds(StepDelay);
  }
  for( i=0;i<=Duration;i++) {
    HipMove4(Right);
    AnkleMove1(Right);
    delayMicroseconds(StepDelay);
  }
}
void LeftLegTwist() {
  for( i=0;i<=Duration;i++) {
    HipMove1(Left);
    AnkleMove3(Left);
    delayMicroseconds(StepDelay);
  }
  for ( i=0;i<=Duration;i++) {
    HipMove2(Left);
    AnkleMove1(Left);
    delayMicroseconds(StepDelay);
  }
}
/***********************************************************************************************
                                        Dance Moves                                            *
***********************************************************************************************/
void ShuffleStep() {
  StartupLeanRight();    // first movement from startup; not used in normal walking routine
  //------
  LeftFootStepForward();  // begin walk forward loop
  LeftFootPutDown();  //sensor looking right
  RightFootStepToBase();  // base refers to base position; facing forward, one leg in the air, hips straight; this cycle it's rt leg up
  RightFootStepForward();
  RightFootStepBackward();
  RightFootPutDown();
  StartupLeanRight();
  LeftFootStepBackward();
  for( i=0;i<=Duration;i++) {
    HipMove4(Right);
    HipMove4(Left);
    delayMicroseconds(StepDelay);
  }    //------------
  LeftFootPutDown();
}
void LeanAndFootWiggle() {
  StartupLeanRight();
  LeftAnkleWiggle();
  LeftFootPutDown();
  StartupLeanLeft();
  RightAnkleWiggle();
  RightFootPutDown();
}
void LeanAndLegTwist() {
  StartupLeanRight();    // first movement from startup; not used in normal walking routine
  LeftLegTwist();
  LeftFootPutDown();
  StartupLeanLeft();
  RightLegTwist();
  RightFootPutDown();
}
void BobTheBoB() {
  for( i=0;i<=Duration;i++) {
    AnkleMove2(Right);
    AnkleMove2(Left);
    delayMicroseconds(StepDelay);
  }
  for( i=0;i<=Duration;i++) {
    AnkleMove4(Right);
    AnkleMove4(Left);
    delayMicroseconds(StepDelay);
  }
  for( i=0;i<=Duration;i++) {
    AnkleMove1(Right);
    AnkleMove1(Left);
    delayMicroseconds(StepDelay);
  }
  for( i=0;i<=Duration;i++) {
    AnkleMove3(Right);
    AnkleMove3(Left);
    delayMicroseconds(StepDelay);
  }
}
  

/*****************************************************************************************************
                                              Individual Moves                                       *
******************************************************************************************************/

// each affects single servo position changes

void HipMove1 (int WhichServo) {
  Ease.setTotalChangeInPosition(HipRange); 
  switch (WhichServo) {
    case 1:  //right
      easedPosition=Ease.easeIn(i);
      Pos = RightHipMid + easedPosition;
      RightHipServo.writeMicroseconds(Pos);
      break;
    case 2:  // left
      easedPosition=Ease.easeIn(i);
      Pos = LeftHipMid + easedPosition;
      LeftHipServo.writeMicroseconds(Pos);
      break;
    }
}
void HipMove2 (int WhichServo) {
  Ease.setTotalChangeInPosition(HipRange); 
  switch (WhichServo) {
    case 1:  //right
      easedPosition=Ease.easeInOut(i);
      Pos = RightHipRight - easedPosition;
      RightHipServo.writeMicroseconds(Pos);
      break;
    case 2:  // left
      easedPosition=Ease.easeInOut(i);
      Pos = LeftHipRight - easedPosition;
      LeftHipServo.writeMicroseconds(Pos);
      break;
    }
}
void HipMove3 (int WhichServo) {
  Ease.setTotalChangeInPosition(HipRange); 
  switch (WhichServo) {
    case 1:  //right
      easedPosition=Ease.easeIn(i);
      Pos = RightHipMid - easedPosition;
      RightHipServo.writeMicroseconds(Pos);
      break;
    case 2:  // left
      easedPosition=Ease.easeIn(i);
      Pos = LeftHipMid - easedPosition;
      LeftHipServo.writeMicroseconds(Pos);
      break;
    }
}
void HipMove4 (int WhichServo) {
  Ease.setTotalChangeInPosition(HipRange); 
  switch (WhichServo) {
    case 1:  //right
      easedPosition=Ease.easeInOut(i);
      Pos = RightHipLeft + easedPosition;
      RightHipServo.writeMicroseconds(Pos);
      break;
    case 2:  // left
      easedPosition=Ease.easeInOut(i);
      Pos = LeftHipLeft + easedPosition;
      LeftHipServo.writeMicroseconds(Pos);
      break;
    }
}
void AnkleMove1 (int WhichServo) {
  Ease.setTotalChangeInPosition(AnkleRange); 
  switch (WhichServo) {
    case 1:  //right
      easedPosition=Ease.easeInOut(i);
      Pos = RightAnkleMid + easedPosition;
      RightAnkleServo.writeMicroseconds(Pos);
      break;
    case 2:  // left
      easedPosition=Ease.easeInOut(i);
      Pos = LeftAnkleMid - easedPosition;
      LeftAnkleServo.writeMicroseconds(Pos);
      break;
    }
}
void AnkleMove2 (int WhichServo) {
  Ease.setTotalChangeInPosition(AnkleRange); 
  switch (WhichServo) {
    case 1:  //right
      easedPosition=Ease.easeInOut(i);
      Pos = RightAnkleMid - easedPosition;
      RightAnkleServo.writeMicroseconds(Pos);
      break;
    case 2:  // left
      easedPosition=Ease.easeInOut(i);
      Pos = LeftAnkleMid + easedPosition;
      LeftAnkleServo.writeMicroseconds(Pos);
      break;
  }
}
void AnkleMove3 (int WhichServo) {
  Ease.setTotalChangeInPosition(AnkleRange); 
  switch (WhichServo) {
    case 1:  //right
      easedPosition=Ease.easeOut(i);
      Pos = RightAnkleDown - easedPosition;
      RightAnkleServo.writeMicroseconds(Pos);
      break;
    case 2:  // left
      easedPosition=Ease.easeOut(i);
      Pos = LeftAnkleDown + easedPosition;
      LeftAnkleServo.writeMicroseconds(Pos);
      break;
  }
}
void AnkleMove4 (int WhichServo) {
  Ease.setTotalChangeInPosition(AnkleRange); 
  switch (WhichServo) {
    case 1:  //right
      easedPosition=Ease.easeOut(i);
      Pos = RightAnkleUp + easedPosition;
      RightAnkleServo.writeMicroseconds(Pos);
      break;
    case 2:  // left
      easedPosition=Ease.easeOut(i);
      Pos = LeftAnkleUp - easedPosition;
      LeftAnkleServo.writeMicroseconds(Pos);
      break;
  }
}

/****************************************************************************************************************
                                                        other functions                                         *
*****************************************************************************************************************/


void Navigate() {
  GetDistance();
  if (Distance < DistanceMax && Distance > 0) {  
    switch (FootUp) {  // shift to start standing position, aka position A
      case 1:  // right foot up, will turn left      
      RightFootPutDown();
      TurnLeft();
      GetDistance();
      GoNoGo();
      StartupLeanRight();     // restart with StartupLean
      LeftFootStepForward();  
      LeftFootPutDown();  
      RightFootStepToBase();  // returns to position before avoidance loop
      break;
    
    case 2:
      LeftFootPutDown();
      TurnRight();
      GetDistance();
      GoNoGo();
      StartupLeanLeft();
      RightFootStepForward();
      RightFootPutDown(); 
      LeftFootStepToBase();  // restarts and returns to position before avoidance loop
      break;
    }
  }
}
void GetDistance() {
  Distance = sonar.ping(); // Send ping, get flight time in microseconds (uS).
}
void GoNoGo() {
      if (Distance < DistanceMax && Distance > 0) {
        do {
          switch (FootUp) {
            case 1:
              TurnLeft();
              break;
            case 2:
              TurnRight();
              break;
          }        
          GetDistance();  // read distance again
        } while (Distance < DistanceMax && Distance > 0);
      }   
}    

