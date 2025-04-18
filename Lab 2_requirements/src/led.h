#ifndef LED_H  
#define LED_H  

// Function to initialize LED pins (PA0-PA3) as outputs
// This must be called once at the start of the program
void initLED();

// Function to display a binary pattern on LEDs connected to PA0-PA3
// Takes an unsigned char parameter (0-255) and uses the lower 4 bits
// to set the states of the four LEDs in a single operation
void turnOnLEDWithChar(unsigned char num);

#endif  
