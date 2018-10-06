# Hardware PWM
This is a relatively straight forward program that simply toggles an LED using the built-in timer0 module running in fastPWM. This was built using AVR-GCC 5.4.0 on linux using a makefile. 

I included videos for this program, but only this program since it's cumulative and the video files are massive relative to the rest of the project. Even downconverted from 4k60 to 640x480 10fps, they're still large. They should be available in this folder.

## ATtiny85
For this board, the code sets all outputs to zero except for the button, enabling the pullup resistor. It enables timer0 in fastPWM where TOP is 125 instead of 255. It then enables pin change interrupts and sets the timer perscalar, which enables the timer. 

The timer operates at 1 KHz at 50% duty cycle until a button interrupt is fired. When this happens, timer1 is turned on and used for debouncing. When the timer overflows, it checks whether the button is still pressed. After 30 overflows, if the amount of overflows where is was pressed is greater then the amount of times where it wasn't, then it counts as a button press. 

When a button press is registered, a counter increments and sets the fastPWM value to the next value in the array of logarithmic values. 
Any time the program is not in an ISR, the processor is sleeping in "idle", where the CPU is sleeping but all the peripherals are untouched.


## ATtiny13a
This code does exactly the same thing, except since this is a very basic microcontroller, it doesn't have a second timer. The debouncing code is done in the ISR. This is a bad practice, but since this is the only ISR executing in this program, there isn't a conflict. 
