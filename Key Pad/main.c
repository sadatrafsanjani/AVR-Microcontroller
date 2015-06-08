#define  F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>
#include "keypad.h"
#include "lcd.h"


int main(void){
	
	uint8_t key;
	
	//disable JTAG from PORTC
	MCUCSR |= 1<<JTD;
	MCUCSR |= 1<<JTD;
	
	//initialize LCD display
	lcd_init(LCD_DISP_ON);
	lcd_puts("key:");

	while(1){
		
		key = GetKeyPressed();	//Get the keycode of pressed key
		
		if(key != NO_KEY){
			
			//lcd_gotoxy(6, 0);		//goto lcd 0,0 location
			lcd_putc(key);			//Print it at location 0,0 on LCD.
			while(key == GetKeyPressed());
		}
	}
}