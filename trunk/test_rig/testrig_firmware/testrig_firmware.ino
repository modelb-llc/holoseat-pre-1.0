/*
Holoseat Test Rig Firmware

based on:
* SimPlot Demo Arduino Sketch - Generates and sends out 4 channels of data to be plotted using SimPlot.
* Adafruit Arduino - Lesson 16. Stepper
* AccelStepper - ConstantSpeed

*/
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


