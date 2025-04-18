//----------------------------------------------------------------------//

// Author:   Muhammad Hafiz      
// Net ID:   muhammadhafiz      
// Date:        03 March 2025     
// Assignment:     Lab 2
//----------------------------------------------------------------------//


#ifndef TIMER_H  
#define TIMER_H  
#include <avr/io.h>  

// Function to initialize Timer0 in CTC mode
// - Sets up the timer but does not start it
// - Configures for precise 1ms timing intervals
// This must be called once at the start of the program
void initTimer0();

// Function to create a precise millisecond delay
// Parameters:
//   delay - Number of milliseconds to wait (works reliably up to 200ms)
// Uses Timer0 to create accurate timing regardless of CPU operations
void delayMs(unsigned int delay);

#endif  