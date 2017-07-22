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
// Holoseat Firmware
// This firmware detects the cadence and direction of an exercise bike or eliptical machine 
// and when the cadence is greater than a trigger value sends the specified key to trigger 
// walking forward (w) or backward (s) as needed in video games such as FPSs, RPGs, and MMOs.
//
// The process for calculating cadence is to measure the time difference (deltaT) between
// sensor events on the primary sensor.  We then calculate the cadence from deltaT since we
// know a single revolution has occurred during the time measured as deltaT. 
//
// The process for determining the direction of the pedalling is to measure the time between 
// sensor events on sensors 1 and 2.  We record both the time from sensor 1 to 2 (SensedDirectionT2) 
// and the time from sensor 2 to 1 (SensedDirectionT1).  If SensedDirectionT1 is greater than 
// SensedDirectionT2, then the user is pedalling forward, otherwise the user is pedalling
// backward.

 //#define DEBUG

 #include "holoseat_constants.h"  // contains holoseat configuration settings
 #include "Keyboard.h"            // for sending the walk keys
 #include "math.h"                // ??
 #include <Bounce2.h>             // for debouncing the enable button
 
char FirmwareVersionString[] = "0.3.0";  // per wiki - https://opendesignengine.net/projects/holoseat/wiki/V0_3Description

// Parameter values from holoseat_constants.h
char WalkForwardCharacter = DefaultWalkForwardCharacter;
char WalkBackwardCharacter = DefaultWalkBackwardCharacter;
unsigned int ForwardTriggerCadence = DefaultTriggerCadence;
unsigned int BackwardTriggerCadence = DefaultTriggerCadence;
unsigned int LoggingEnabled = DefaultLoggingEnabled;
unsigned int LoggingInterval = DefaultLoggingInterval;

// when we wake up, we will go through the transition right away, so set up for that fact
unsigned int HoloseatEnabled = !DefaultHoloseatEnabled;  

// Track key board state
char CurrentPressedKey = 0;       // what is the current key being pressed, 0 means no key pressed
char DesiredPressedKey = 0;       // what key does the user want pressed, 0 means no key

// calculated values
float Cadence;			              // pedalling speed
volatile float SensedDeltaT;      // deltaT as calculated during interrupt calls
volatile boolean WalkingForward;  // walking direction

// sensor data and functions
const int CadencePin = 3;                         // pin used to measure cadence
const int DirectionPin = 2;                       // pin to read direction
const int NumPoles = 12;                          // number of magnetic pole pairs on the tone ring
volatile unsigned long LastStepTime;              // last time the step sensor was triggered

// common function to attach/detach interrupts
void EnableSensors(unsigned int enable) {
  if (enable) {
    attachInterrupt(digitalPinToInterrupt(CadencePin), DetectCadence, FALLING);
  }
  else {
    detachInterrupt(digitalPinToInterrupt(CadencePin));
  }
}

// interrupt function for sensor 1, used to measure cadence
void DetectCadence() {
  unsigned long currentTime = millis();
  SensedDeltaT = (currentTime - LastStepTime);
  LastStepTime = currentTime;
  WalkingForward = digitalRead(DirectionPin);  // CCW is forward
}

// Logging data
volatile unsigned long LastLogTime;		// time since last log message was sent

// formats status string and sends to serial connection if available
// see https://opendesignengine.net/projects/holoseat/wiki/Software_Source_Code#HoloSeat-Serial-Protocol
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
  if (!WalkingForward)
    Serial.print("-");
  Serial.print(round(Cadence));
  Serial.print("/");
  Serial.print(ForwardTriggerCadence);
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

