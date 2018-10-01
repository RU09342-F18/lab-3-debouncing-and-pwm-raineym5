#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL 

volatile uint8_t incrementer=0,totalcounter=0;

ISR(TIMER0_OVF_vect){
}
ISR(PCINT0_vect){
}

int main(void){
    DDRB = 0xFD;//all outputs
    while(1){
    	asm("SEI");
    	asm("sleep");
	}
}

