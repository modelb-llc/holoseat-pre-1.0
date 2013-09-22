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
 
volatile float StepsCount;
volatile unsigned long LastDebounceTime;

long DebounceDelay;
float StepsPerMin;
float TriggerStepsPerMin;
unsigned long TimeOld;
unsigned int InterruptNumber;
float SampleRate;
unsigned long DelayTime; 
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
#ifdef debug
   //Initialize serial and wait for port to open:
   Serial.begin(9600); 
   while (!Serial) 
     {
     ; // wait for serial port to connect. Needed for Leonardo only
     }
     Serial.println("Debugger Connected");
#endif
   
   //Interrupt 1 is digital pin 2, so that is where the reed switch is connected
   //Triggers on FALLING (change from HIGH to LOW)
   InterruptNumber = 1;
   attachInterrupt(InterruptNumber, StepsCalc, FALLING);

   StepsCount = 0;
   StepsPerMin = 0;
   TimeOld = 0;
   TriggerStepsPerMin = 80;
   SampleRate = 1;
   DelayTime = 1000 / SampleRate + 5;

   DebounceDelay = 100;    // the debounce time; increase if the output flickers
   LastDebounceTime = 0;
   WalkingState = false;
   LastWalkingState = false;
   
   Keyboard.begin();
 }

 void loop()
 {
   delay(DelayTime);  // go slightly slower than max rate of sampling
   
   // Don't process interrupts during calculations
   detachInterrupt(InterruptNumber);
   
   unsigned int timeStep = millis() - TimeOld;
   StepsPerMin = StepsCount * 60.0 * 1000.0 / timeStep;
   TimeOld = millis();

   // Calculate actual trigger rate based on potentiometer value
   // Then update sample rate ased on trigger rate
   float calculatedTriggerStepsPerMin = TriggerStepsPerMin;
   SampleRate = calculatedTriggerStepsPerMin / 60;
   DelayTime = floor(1000 / SampleRate) + 5;
   
   // If step rate is fast enough, send a "w";  note, only call the keyboard library
   // our walking state has changed. 
   WalkingState = StepsPerMin > calculatedTriggerStepsPerMin;
   
#ifdef debug
   if (LastWalkingState || (StepsPerMin > 0.))
     {
     Serial.print("Delay=");
     Serial.print(DelayTime);
     Serial.print(" | LWS=");
     Serial.print(LastWalkingState);
     Serial.print(" | WS=");
     Serial.print(WalkingState);
     Serial.print(" | Steps=");
     Serial.print(StepsCount,0);
     Serial.print(" | TimeStep=");
     Serial.print(timeStep);
     Serial.print(" | SPM=");
     Serial.print(StepsPerMin,1);
     Serial.print(" Trigger=");
     Serial.println(calculatedTriggerStepsPerMin,1);
     }
#endif
   
   StepsCount = 0;
   
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
