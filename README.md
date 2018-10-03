# Lab 3: Timers and PWM
In this lab, the following three projects are completed for two different microcontrollers:
* Debounce a switch input using the Timer Modules and interrupts
* Implement Software based PWM using the built in Timer Modules
* Implement Hardware based PWM using the timer modules

There is one key difference in this lab. Instead of MSP43x microcontrollers, this lab will be using AVR microcontrollers. I've used AVR in assembly/C for about 5 years and wish to continue using it.

This lab will use the following micros:
* ATMega328PB
* ATTiny85
* ATTiny13A

And Possibly
* ATTiny88
* ATTiny24
* ATTiny10

## Advantages of AVR
AVR has several advantages. These include:
* Significantly more compiler/community support and much better compiler
* Significantly more current sourcing and sinking (20 mA/GPIO, 200mA total for ALL avrs)
* Generally lower cost
* (typically) more flash, ram, eeprom
* 8-bit (useful for uart)
* Generates significantly smaller code
* 5v tolerant (1.8 - 5.5v)
* More tolerant BOD
* 2-cycle 16-bit arithmetic and more advanced hardware multiplier
* Almost all uC's have DIP variants making prototyping easier
* More advanced UART transceiver
* Significantly more ESD-resistant

## Advantages of MSP430
There is not much of a difference between the two, but the MSP430 does have a few areas that it really shines. These include:
* 16 bit hardware
* More peripherals
* FRAM
* 12 (vs 10) bit ADC
* Less feature creep
* Moderately lower power
* MUCH faster clock startup time

