#include <avr/io.h>         
#include <avr/interrupt.h>  
#include "led.h"            
#include "switch.h"         
#include "timer.h"         

/* 
 * States for button handling state machine
 * This helps track what's happening with the button
 */
typedef enum {
    WAIT_PRESS,         // Waiting for button to be pressed
    DEBOUNCE_PRESS,     // Wait a bit after button press to avoid bounce
    WAIT_RELEASE,       // Waiting for button to be released
    DEBOUNCE_RELEASE    // Wait a bit after release to avoid bounce
} State;

// This variable is used by the timer interrupt to count milliseconds
extern volatile unsigned int ms_counter;  // "extern" means it's defined in timer.cpp

// Flag that gets set when button is pressed
// "volatile" tells compiler this can change in an interrupt
volatile bool buttonPressed = false;  

// How fast the LEDs will update (start at 100ms)
unsigned int blinkSpeed = 100;        

// Current value to display on LEDs (0-15)
unsigned char counterValue = 0;       

// Start in the WAIT_PRESS state
State buttonState = WAIT_PRESS;       

int main() {
    // Set up all hardware
    initLED();         // Configure LED pins as outputs
    initSwitchPB3();   // Configure the button with pull-up and interrupt
    initTimer0();      // Set up Timer0 with interrupts for timing
    sei();             // Enable global interrupts - now ISRs can run
    
    
    // Run forever
    while (1) {
        // Update the LEDs to show current counter value
        // This function handles the bit manipulation in one line
        turnOnLEDWithChar(counterValue);
        
        // Button state machine to handle press, release, and debouncing
        switch (buttonState) {
            case WAIT_PRESS:
                // If ISR detected a button press...
                if (buttonPressed) {
                    // Move to debounce state
                    buttonState = DEBOUNCE_PRESS;
                    buttonPressed = false;  // Reset the flag for next time
                }
                break;
                
            case DEBOUNCE_PRESS:
                // Wait 30ms to make sure button press wasn't just noise
                delayMs(30);  
                
                /* 
                 Toggle the speed as soon as the button press is debounced
                 This makes the speed change immediately instead of waiting for release
                 Placed here rather than WAIT_PRESS to avoid multiple toggles from button bounce
                 */
                blinkSpeed = (blinkSpeed == 100) ? 200 : 100;
                
                // Now wait for button to be released
                buttonState = WAIT_RELEASE;
                break;
                
            case WAIT_RELEASE:
                // Check if button is released (PB3 is high due to pull-up)
                // PINB reads the actual pin state, and PINB3 is bit 3
                if (PINB & (1 << PINB3)) {
                    // Button released, go to debounce release state
                    buttonState = DEBOUNCE_RELEASE;
                }
                break;
                
            case DEBOUNCE_RELEASE:
                // Wait 20ms to make sure release wasn't just noise
                delayMs(20);  
                
                // Go back to waiting for next press
                // Speed already toggled in DEBOUNCE_PRESS state for immediate response
                buttonState = WAIT_PRESS;
                break;
        }
        
        // Wait for the current blink speed before updating counter
        // This controls how fast the binary counter increments
        delayMs(blinkSpeed);
        
        // Increment counter and wrap around when it reaches 16
        counterValue++;
        if (counterValue > 0x0F) {  // 0x0F is hexadecimal for 15
            counterValue = 0;
        }
        
    }
    
    return 0;  // This will never actually run (infinite loop above)
}

/* 
 * This function runs when the button's pin changes state
 * PCINT0_vect is chosen because PB3 is part of PCINT[7:0] pins
 */
ISR(PCINT0_vect) {
    // Check if button is pressed (PB3 is low)
    // Since a pull-up resistor is used, the pin is normally HIGH
    // and goes LOW when the button is pressed
    if (!(PINB & (1 << PINB3))) {
        buttonPressed = true;  // Set flag for main loop to handle
    }
}

/* 
 * Timer0 compare match interrupt happens every 1 millisecond
 * TIMER0_COMPA_vect is used because Timer0 is in CTC mode
 */
ISR(TIMER0_COMPA_vect) {
    ms_counter++;  // Count each millisecond
}
