#ifndef SWITCH_H  
#define SWITCH_H  

// Function to initialize the push button on pin PB3
// - Configures PB3 as an input with pull-up resistor
// - Enables pin change interrupt for PB3 (PCINT3)
// This must be called once at the start of the program
void initSwitchPB3();

#endif  
