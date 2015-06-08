#define F_CPU 1000000UL

#define setBit(port,bit)(_SFR_BYTE(port)|=(1<<bit))
#define clearBit(port,bit)(_SFR_BYTE(port)&=~(1<<bit))

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

ISR(INT0_vect){

	setBit(PORTC,PC1);

	//PORTC |= (1<<PC1);

	//PORTC ^= (1<<PC1);
}

ISR(INT1_vect){

	clearBit(PORTC,PC1);

	//PORTC &= ~(1<<PC1);
}

int main(void){

	DDRC |= (1<<PC1);

	MCUCR |= (1<<ISC00) | (1<<ISC01);
	GICR |= (1<<INT0) | (1<<INT1);
	sei();

	while(){

	}
}
