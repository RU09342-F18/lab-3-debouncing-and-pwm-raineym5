# Software PWM
This is a relatively straight forward program that simply toggles an LED using the built-in timer0 module running in CTC (clear timer on compare). This was built using AVR-GCC 5.4.0 on linux using a makefile. 

## ATtiny85
For this board, the code sets all outputs to zero except for the button, enabling the pullup resistor. It enables timer0 in CTC where TOP is 125 instead of 255. It then enables pin change interrupts, compare interrupts and sets the timer perscalar, which enables the timer. 

The timer operates at 1 KHz at 50% duty cycle until a button interrupt is fired. When this happens, timer1 is turned on and used for debouncing. When the timer overflows, it checks whether the button is still pressed. After 30 overflows, if the amount of overflows where is was pressed is greater then the amount of times where it wasn't, then it counts as a button press. 

When a button press is registered, a counter increments and sets the CTC value to the next value in the array of logarithmic values. 
Any time the program is not in an ISR, the processor is sleeping in "idle", where the CPU is sleeping but all the peripherals are untouched.


## ATMEGA328p
This code does exactly the same thing, except it has a few different register names. 
