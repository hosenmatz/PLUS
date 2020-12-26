#include <Otto9.h>
Otto9 Otto;

#define PIN_YL 2 // left leg, servo[0]
#define PIN_YR 3 // right leg, servo[1]
#define PIN_RL 4 // left foot, servo[2]
#define PIN_RR 5 // right foot, servo[3]
#define PIN_Trigger 8 // ultrasound
#define PIN_Echo 9 // ultrasound
#define PIN_Buzzer  13 //buzzer

#define LeftLeg -15
#define RightLeg -15

#define LeftFoot -20
#define RightFoot 25

void setup() {
  Otto.init(PIN_YL, PIN_YR, PIN_RL, PIN_RR, true, A6, PIN_Buzzer, PIN_Trigger, PIN_Echo);
  Otto.setTrims(LeftLeg,RightLeg,LeftFoot,RightFoot);
  //Otto.setTrims(-15,0,0,15);
 Otto.saveTrimsOnEEPROM();
    // Change the legs and feet values gradually with small values and increments(+5 or - 5 degrees)
  //
  // Iteratively you have to check/upload the code multiple times, until Otto legs and feet looks completely straight.
  //calibrated
  // ONLY after the robot looks straight you can activate this block, then disable or delete again for further programming, otherwise can leave permanent damage in the memory. BE CAREFUL
  //calibration saved

}

void loop() {
    Otto.home();
    delay(4000);
    Otto.walk(5);
}
