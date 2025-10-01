#include <Arduino.h>
#include <P1AM.h>

enum MachineStates{
  Waiting,
  ColorSensing,
  CountedMove,
  Eject
};

MachineStates curState = Waiting;

//Moduels
int modInput = 1;
int modOutput = 2;
int modAnalog = 3;

//Inputs
int pulse = 1;
int lbIn = 2;
int lbOut = 3;

//Outputs
int conv = 1;

//Analog inputs
int color = 1;

void setup(){

  // Start up P1am modules
  while(!P1.init()){
    delay(1);
  }

  Serial.begin(9600);
}

bool InputTriggered(){
  return !P1.readDiscrete(modInput,lbIn);
}

void ToggleConveyor(bool s){
  P1.writeDiscrete(s, modOutput, conv);
}


void loop(){
  
  /*bool isOn = P1.readDiscrete(1,2);  // 1st moduel 2nd pin
  Serial.println(isOn); // 1 true, 0 false
  delay(100);*/

  switch (curState){
    case Waiting:
      // Wait for lighr barrier to be tripped
      //After tripped, switch state and turn on conveyor
      if(InputTriggered()){
        curState = ColorSensing;
        ToggleConveyor(true);
      }
      break;

    default:
      break;
  }
}