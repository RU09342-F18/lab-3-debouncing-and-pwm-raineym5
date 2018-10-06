#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#define F_CPU 4800000UL 

//This program outputs a logarithmic PWM on pin PB1 with an input on pin PB3. The output LED is on PB4 and the button is on PB3.
//LED: PB4
//BUT: PB3 
//LOG LED values: 69-69log(10-n) for n=1:10
//0: 0
//1: 3
//2: 7
//3: 11
//4: 15
//5: 21
//6: 28
//7: 36
//8: 48
//9: 69


volatile uint8_t lookupcounter = 4, incrementer=0,hit=0,miss=0,totalcounter=0;
const uint8_t LOOKUP[] = {0,3,7,11,15,21,28,36,48,69};

ISR(PCINT0_vect){

	if(((PINB & (1<<PB3)))==(1<<PB3)){//button down only
		while(totalcounter < 30){//can do this in the ISR since it's the only interrupt. Still bad practice though
			for(uint8_t i=0;i<30;i++)
				asm("nop");
			totalcounter++;
			if((PINB & (1<<PB3))==(1<<PB3))//check for button down
				hit++;
			else
				miss++;
		}
		if(hit > miss){
			lookupcounter++;
			if(lookupcounter == 10)
				lookupcounter=0;
			OCR0B = LOOKUP[lookupcounter];
		}
		hit=0;
		miss=0;
		totalcounter=0;
	}
}

int main(void){

    DDRB = ~(1<<PB3);//all outputs except PB3
    OCR0A = 69;//CTC value for 1 KHz
	OCR0B = 33;
    PORTB = (1<<PB3);//turn on pullups
    
    GIMSK = (1<<PCIE);//set pin change interrupts
    PCMSK = (1<<PCINT3);//set pin change interrupt on pin PB3 in specific
    TCCR0A = (1<<WGM00)|(1<<COM0B1);//clear timer on compare with OCR0A
    TCCR0B = (1<<CS01)|(1<<WGM02);//8 prescalar, fast pwm


    while(1){
    	sei();
    	asm("sleep");//sleep mode idle
	}
	return 0;
}

