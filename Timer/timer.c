#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "lcd.h"

char buffer[7];
volatile int counter = 0;
volatile int second = 0;

ISR(TIMER0_OVF_vect){

	counter++;
	
	if(counter >= 4){
	
		second++;
	
	}
	
}

int main(void){
	
	lcd_init(LCD_DISP_ON);
	
	TCCR0 |= (1<<CS00) | (1<<CS02);
	TIMSK |= (1<<TOIE0);
	sei();
	
    while(1){
		
		itoa(counter,buffer,10);
		lcd_gotoxy(0,0);
		lcd_puts(buffer);
        
		_delay_ms(100);
    }
}