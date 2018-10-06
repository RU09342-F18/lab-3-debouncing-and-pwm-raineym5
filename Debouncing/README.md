# Debouncing
This is a relatively straight forward program that simply toggles an LED using the built-in timer0 module running in fastPWM. This was built using AVR-GCC 5.4.0 on linux using a makefile. 

## ATtiny85
For this board, the code sets all outputs to zero except for the button, enabling the pullup resistor. It then enables pin change interrupts, and goes to sleep, waiting for a button interrupt. 

When a button interrupt occurs, the ISR checks if it is a low-high or high-low transition. Since the button pulls down the input, the only transition we care about here is the high-low transition. When this happens, it enables timer0 and waits for an overflow. On each overflow, the timer ISR checks if the button is pressed. After 30 overflows, the timer is disabled and if the amount of presses is higher than the amount of times the button isn't pressed, it counts as a button press and the code toggles the LED.

Any time the code is not in an ISR, the program is sleeping in "IDLE".

## ATMEGA328P
This code does exactly the same thing, but using different register names. 
