#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

int digit[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

int main(void){

     DDRB = 0xFF;

     while(1){

          for(int i=0; i<10; i++){

			PORTB = digit[i];
			_delay_ms(500);
          }
     }
}
