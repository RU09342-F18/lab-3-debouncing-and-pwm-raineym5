#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL 


//LED: PB4 
//BUT: PB3
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
		PORTB &= ~(1<<PB4);
}
ISR(TIMER0_COMPA_vect){
	if(OCR0B != 0)
		PORTB |= (1<<PB4);
}
ISR(PCINT0_vect){

	if((PINB & (1<<PB3))==0){

    	GIMSK =0;//clear pin change interrupts
		TCNT1 = 0;
	    TIMSK |= (1<<TOIE1);//set timer overflow interrupts
	    TCCR1 = (1<<CS12);//set clock divider (8) for timer
	}
}

ISR(TIMER1_OVF_vect){
	totalcounter++;
	if((PINB & (1<<PB3))==0)
		hit++;
	else
		miss++;
	if(totalcounter==30){
		if(hit >= miss){
		
			lookupcounter++;
			if(lookupcounter == 10)
				lookupcounter=0;
			OCR0B = LOOKUP[lookupcounter];
			
		}
		TCCR1 = 0;//kill timer
		GIMSK |= (1<<PCIE);//set pin change interrupts
		hit=0;
		miss=0;
		totalcounter=0;
	}
}
int main(void){

    DDRB = ~(1<<PB3);//all outputs except PB3
    OCR0A = 125;//CTC value for 1 KHz
    OCR0B = 62;//CTC value for 50% duty cycle
    PORTB = (1<<PB3);//turn on pullups
    
    GIMSK = (1<<PCIE);//set pin change interrupts
    PCMSK = (1<<PCINT3);//set pin change interrupt on pin PB3 in specific
    TCCR0A = (1<<WGM01);//clear timer on compare with OCR0A
    TCCR0B = (1<<CS01)|(1<<CS00);///64 prescaler
    TIMSK =(1<<OCIE0A)|(1<<OCIE0B);//timer match b interrupt

    while(1){
    	sei();
    	asm("sleep");
	}
	return 0;
}

