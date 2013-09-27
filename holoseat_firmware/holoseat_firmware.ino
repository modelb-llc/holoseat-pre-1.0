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
 *  - http://www.arduino.cc/en/Tutorial/Potentiometer
 *  - http://www.arduino.cc/en/Tutorial/Switch
 */
 
//#define debug
 
volatile unsigned long LastDebounceTime;
volatile unsigned long LastStepTime;
volatile unsigned long StepPeriodTriggered;

long DebounceDelay;
float StepsPerMin;
float TriggerStepsPerMin;
unsigned int InterruptNumber;
boolean WalkingState;
boolean LastWalkingState;
unsigned long StepPeriod;
unsigned long  LastStepPeriod;
char WalkCommandChar;

void StepsCalc()
 {
   if (millis() - LastDebounceTime > DebounceDelay)
     {
     StepPeriodTriggered = millis() - LastStepTime;
     LastStepTime = millis();
     }
     
   LastDebounceTime = millis();  
 }

void setup()
 {
   WalkCommandChar = 'w';
   TriggerStepsPerMin = 75;
#ifdef debug
   //Initialize serial and wait for port to open:
   Serial.begin(9600); 
   while (!Serial) 
     {
     ; // wait for serial port to connect. Needed for Leonardo only
     }
     Serial.println("Debugger Connected");
     Serial.println("==================");
     Serial.println("Setup");
     Serial.println("------------------------");
     Serial.print("Walk Char= ");
     Serial.println(WalkCommandChar);
     Serial.print("Default TriggerStepsPerMin= ");
     Serial.println(TriggerStepsPerMin);
     Serial.println("------------------------");
#endif
   
   //Interrupt 1 is digital pin 2, so that is where the reed switch is connected
   //Triggers on FALLING (change from HIGH to LOW)
   InterruptNumber = 1;
   attachInterrupt(InterruptNumber, StepsCalc, FALLING);

   StepsPerMin = 0;
   LastStepTime = millis()-5000;          // initialize step times to 5 seconds in the past so we do not trigger walking on setup
   StepPeriodTriggered = millis()-5000;
   StepPeriod = 0;
   LastStepPeriod = 0;

   DebounceDelay = 100;    // the debounce time; increase if walking jitters
   LastDebounceTime = 0;
   WalkingState = false;
   LastWalkingState = false;
   
   Keyboard.begin();
 }

 void loop()
 {
   delay(DebounceDelay+50);  // delay should be longer than the debounce time
   
   // Don't process interrupts during calculations
   detachInterrupt(InterruptNumber);
   
   StepPeriod = millis() - LastStepTime;
   StepsPerMin = (1.0/max(StepPeriod, StepPeriodTriggered)) * 60.0 * 1000.0;

   // Calculate actual trigger rate based on potentiometer value
   // Then update sample rate ased on trigger rate
   float calculatedTriggerStepsPerMin = TriggerStepsPerMin;
   
   // If step rate is fast enough, send a "w";  note, only call the keyboard library
   // our walking state has changed. 
   WalkingState = StepsPerMin > calculatedTriggerStepsPerMin;
   
   if ((LastWalkingState || (StepsPerMin > (calculatedTriggerStepsPerMin/2))))
      LogDebugInfo(calculatedTriggerStepsPerMin);
      
    if (!WalkingState)
     {  
     if (LastStepPeriod > StepPeriod)
       {
       LogDebugInfo(0);
       WalkNSteps(20);
       }
     }   
      
   if (WalkingState != LastWalkingState)
     {
     LastWalkingState = WalkingState;
     if (WalkingState)
       Keyboard.press(WalkCommandChar);
     else
       Keyboard.releaseAll();
     }

   LastStepPeriod = StepPeriod;

   //Restart the interrupt processing
   attachInterrupt(InterruptNumber, StepsCalc, FALLING);
  }
  
void WalkNSteps(int n)
{
  Keyboard.press(WalkCommandChar);
  delay(10*n);
  Keyboard.releaseAll(); 
}
 
 
 void LogDebugInfo(float spm)
 {
 #ifdef debug 
   Serial.print("LWS=");
   Serial.print(LastWalkingState);
   Serial.print(" | WS=");
   Serial.print(WalkingState);
   Serial.print(" | LastPeriod=");
   Serial.print(LastStepPeriod);
   Serial.print(" | Period=");
   Serial.print(StepPeriod);
   Serial.print(" | PeriodT=");
   Serial.print(StepPeriodTriggered);
   Serial.print(" | SPM=");
   Serial.print(StepsPerMin,1);
   Serial.print(" Trigger=");
   Serial.println(spm,1);
#endif
 }

