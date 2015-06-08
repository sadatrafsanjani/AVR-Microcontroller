#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void){
	
	DDRC |= (1<<PC0);
	
    while(1){
		
		if(PINA & (1<<PC0)){
		
			PORTC |= (1<<PC0);
			_delay_ms(500);
			//PORTC &= ~(1<<PC0);
			//_delay_ms(500);	
		}
		else{
			
			PORTC &= ~(1<<PC0);
		}
    }
}