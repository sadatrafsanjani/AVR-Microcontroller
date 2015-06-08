/*******************************************
 * keypad.c
 *
 * Created: 04/01/2015 3:58:01 PM
 *  Author: Rana
 *
 
Function return the keycode of keypressed
on the Keypad. Keys are numbered as follows

[00] [01] [02]
[03] [04] [05]
[06] [07] [08]
[09] [10] [11]

Arguments:
	None

Return:
	Any number between 0-11 depending on
	keypressed.

	255 (hex 0xFF) if NO keypressed.

Precondition:
	None. Can be called without any setup.

*******************************************/

#include "keypad.h"


uint8_t GetKeyPressed()
{
	uint8_t r,c;
	uint8_t ret;

	KEYPAD_PORT|= 0x0F;

	for(c=0;c<3;c++)
	{
		KEYPAD_DDR&=~(0x7F);
		KEYPAD_DDR|=(0x40>>c);
		for(r=0;r<4;r++)
		{
			if(!(KEYPAD_PIN & (0X08>>r)))
			{
				ret = (r*3+c)+49;
				if(ret == 58) ret = '*';
				else if(ret == 59) ret = '0'; 
				else if(ret == 60) ret = '#';
				return(ret);
			}
		}
	}

	return NO_KEY; //no button press
}

