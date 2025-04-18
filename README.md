# Lab 2: Binary Counter with Interrupt-Driven Speed Control

![Binary Counter Board](https://github.com/user-attachments/assets/17f0c9b1-890f-472c-a77a-7557a210cae5)

## 🔧 Overview

This project implements a 4-bit **binary counter** using an AVR microcontroller. The current counter value (0–15) is displayed on four LEDs connected to Port A. The update rate of the counter can be toggled by pressing a button connected to PB3, utilizing **pin change interrupts** and a **timer-based delay system**.

The lab demonstrates practical use of **interrupts**, **state machines**, and **timer configurations**, making it a solid introduction to responsive embedded system design.

## 🎯 Project Behavior

* LEDs show a 4-bit binary value that **increments from 0 to 15**, then wraps back to 0.
* The counter updates every **100ms** by default.
* Pressing the button **toggles the update speed** between 100ms and 200ms.
* Button input is handled using **interrupts and a debounce state machine**.

## ⚙️ Functional Breakdown

### `initLED()` and `turnOnLEDWithChar(unsigned char num)`
* `initLED()`: Configures PA0–PA3 as outputs.
* `turnOnLEDWithChar()`: Updates all 4 LED bits in one line using masking and OR operations to preserve upper bits of PORTA.

### `initSwitchPB3()`
* Sets PB3 as input with a pull-up resistor.
* Enables **pin change interrupt** specifically for PB3 (PCINT3).
* PB3 goes LOW when pressed and HIGH when released.

### `initTimer0()` and `delayMs(unsigned int)`
* Configures **Timer0 in CTC mode** to generate 1ms interrupts.
* `delayMs()` uses a shared `ms_counter` updated by the timer ISR to manage blocking delays.

### Button Handling State Machine
Managed using four states:
* `WAIT_PRESS`: Waiting for button press
* `DEBOUNCE_PRESS`: Short delay to filter bounce
* `WAIT_RELEASE`: Waiting for button release
* `DEBOUNCE_RELEASE`: Final debounce before restarting the cycle

Speed toggle is handled in `DEBOUNCE_PRESS` for immediate effect.

## 🛠️ Key Features

* Fully interrupt-driven button input (no polling)
* Precise millisecond timing via Timer0
* LED output with efficient masking logic
* Debounced input handling using state machine
* Modular and readable codebase

## 📁 File Structure

```
├── led.c / led.h         # LED output logic
├── switch.c / switch.h   # Button input and interrupt setup
├── timer.c / timer.h     # Timer0 config and delay function
├── main.c               # Core logic, state machine, counter
```

## 🧠 Concepts in Use

* Pin change interrupts (`PCINTx`)
* Debouncing and state machines
* CTC (Clear Timer on Compare match) mode
* Efficient bit masking
* Global interrupt management (`sei()`, `ISR()` macros)

## 🔌 Hardware Requirements

* AVR ATmega2560 microcontroller board
* 4 LEDs connected to PA0-PA3
* Push button connected to PB3
* Power supply (5V)
