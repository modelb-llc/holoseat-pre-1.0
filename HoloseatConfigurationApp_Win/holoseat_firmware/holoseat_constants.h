#ifndef holoseat_constants_h
#define holoseat_constants_h

// default parameter values for Holoseat
// What key is sent to move the character in the game
const char DefaultWalkCharacter = 'w';
// Is the Holoseat enabled by default?
const unsigned int DefaultHoloseatEnabled = 1; 
// How fast does the user need to pedal (in RPM) to trigger walking?
const unsigned int DefaultTriggerCadence = 75; 
// Is serial logging enabled by default?
const unsigned int DefaultLoggingEnabled = 0; 
// How long between messages in serial logging in deci-seconds (0.1 of a second)
const unsigned int DefaultLoggingInterval = 10; 

//serial port = 6;
//hardware type = leo;
// other boot parameters
const unsigned int SerialBaudRate = 57600;

#endif
