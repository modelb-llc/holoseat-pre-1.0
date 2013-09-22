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
 
volatile int StepsCount;
volatile unsigned long LastDebounceTime;

long DebounceDelay;
unsigned int StepsPerMin;
unsigned int TriggerStepsPerMin;
unsigned long TimeOld;
unsigned int InterruptNumber;
unsigned int SampleRate;
boolean WalkingState;
boolean LastWalkingState;

void StepsCalc()
 {
   //Each rotation, this interrupt function is run twice, so take that into consideration for
   //calculating RPM
   //Update count
   
   if (millis() - LastDebounceTime > DebounceDelay)
     {
     StepsCount++;
     }
     
   LastDebounceTime = millis();  
 }

void setup()
 {
   //Interrupt 1 is digital pin 2, so that is where the reed switch is connected
   //Triggers on FALLING (change from HIGH to LOW)
   InterruptNumber = 1;
   attachInterrupt(InterruptNumber, StepsCalc, FALLING);

   StepsCount = 0;
   StepsPerMin = 0;
   TimeOld = 0;
   TriggerStepsPerMin = 80;
   SampleRate = 1;

   DebounceDelay = 100;    // the debounce time; increase if the output flickers
   LastDebounceTime = 0;
   WalkingState = false;
   LastWalkingState = false;
   
   Keyboard.begin();
 }

 void loop()
 {
   delay(1000 / SampleRate + 5);  // go slightly slower than max rate of sampling
   
   // Don't process interrupts during calculations
   detachInterrupt(InterruptNumber);
   
   StepsPerMin = 60*1000/(millis() - TimeOld)*StepsCount;
   TimeOld = millis();
   StepsCount = 0;

   // Calculate actual trigger rate based on potentiometer value
   // Then update sample rate ased on trigger rate
   unsigned int calculatedTriggerStepsPerMin = TriggerStepsPerMin;
   SampleRate = calculatedTriggerStepsPerMin / 60;
   
   // If step rate is fast enough, send a "w";  note, only call the keyboard library
   // our walking state has changed. 
   WalkingState = StepsPerMin > calculatedTriggerStepsPerMin;
   if (WalkingState != LastWalkingState)
     {
     LastWalkingState = WalkingState;
     if (WalkingState)
       Keyboard.press('w');
     else
       Keyboard.releaseAll();
     }

   //Restart the interrupt processing
   attachInterrupt(InterruptNumber, StepsCalc, FALLING);
  }
