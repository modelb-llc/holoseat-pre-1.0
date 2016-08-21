/* Copyright (C) 2016 Model B, LLC
 * author: J. Simmons 
 * https://opendesignengine.net/projects/holoseat/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

/*
 * Holoseat Firmware
 * This firmware detects the speed of an exercise bike or eliptical machine and
 * when the speed is greater than a trigger value sends the "w" key to trigger 
 * walking in video games such as FPSs, RPGs, and MMOs.
 */

 //#define DEBUG

 #include "holoseat_constants.h"  // contains holoseat configuration settings
 #include "Keyboard.h"            // for sending the walk keys
 #include "math.h"                // ??
 #include <Bounce2.h>             // for debouncing the enable button
 
char FirmwareVersionString[] = "0.3.0";  // per wiki - https://opendesignengine.net/projects/holoseat/wiki/V0_3Description

// Parameter values from holoseat_constants.h
char WalkForwardCharacter = DefaultWalkForwardCharacter;
char WalkBackwardCharacter = DefaultWalkBackwardCharacter;
unsigned int HoloseatEnabled = !DefaultHoloseatEnabled;  // when we wake up, we will go through the transition right away, so set up for that fact
unsigned int TriggerCadence = DefaultTriggerCadence;
unsigned int LoggingEnabled = DefaultLoggingEnabled;
unsigned int LoggingInterval = DefaultLoggingInterval;

// setup walking state
boolean WalkingState;
boolean LastWalkingState;
int WalkingDirection;
int LastWalkingDirection;

// calculated values
float Cadence;
float LastLocalDeltaT;

// sensor data and functions
volatile unsigned long LastStepTime;
volatile unsigned long LastDirectionTime;
volatile float SensedDeltaT;
volatile float SensedDirectionT1;
volatile float SensedDirectionT2;
const unsigned int CadenceInterruptNumber = 0;
const unsigned int DirectionInterruptNumber = 1;

void EnableSensors(unsigned int enable) {
  if (enable) {
    attachInterrupt(CadenceInterruptNumber, DetectCadence, FALLING);
    attachInterrupt(DirectionInterruptNumber, DetermineDirection, FALLING);
  }
  else {
    detachInterrupt(CadenceInterruptNumber);
    detachInterrupt(DirectionInterruptNumber);
  }
}

void DetectCadence() {
  unsigned long currentTime = millis();
  SensedDeltaT = (currentTime - LastStepTime);
  SensedDirectionT1 = currentTime - LastDirectionTime;
  LastStepTime = currentTime;
}

void DetermineDirection() {
  unsigned long currentTime = millis();
  SensedDirectionT2 = currentTime - LastStepTime;
  LastDirectionTime = currentTime;
}

// Logging data
volatile unsigned long LastLogTime;

void SendStateMessage() {
  if(!Serial) // if the serial port connection is not available, skip state message
    return;
  
  Serial.print(FirmwareVersionString);
  Serial.print(",");
  Serial.print(WalkForwardCharacter);
  Serial.print("(");
  Serial.print(DefaultWalkForwardCharacter);
  Serial.print("),");
  Serial.print(WalkBackwardCharacter);
  Serial.print("(");
  Serial.print(DefaultWalkBackwardCharacter);
  Serial.print("),");
  Serial.print(HoloseatEnabled);
  Serial.print("(");
  Serial.print(DefaultHoloseatEnabled);
  Serial.print("),");
  Serial.print(WalkingDirection * round(Cadence));
  Serial.print("/");
  Serial.print(TriggerCadence);
  Serial.print("(");
  Serial.print(DefaultTriggerCadence);
  Serial.print("),");
  Serial.print(LoggingEnabled);
  Serial.print("(");
  Serial.print(DefaultLoggingEnabled);
  Serial.print(")/");
  Serial.print(LoggingInterval);
  Serial.print("(");
  Serial.print(DefaultLoggingInterval);
  Serial.println(")");
}

void ProcessSerialData() {
  if (Serial && Serial.available()) {
    // FIXME - replace with C-string functions later for stability 
    String command = Serial.readStringUntil('\n'); 
    int nextStart = 0;
  
    if (command.charAt(0) == '?') {
      Serial.println("R"); // send ready signal
      SendStateMessage();
    }
    else if (command.charAt(0) == 'Q') {
      SendStateMessage();
    }
    else if (command.charAt(0) == 'S') {
      // find new walk forward character
      nextStart = 2;
      WalkForwardCharacter = command.charAt(nextStart);

      // find new walk backward character
      nextStart = command.indexOf(',', nextStart);
      WalkBackwardCharacter = command.charAt(nextStart+1);
    
      // find new enabled flag
      nextStart = command.indexOf(',', nextStart+1);
      HoloseatEnabled = command.substring(nextStart+1).toInt();
      
      // find trigger cadence
      nextStart = command.indexOf(',', nextStart+1);
      TriggerCadence = command.substring(nextStart+1).toInt();
      
      // find new enable logging
      nextStart = command.indexOf(',', nextStart+1);
      LoggingEnabled = command.substring(nextStart+1).toInt();
      
      // find the new logging interval
      nextStart = command.indexOf(',', nextStart+1);    
      LoggingInterval = command.substring(nextStart+1).toInt();
      
      Serial.println("OK");
    }
    else {
      Serial.println("ERROR");  
    }
  }
  
  if (LoggingEnabled && (millis() - LastLogTime >= (100 * LoggingInterval))) { // measured in 1/10 sec
    LastLogTime = millis();
    SendStateMessage();
  }
}

