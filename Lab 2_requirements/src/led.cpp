// led.cpp - Controls LEDs connected to PA0, PA1, PA2, and PA3
// ECE372A Lab 2

// Author:   Muhammad Hafiz      
// Net ID:   muhammadhafiz      
// Date:       03 March 2025     
// Assignment:     Lab 2
//----------------------------------------------------------------------//

#include "led.h"
#include <avr/io.h>

void initLED() {
    /* 
     Set pins PA0-PA3 as outputs
     DDRx sets the direction of pins (1=output, 0=input)
     */
    DDRA |= (1 << DDA0) | (1 << DDA1) | (1 << DDA2) | (1 << DDA3);
    
}

void turnOnLEDWithChar(unsigned char num) {
    /* 
     This function updates all 4 LEDs in one operation:
     PORTA & 0xF0 keeps the upper 4 bits of PORTA unchanged
     (0xF0 in binary is 11110000, masking to keep bits 4-7)
     num & 0x0F gets the lower 4 bits of num
     (0x0F in binary is 00001111, masking to get bits 0-3)
     Then OR combines the values
     */
    PORTA = (PORTA & 0xF0) | (num & 0x0F);
    
    // Implemented in one line as required by the lab2 requirements
}