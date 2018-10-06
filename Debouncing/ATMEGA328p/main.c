#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL 
//This program debounces an input and toggles an LED. The output LED is on PB2 and the button is on PB1.
//PB1: button
//PB2: LED
volatile uint8_t hit=0,miss=0,totalcounter=0;
ISR(TIMER0_OVF_vect){
	totalcounter++;
	if((PINB & (1<<PB3))==0)
		hit++;
	else
		miss++;
	if(totalcounter==30){
		if(hit >= miss){
			PORTB ^= (1<<PB0);
		}
		TCCR0B = 0;//kill timer
    	PCMSK0 = (1<<PCINT0);//set pin change interrupt on PB0
		hit=0;
		miss=0;
		totalcounter=0;
	}
	
}
ISR(PCINT0_vect){
	if((PINB & (1<<PB3))==0){
		TCNT0 = 0;
		PCMSK0 = 0;//clear pin change interrupts
	    TIMSK0 = (1<<TOIE0);//set timer overflow interrupts
	    TCCR0B = (1<<CS01);//set clock divider (8) for timer
	}

}

int main(void){
    DDRB = ~(1<<PB1);//all outputs
    PORTB = (1<<PB1);
    PCICR = (1<<PCIE0);//enable pin change interrupts
    PCMSK0 = (1<<PCINT0);//set pin change interrupt on PB0
    while(1){
    	asm("SEI");
    	asm("sleep");
	}
}


