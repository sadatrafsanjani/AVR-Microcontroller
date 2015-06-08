#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lcd.h"

char buffer[7];

int main(void){
	
	MCUCSR |= 1<<JTD;
	MCUCSR |= 1<<JTD;
	
	lcd_init(LCD_DISP_ON);
	
	lcd_gotoxy(14,0);
	lcd_putc('T');
	
	_delay_ms(500);
	lcd_clrscr();
	
	lcd_gotoxy(0,0);
	lcd_puts("RAFSANJANI");
	
	_delay_ms(300);
	lcd_clrscr();
	
	int var = 123;
	itoa(var,buffer,10);
	lcd_puts(buffer);	
	
    while(1){
		
		_delay_ms(300);
		lcd_clrscr();
		
        for(char i='a'; i<'z'; i++){
		 
			lcd_putc(i);
			_delay_ms(200);
		 }
		 
		 lcd_clrscr();
		 lcd_gotoxy(3,0);
		 
		 for(char i='0'; i<='9'; i++){
			 
			 lcd_putc(i);
			 _delay_ms(200);
		 }
		 
		 lcd_clrscr();
		 lcd_gotoxy(3,0);
		 
		 for(char i='0'; i<='9'; i++){
			 
			 lcd_putc(i);
			 _delay_ms(200);
			 lcd_clrscr();
		 }
    }
}