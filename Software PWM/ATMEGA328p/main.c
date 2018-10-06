#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL 


//This code implements a software PWM with PB1 being the input and PB2 being the output LED. It operates timer0 as CTC at 1 KHz.
//PB1: button
//PB2: LED
//LOG LED values: 125-125log(10-n) for n=1:10
//1: 0
//2: 6
//3: 12
//4: 19
//5: 26
//6: 38
//7: 50
//8: 65
//9: 87
//10:125

volatile uint8_t lookupcounter = 4, incrementer=0,hit=0,miss=0,totalcounter=0;
const uint8_t LOOKUP[] = {0,6,12,19,26,38,50,65,87,125};
ISR(TIMER0_COMPB_vect){
	if(OCR0B != 125)
		PORTB &= ~(1<<PB2);
}
ISR(TIMER0_COMPA_vect){
	if(OCR0B != 0)
		PORTB |= (1<<PB2);
}

/////////////////

ISR(TIMER1_OVF_vect){
	totalcounter++;
	if((PINB & (1<<PB3))==0)
		hit++;
	else
		miss++;
	if(totalcounter==30){
		if(hit >= miss){
			PORTB ^= (1<<PB0);
		}
		TCCR1B = 0;//kill timer
    	PCMSK0 = (1<<PCINT0);//set pin change interrupt on PB0
		hit=0;
		miss=0;
		totalcounter=0;
	}
	
}
ISR(PCINT0_vect){
	if((PINB & (1<<PB3))==0){
		TCNT1 = 0;
		PCMSK0 = 0;//clear pin change interrupts
	    TIMSK0 = (1<<TOIE0);//set timer overflow interrupts
	    TCCR1B = (1<<CS01);//set clock divider (8) for timer
	}

}

int main(void){
    DDRB = ~(1<<PB1);//all outputs except PB1
    PORTB = (1<<PB1);//set pullup
    PCICR = (1<<PCIE0);//enable pin change interrupts
    PCMSK0 = (1<<PCINT0);//set pin change interrupt on PB0
 
    OCR0A = 125;//CTC value for 1 KHz
    OCR0B = 62;//CTC value for 50% duty cycle
    
    TCCR0A = (1<<WGM01);//clear timer on compare with OCR0A
    TCCR0B = (1<<CS01)|(1<<CS00);///64 prescaler
    TIMSK0 =(1<<OCIE0A)|(1<<OCIE0B);//timer match b interrupt
    
    
    
    while(1){
    	sei();
    	asm("sleep");
	}
}

