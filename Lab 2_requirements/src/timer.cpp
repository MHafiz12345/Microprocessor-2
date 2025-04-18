// Author:   Muhammad Hafiz      
// Net ID:   muhammadhafiz      
// Date:       03 March 2025    
// Assignment:     Lab 2
//----------------------------------------------------------------------//

#include "timer.h"
#include <avr/io.h>          // For AVR I/O definitions
#include <avr/interrupt.h>   // For interrupt handling
#include <Arduino.h>

// Counter for tracking milliseconds in the timer interrupt
// "volatile" tells compiler this changes in an interrupt
volatile unsigned int ms_counter = 0;

void initTimer0() {
    /* 
     Setup Timer0 in CTC (Clear Timer on Compare match) mode
     This mode resets the timer when it matches OCR0A value
     */
    
    // Set WGM00=0, WGM01=1, WGM02=0 for CTC mode
    TCCR0A &= ~(1 << WGM00);  // Clear bit WGM00
    TCCR0A |= (1 << WGM01);   // Set bit WGM01
    TCCR0B &= ~(1 << WGM02);  // Clear bit WGM02
    
    /* 
     For a 16MHz clock with prescaler of 64:
     (16,000,000 / 64) / 250 = 1000Hz = 1ms 
     Subtract 1 because the count starts at 0
     */
    OCR0A = 249;  // Target value for comparison (250 counts: 0-249)
    
    // Enable the Compare Match A interrupt
    // This makes Timer0 trigger the ISR every 1ms
    TIMSK0 |= (1 << OCIE0A);
    
    /* 
     Start the timer with prescaler set to 64
     CS00=1 and CS01=1 sets the prescaler to 64
     The prescaler is set here and left running
     because with interrupts, consistent timing is needed
     */
    TCCR0B |= (1 << CS01) | (1 << CS00);
    TCCR0B &= ~(1 << CS02);
}

void delayMs(unsigned int delay) {
    // Reset the counter at the start of delay
    ms_counter = 0;
    
    /* 
     Wait until counter reaches desired delay amount
     The counter is incremented in the timer ISR
     This is simpler than polling because all the
     timer management happens in the interrupt
     */
    while (ms_counter < delay);
}