/* Copyright (C) 2013 - J. Simmons https://opendesignengine.net/projects/holoseat/
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
 * 
 * The code in this firmware is based upon a number of freely available tutorials,
 * including:
 *  - http://www.instructables.com/id/Arduino-Bike-Speedometer/
 *  - http://arduino.cc/en/Tutorial/Blink?from=Tutorial.BlinkingLED
 */
 
 #include "holoseat_constants.h"
 #include "Keyboard.h"
 #include "math.h"
 
char FirmwareVersionString[] = "0.0.0";
 
volatile unsigned long LastDebounceTime;
volatile unsigned long LastStepTime;
volatile unsigned long StepPeriodTriggered;
volatile unsigned int StepCount;
volatile unsigned long LastLogTime;

const long DebounceDelay = 100;    // the debounce time; increase if walking jitters
const float TriggerStepsPerMax = 175;
const unsigned int InterruptNumber = 1;
const int LedPin =  13;

// Parameter values
char WalkCharacter = DefaultWalkCharacter;
unsigned int HoloseatEnabled = DefaultHoloseatEnabled;
unsigned int TriggerCadence = DefaultTriggerCadence;
unsigned int LoggingEnabled = DefaultLoggingEnabled;
unsigned int LoggingInterval = DefaultLoggingInterval;

float StepsPerMin;
unsigned long MinTriggerPeriod;
boolean WalkingState;
boolean LastWalkingState;
unsigned long StepPeriod;
unsigned long  LastStepPeriod;
unsigned int LastStepCount;
unsigned long LastStepPeriodTriggered;
unsigned int ExtraSteps;

void StepsCalc()
 {
   if (millis() - LastDebounceTime > DebounceDelay)
     {
     StepPeriodTriggered = millis() - LastStepTime;
     LastStepTime = millis();
     StepCount++;
     }
     
   LastDebounceTime = millis();  
 }

void SendStateMessage()
 {
    Serial.print(FirmwareVersionString);
    Serial.print(",");
    Serial.print(WalkCharacter);
    Serial.print("(");
    Serial.print(DefaultWalkCharacter);
    Serial.print("),");
    Serial.print(HoloseatEnabled);
    Serial.print("(");
    Serial.print(DefaultHoloseatEnabled);
    Serial.print("),");
    Serial.print(round(StepsPerMin));
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

void setup()
 {
   pinMode(LedPin, OUTPUT);
   Serial.begin(SerialBaudRate); 
   while (!Serial) // FIXME - we need to make sure we can get to serial without blocking boot up
     {
     ; // wait for serial port to connect. Needed for Leonardo only
     }
   
   MinTriggerPeriod = floor((1/TriggerStepsPerMax) * 60 * 1000);
   LastDebounceTime = 0;

   
   //Interrupt 1 is digital pin 2, so that is where the reed switch is connected
   //Triggers on FALLING (change from HIGH to LOW)
   attachInterrupt(InterruptNumber, StepsCalc, FALLING);

   InitializeWalkingVariables();

   LastLogTime = millis();
   
   Keyboard.begin();
   Serial.println("R"); // send ready signal
   SendStateMessage();
 }

 void loop()
 {
   delay(DebounceDelay+50);  // delay should be longer than the debounce time

   if (Serial.available())
     {
     // FIXME - replace with C-string functions later for stability 
     String command = Serial.readStringUntil('\n'); 
     int nextStart = 0;
     if (command.charAt(0) == 'Q')
       SendStateMessage();
     else if (command.charAt(0) == 'S')
       {
       // find new walk character
       nextStart = 2;
       WalkCharacter = command.charAt(nextStart);

       // find new enabled flag
       nextStart = command.indexOf(',', nextStart);
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
     else
       Serial.println("ERROR");  
     }

   if (LoggingEnabled && (millis() - LastLogTime >= (100 * LoggingInterval)))  // measured in 1/10 sec
     {
     LastLogTime = millis();
     SendStateMessage();
     }
   
   if (HoloseatEnabled)
     {
     digitalWrite(LedPin, HIGH);
     // Don't process interrupts during calculations
     detachInterrupt(InterruptNumber);
   
     // set of conditions under which we have detected false "extra" steps
     // * both this step count and the last one are > 0
     // * this step count is > 1
     // * walk rate exceeds 2*TriggerRate (aka trigger period < min trigger
     boolean extraStep = ((StepCount > 0) && (LastStepCount > 0)) || (StepCount > 1) || (StepPeriodTriggered < MinTriggerPeriod);
   
     if (extraStep && (ExtraSteps < 2))
       {
       StepPeriodTriggered = LastStepPeriodTriggered;
       LastStepCount = 0;
       ExtraSteps++;
       } 
     else
       {
       ExtraSteps = 0;
       }
 
     StepPeriod = millis() - LastStepTime;
     StepsPerMin = (1.0/max(StepPeriod, StepPeriodTriggered)) * 60.0 * 1000.0;
   
     // If step rate is fast enough, send a "w";  note, only call the keyboard library
     // our walking state has changed. 
     WalkingState = StepsPerMin > TriggerCadence;
      
      if (!WalkingState)
        {  
        if (LastStepPeriod > StepPeriod)
          {
          WalkNSteps(20);
          }
        }  
      
     if (WalkingState != LastWalkingState)
       {
       LastWalkingState = WalkingState;
       if (WalkingState)
         {
         Keyboard.press(WalkCharacter);
         }
       else
         {
         Keyboard.releaseAll();
         }
       }
     
     LastStepCount = StepCount;
     StepCount = 0; 
     LastStepPeriod = StepPeriod;
     LastStepPeriodTriggered = StepPeriodTriggered;

     //Restart the interrupt processing
     attachInterrupt(InterruptNumber, StepsCalc, FALLING);
     }
   else  // Holoseat disabled
     {
     digitalWrite(LedPin, LOW);
     if (WalkingState)  // if we were walking, need to stop and need to clear state
       {
       Keyboard.releaseAll();
       InitializeWalkingVariables();
       }
     }
  }
  
void WalkNSteps(int n)
{
  Keyboard.press(WalkCharacter);
  delay(10*n);
  Keyboard.releaseAll(); 
}
 
void InitializeWalkingVariables()
{
   StepsPerMin = 0;
   LastStepTime = millis()-5000;          // initialize step times to 5 seconds in the past so we do not trigger walking on setup
   StepPeriodTriggered = ((1 / TriggerCadence) * 60 * 1000) + 100;  // initialize to just slower than walking speed
   LastStepPeriodTriggered = StepPeriodTriggered;
   StepPeriod = 0;
   LastStepPeriod = 0;
   StepCount = 0;
   LastStepCount = 0;
   WalkingState = false;
   LastWalkingState = false;
   ExtraSteps = 0; 
}

