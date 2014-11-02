/*
Holoseat Test Rig Firmware

based on:
* SimPlot Demo Arduino Sketch - Generates and sends out 4 channels of data to be plotted using SimPlot.
* Adafruit Arduino - Lesson 16. Stepper

*/
#include <Stepper.h>

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

Stepper motor(512, in1Pin, in2Pin, in3Pin, in4Pin);

void setup() 
{ 
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
 
  Serial.begin(57600);  
  motor.setSpeed(20); 
} 

void loop() 
{ 
  if (Serial.available())
  {
    int steps = Serial.parseInt();
    motor.step(steps);
  }  
 
/*  
  int data1;
  int data2;
  int data3;
  int data4;
  
  time = millis();
  if ((time < 2000) || (time >= 32000)) 
  { 
    experimentRunning = false;  // collect data for 30 seconds (with 2 s delay before starting)
  }
  else
  {
    experimentRunning = true;
  }
  
  if (time < 9500)
  {
    sample = 2;  // run sample 1
  }
  else if (time < 15000)
  {
    sample = 1.5;  // run sample 2
  }
  else if (time < 24500)
  {
    sample = 4;   // run sample 3
  }
  else if (time < 32000)
  {
    sample = 1.1; // run sample 4
  }

  if (experimentRunning)
  { 
    //Generating data that will be plotted
    data1 = amplitude * sin(angle);
    data2 = amplitude * cos(angle);
 
    data3 = (amplitude/sample) * sin(angle);
    data4 = (amplitude/2) * cos(angle);
 
    angle = angle + deltaAngle;
 
    plot(data1,data2,data3,data4, realTime);
    timeStep = timeStep + 1;
  }
  
  delay(100); //Need some delay else the program gets swamped with data  
*/
} 

void plot(int data1, int data2, int data3, int data4, boolean simplot)
{
  if (simplot)
  {
    int pktSize;
 
    buffer[0] = 0xCDAB;             //SimPlot packet header. Indicates start of data packet
    buffer[1] = 4*sizeof(int);      //Size of data in bytes. Does not include the header and size fields
    buffer[2] = data1;
    buffer[3] = data2;
    buffer[4] = data3;
    buffer[5] = data4;
   
    pktSize = 2 + 2 + (4*sizeof(int)); //Header bytes + size field bytes + data
 
    //IMPORTANT: Change to serial port that is connected to PC
    Serial.write((uint8_t * )buffer, pktSize);
  }
  else
  {
    Serial.print(timeStep);
    Serial.print(",");
    Serial.print(data1);
    Serial.print(",");
    Serial.print(data2);
    Serial.print(",");
    Serial.print(data3);
    Serial.print(",");
    Serial.println(data4);
  }  
}
