#ifndef holoseat_constants_h
#define holoseat_constants_h

// default parameter values for Holoseat
const char DefaultWalkCharacter = 'w';  // What key is sent to move the character in the game
const unsigned int DefaultHoloseatEnabled = 1; // Is the Holoseat enabled by default?
const unsigned int DefaultTriggerCadence = 75; // How fast does the user need to pedal (in RPM) to trigger walking?
const unsigned int DefaultLoggingEnabled = 0; // Is serial logging enabled by default?
const unsigned int DefaultLoggingInterval = 10; // How long between messages in serial logging in deci-seconds (0.1 of a second)

// other boot parameters
const unsigned int SerialBaudRate = 115200;

#endif