// set up enabled state variables
int enableReading = LOW;          
int enablePrevious = LOW;

// set up enable button elements
int enableLedPin = 13;
int enableButtonPin = 10;
Bounce debouncer = Bounce();

void setup() {
  // put your setup code here, to run once:
  pinMode(enableLedPin, OUTPUT); //our ledPin is an output
  pinMode(enableButtonPin, INPUT_PULLUP); //we're reading from the button
  debouncer.attach(enableButtonPin);
  debouncer.interval(5); // interval in ms

  Serial.begin(SerialBaudRate);    
  //MinTriggerPeriod = floor((1/TriggerStepsPerMax) * 60 * 1000);

  InitializeWalkingVariables();
  EnableSensors(true);
  LastLogTime = millis();
   
  Keyboard.begin();

#ifdef DEBUG  // when debugging, hold for the serial monitor
  while (!Serial)
    {
    ;
    }

  // override defaults
  WalkForwardCharacter = 'w';
  WalkBackwardCharacter = 's';
  HoloseatEnabled = !true;  // when we wake up, we will go through the transition right away, so set up for that fact
  TriggerCadence = 45;
  LoggingEnabled = 1;
  LoggingInterval = 5;

  // send ready message and state
  Serial.println("R"); // send ready signal, if there is a serial connection
  SendStateMessage();
#endif
}

void loop() {
  // put your main code here, to run repeatedly:
  debouncer.update();
  enableReading = debouncer.read();

  ProcessSerialData();
  
  if (enableReading == HIGH && enablePrevious == LOW)
    HoloseatEnabled = !HoloseatEnabled;

  if (HoloseatEnabled) {
    digitalWrite(enableLedPin, HIGH);
    HandleWalking();
  }
  else {
    digitalWrite(enableLedPin, LOW);
    InitializeWalkingVariables();
  }
    
  enablePrevious = enableReading;
}

void HandleWalking() {
  // disable interrupts while we do some math and work the keyboard
  EnableSensors(false);

  // calculate the Cadence
  unsigned long currentTime = millis();
  float localDeltaT = (currentTime - LastStepTime);  
  float deltaT = max(SensedDeltaT, localDeltaT)/1000; // in seconds
  Cadence = 60.0/deltaT;  // in RPM

  // deal with walking
  WalkingState = Cadence > TriggerCadence;
  float directionDeltaT = SensedDirectionT1 - SensedDirectionT2;
  WalkingDirection = (directionDeltaT >= 0)?1:-1;
 
/*
  Serial.print(SensedDirectionT1);
  Serial.print(" - ");
  Serial.print(SensedDirectionT2);
  Serial.print(" = ");
  Serial.println(directionDeltaT);
*/
  if ((!WalkingState) && (LastLocalDeltaT > localDeltaT)) {  
    if (WalkingDirection > 0)
      WalkNSteps(20, WalkForwardCharacter);
    else
      WalkNSteps(20, WalkBackwardCharacter);
  }  

  if (WalkingState && (WalkingDirection * LastWalkingDirection < 0))  // we reversed direction, stop!
    InitializeWalkingVariables();

  if ((WalkingState != LastWalkingState)) {
    LastWalkingState = WalkingState;
    if (WalkingState) {
      if (WalkingDirection > 0) {
        Keyboard.release(WalkBackwardCharacter);
        Keyboard.press(WalkForwardCharacter);
      }
      else {
        Keyboard.release(WalkForwardCharacter);
        Keyboard.press(WalkBackwardCharacter);
      }
    }
    else
      InitializeWalkingVariables();
  }

  LastWalkingDirection = WalkingDirection;
  LastLocalDeltaT = localDeltaT;
  
  // re-enbale the interrupts now that we are done
  EnableSensors(true);
}

void WalkNSteps(int n, char c) {
  Keyboard.press(c);
  delay(10*n);
  Keyboard.releaseAll(); 
}

void InitializeWalkingVariables() {
  Keyboard.releaseAll();
  Cadence = 0.0;
  SensedDeltaT = 5000;            // initialize sensed deltaT (and the value used to compute it, LastStepTime) to 5 seconds in the past
  LastStepTime = millis() - 5000; // as above
  SensedDirectionT1 = 1000;         
  SensedDirectionT2 = 100;
  LastLocalDeltaT = 0;
  WalkingState = false;
  LastWalkingState = false;
  WalkingDirection = 1;  
  LastWalkingDirection = 1;
}
