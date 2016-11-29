// Copyright Model B, LLC 2016.
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
// Holoseat Test Rig Firmware
// 
#include <AccelStepper.h> // requires AccelStepper v1.45

int buffer[20];
float deltaAngle = 3.14/51; //Arbitrary angle increment size
float angle = 0;
int amplitude = 100;
int timeStep = 0;
boolean realTime = false;  // set to true to send data to simplot for real time visualization
                           // set to false to use built-in serial monitor for data capture
unsigned long time;
float sample;
boolean experimentRunning = false;

int in1Pin = 12;
int in2Pin = 11;
int in3Pin = 10;
int in4Pin = 9;

float RPMtoSPS = 8.533;  // conversion factor from RPM to Steps/Sec

//Stepper motor(512, in1Pin, in2Pin, in3Pin, in4Pin);
AccelStepper stepper(AccelStepper::FULL4WIRE, in1Pin, in2Pin, in3Pin, in4Pin); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

void setup() 
{ 
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
 
  Serial.begin(57600);  
  //motor.setSpeed(20);
  stepper.setMaxSpeed(1024); 
  stepper.setAcceleration(100.0);
  //stepper.moveTo(0);
  stepper.setSpeed(0);

  Serial.println("r"); // send ready signal
} 

void loop() 
{ 
  if (Serial.available())
  {
    int steps = Serial.parseInt();
    //stepper.move(steps);
    stepper.setSpeed(steps * RPMtoSPS);
  }  
  
  stepper.runSpeed();
} 


