#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL 

volatile uint8_t incrementer=0,totalcounter=0;

ISR(TIMER0_COMPB_vect){
	PORTB ^= 0x01;
}
ISR(PCINT0_vect){
	if(PORTB && PORTB0){
	OCR0B += 25;
	if(OCR0B >= 250)
		OCR0B = 0;
	}

}

int main(void){
    DDRB = 0xFD;//all outputs
    OCR0A = 250;//CTC value for 1 KHz
    OCR0B = 125;//CTC value for 50% duty cycle
    GIMSK = (1<<PCIE);//set pin change interrupts
    PCMSK = (1<<PCINT0);//set pin change interrupt on pin 0
    TCCR0A = (1<<WGM01);//clear timer on compare
    TCCR0B = (1<<CS02);///256 prescaler
    TIMSK0 = (1<<OCIE0B);

	
    TIMSK0 = (1<<OCIE0A
    while(1){
    	asm("sei");
    	asm("sleep");
	}
}

