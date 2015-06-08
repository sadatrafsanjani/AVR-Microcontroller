#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void){

	DDRC = 0XFF;

    while(1){
		
         for(int i=0; i<8; i++){
		 
			PORTC = (1<<i);
			_delay_ms(100);
		 }
    }
}