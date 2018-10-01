#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL 

volatile uint8_t incrementer=0,totalcounter=0;

ISR(TIMER0_OVF_vect){
	totalcounter++;
	if(PORTB && ~PORTB0)
		incrementer++;
	if(totalcounter==30){
		    TCCR0B = 0;//kill timer
	}
	
}
ISR(PCINT0_vect){
	if(PORTB && ~PORTB0){
		TCNT0 = 0;
	    TIMSK0 = (1<<TOIE0);//set timer overflow interrupts
	    TCCR0B = (1<<CS02)|(1<<CS00);//set clock divider (1024) for timer
	}else{
		if(totalcounter == incrementer)
			PORTB ^= PORTB1;
	}

}

int main(void){
    DDRB = 0xFD;//all outputs
    PCICR= (1<<PCIE0);//enable pin change interrupts
    PCMSK0 = (1<<PCINT0);//set pin change interrupt on pin 0
    while(1){
    	asm("SEI");
    	asm("sleep");
	}
}

