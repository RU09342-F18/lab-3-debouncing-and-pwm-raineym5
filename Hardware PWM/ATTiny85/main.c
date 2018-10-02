#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL 


//LED: PB4
//BUT: PB3
//LOG LED values: 125-125log(10-n) for n=1:10
//1: 0
//2: 11
//3: 24
//4: 39
//5: 56
//6: 76
//7: 101
//8: 133
//9: 178
//10:255

volatile uint8_t lookupcounter = 4, incrementer=0,hit=0,miss=0,totalcounter=0;
const uint8_t LOOKUP[] = {0,11,24,39,56,76,101,133,178,255};

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
			OCR0A = LOOKUP[lookupcounter];
			
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

    PORTB = (1<<PB3);//turn on pullups
    
    GIMSK = (1<<PCIE);//set pin change interrupts
    PCMSK = (1<<PCINT3);//set pin change interrupt on pin PB3 in specific
    TCCR0A = (1<<WGM00)|(1<<COM0A1);//clear timer on compare with OCR0A
    TCCR0B = (1<<CS01)|(1<<CS00);///64 prescaler


    while(1){
    	sei();
    	asm("sleep");
	}
	return 0;
}

