#define F_CPU 1000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

int digit[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
int state = 1;

ISR(INT0_vect){

	if(state == 0){

		PORTB = 0xFF;
		state = 1;
	}
	else{

		PORTB = 0;
		state = 0;
	}
}

int main(void){

	MCUCR |= (1<<ISC01);
	GICR |= (1<<INT0);
	sei();

    while(1){

		for(int i=0; i<10; i++){

			if(state == 0){

				continue;
			}

			PORTB = digit[i];
			_delay_ms(1000);
		}
    }
}
