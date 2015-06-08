#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "uart.h"

char buffer[7];

int main(void){
	
	uart_init(UART_BAUD_SELECT(4800,F_CPU));
	sei();
	
	uart_putc('R');
	uart_puts("STOM");
	
	int value = 12345;
	itoa(value, buffer, 10);
	uart_puts(buffer);
	
    while(1){
		
        char ch = uart_getc();
        
        if ( ch != UART_NO_DATA ){
	        
	        uart_putc(ch);
        }
    }
}