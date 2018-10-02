#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL 

//button: PB0
//LED: PB1
volatile uint8_t hit=0,miss=0,totalcounter=0;

ISR(TIMER1_OVF_vect){
	totalcounter++;
	if((PINB & (1<<PB3))==0)
		hit++;
	else
		miss++;
	if(totalcounter==30){
		if(hit >= miss){
			PORTB ^= (1<<PB4);
		}
		TCCR1 = 0;//kill timer
		GIMSK |= (1<<PCIE);//set pin change interrupts
		hit=0;
		miss=0;
		totalcounter=0;
	}
}
ISR(PCINT0_vect){

	if((PINB & (1<<PB3))==0){

    	GIMSK =0;//clear pin change interrupts
		TCNT1 = 0;
	    TIMSK = (1<<TOIE1);//set timer overflow interrupts
	    TCCR1 = (1<<CS12);//set clock divider (8) for timer
	}
}

int main(void){
    DDRB = ~(1<<PB3);//all outputs except PB3
    PORTB = ~(1<<PB3);
    GIMSK = (1<<PCIE);//set pin change interrupts
    PCMSK = (1<<PCINT3);//set pin change interrupt on pin 3
    PORTB = (1<<PORTB3);//set the pullup on PB3
    while(1){
    	sei();
    	asm("sleep");
	}
}

