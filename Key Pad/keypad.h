/*
 * keypad.h
 *
 * Created: 04/01/2015 3:57:50 PM
 *  Author: Rana
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <avr/io.h>


/*keypad type config*/
#define KEYPAD_ROW	4
#define KEYPAD_COL	4


/*port and pin definitions*/
#define KEYPAD_DDR 	DDRA
#define KEYPAD_PORT PORTA
#define KEYPAD_PIN 	PINA


/*indicate no button press*/
#define NO_KEY	0xff


/*available functions*/
extern uint8_t GetKeyPressed();

#endif /* KEYPAD_H_ */