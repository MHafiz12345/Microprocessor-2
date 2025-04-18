#include "switch.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void initSwitchPB3() {
    // Set PB3 as input
    // Clearing the bit in DDRB makes it an input
    DDRB &= ~(1 << DDB3);
    
    // Enable pull-up resistor on PB3
    // This keeps the pin HIGH when button is not pressed
    PORTB |= (1 << PORTB3);
    
    /* 
     Enable pin change interrupts for PCINT[7:0] group
     PB3 is part of this group as it's also known as PCINT3
     PCIE0 enables interrupts for the whole PCINT[7:0] group
     */
    PCICR |= (1 << PCIE0);
    
    // Enable interrupt specifically for PB3 (PCINT3)
    // This way only changes on PB3 will trigger the interrupt
    PCMSK0 |= (1 << PCINT3);
}   