// Parses commands from serial connection
// see https://opendesignengine.net/projects/holoseat/wiki/Software_Source_Code#HoloSeat-Serial-Protocol
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
      ForwardTriggerCadence = command.substring(nextStart+1).toInt();
      BackwardTriggerCadence = ForwardTriggerCadence;
      
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
  // set up pins and debouncer library
  pinMode(enableLedPin, OUTPUT); //our ledPin is an output
  pinMode(enableButtonPin, INPUT_PULLUP); //we're reading from the button
  debouncer.attach(enableButtonPin);
  debouncer.interval(5); // interval in ms

  // configure DirectionPin for reading
  pinMode(DirectionPin, INPUT);

  Serial.begin(SerialBaudRate);    
  //MinTriggerPeriod = floor((1/TriggerStepsPerMax) * 60 * 1000);

  // start holoseat behavior
  InitializeWalkingVariables();
  EnableSensors(true);
  LastLogTime = millis();
  Keyboard.begin();

#ifdef DEBUG  // when debugging, hold for the serial monitor and setup some test defaults
  while (!Serial)
    {
    ;
    }

  // override defaults
  WalkForwardCharacter = 'w';
  WalkBackwardCharacter = 's';
  HoloseatEnabled = !true;  // when we wake up, we will go through the transition right away, so set up for that fact
  ForwardTriggerCadence = 45;
  BackwardTriggerCadence = 45;
  LoggingEnabled = 1;
  LoggingInterval = 5;

  // send ready message and state
  Serial.println("R"); // send ready signal, if there is a serial connection
  SendStateMessage();
#endif
}

void loop() {
  // read from enable button
  debouncer.update();
  enableReading = debouncer.read();

  // read from serial port
  ProcessSerialData();
  
  // handle enable switching
  if (enableReading == HIGH && enablePrevious == LOW)
    HoloseatEnabled = !HoloseatEnabled;

  // handle "walking" (or not)
  if (HoloseatEnabled) {
    digitalWrite(enableLedPin, HIGH);
    HandleWalking();
  }
  else {
    digitalWrite(enableLedPin, LOW);
    InitializeWalkingVariables();
  }
    
  // store previous enable reading for use in next iteration
  enablePrevious = enableReading;
}

// handle sensor data to determine walk state and act accordingly
void HandleWalking() {
  // disable interrupts while we do some math and work the keyboard
  EnableSensors(false);

  // calculate the Cadence
  unsigned long currentTime = millis();
  float localDeltaT = (currentTime - LastStepTime);  
  float deltaT = max(SensedDeltaT, localDeltaT)/1000; // in seconds
  Cadence = round(60.0/deltaT/NumPoles);  // in RPM

  // determine what key is desired
  if (WalkingForward && (Cadence >= ForwardTriggerCadence))
    DesiredPressedKey = WalkForwardCharacter;
  else if (!WalkingForward && (Cadence >= BackwardTriggerCadence))
    DesiredPressedKey = WalkBackwardCharacter;
  else
    DesiredPressedKey = 0;

  // handle desired pressed key
  if (DesiredPressedKey != CurrentPressedKey) { // only need to do something when there is a change 
    if (!CurrentPressedKey) {
      // no key pressed so just press the desired key and record the pressed key
      Keyboard.press(DesiredPressedKey);
      CurrentPressedKey = DesiredPressedKey;
      }
    else if (!DesiredPressedKey) {
      // the desired key press is no keys
      Keyboard.release(CurrentPressedKey);
      CurrentPressedKey = DesiredPressedKey;
      }
    else {
      // the current key pressed is different than the key we desire: release, press, record 
      Keyboard.release(CurrentPressedKey);
      Keyboard.press(DesiredPressedKey);
      CurrentPressedKey = DesiredPressedKey;
      }
    }

  
  // re-enbale the interrupts now that we are done
  EnableSensors(true);
}

// resets walking state variables, used when holoseat is disabled
void InitializeWalkingVariables() {
  Keyboard.releaseAll();
  Cadence = 0.0;
  WalkingForward = true;
  SensedDeltaT = 5000;            // initialize sensed deltaT (and the value used to compute it, LastStepTime) to 5 seconds in the past
  LastStepTime = millis() - 5000; // as above
  CurrentPressedKey = 0;
  DesiredPressedKey = 0;
}
