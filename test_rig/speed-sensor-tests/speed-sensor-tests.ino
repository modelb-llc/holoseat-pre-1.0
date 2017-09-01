// Copyright Model B, LLC 2017.
// Author: J. Simmons 
// https://opendesignengine.net/projects/holoseat/
// 
// This file is part of the Holoseat software suite (firmware, control software, etc).
//
// The Holoseat software suite is free software: you can redistribute it and/or modify 
// it under the terms of the GNU General Public License as published by the Free Software 
// Foundation, either version 3 of the License, or (at your option) any later version.
//
// Holoseat software suite is distributed in the hope that it will be useful, but 
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with Holoseat 
// software suite.  If not, see <http://www.gnu.org/licenses/>.

// 
// Holoseat Speed Sensor Tests
// 

#include <math.h>

const int CadencePin = 3;                         // pin used to measure cadence
const int DirectionPin = 2;                       // pin to read direction
const int NumPoles = 12;                          // number of magnetic pole pairs on the tone ring

volatile unsigned long LastStepTime;              // last time the step sensor was triggered
volatile float SensedDeltaT;                      // deltaT as calculated during interrupt calls
volatile boolean WalkingForward;                  // walking direction state

float Cadence;                                    // pedalling speed


// common function to attach/detach interrupts
void EnableSensors(unsigned int enable) {
  if (enable) {
    attachInterrupt(digitalPinToInterrupt(CadencePin), DetectCadence, FALLING);
    //attachInterrupt(DirectionInterruptNumber, DetermineDirection, FALLING);
  }
  else {
    detachInterrupt(digitalPinToInterrupt(CadencePin));
    //detachInterrupt(DirectionInterruptNumber);
  }
}

// interrupt function used to measure cadence
void DetectCadence() {
  unsigned long currentTime = millis();
  SensedDeltaT = (currentTime - LastStepTime);
  LastStepTime = currentTime;
  WalkingForward = digitalRead(DirectionPin);  // CCW is forward
}

// resets walking state variables, used when holoseat is disabled
void InitializeWalkingVariables() {
  Cadence = 0.0;
  SensedDeltaT = 5000;            // initialize sensed deltaT (and the value used to compute it, LastStepTime) to 5 seconds in the past
  LastStepTime = millis() - 5000; // as above
  WalkingForward = true;  
}

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(DirectionPin, INPUT);
  pinMode(CadencePin, INPUT);
  InitializeWalkingVariables();
  EnableSensors(true);
  Serial.begin(57600); 
  Serial.println("r"); // send ready signal
}

// the loop function runs over and over again forever
void loop() {
  delay(10);
  EnableSensors(false);

  // calculate the Cadence
  unsigned long currentTime = millis();
  float localDeltaT = (currentTime - LastStepTime);  
  float deltaT = max(SensedDeltaT, localDeltaT)/1000; // in seconds
  Cadence = round(60.0/deltaT/NumPoles);  // in RPM
  
  if (WalkingForward)
    Serial.print("+");
  else
    Serial.print("-");

  Serial.print((int)Cadence);
  Serial.println("");  
  EnableSensors(true);                  
}
