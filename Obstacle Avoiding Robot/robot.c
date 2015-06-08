#define F_CPU 1000000

#define USS_DDR			DDRA
#define USS_PIN			PINA
#define USS_PORT		PORTA
#define TRIG_PIN		PA0
#define ECHO_PIN		PA1

#define MOTOR_DDR		DDRD
#define MOTOR_PORT		PORTD
#define LeftMotorPinA	PD3
#define LeftMotorPinB	PD4
#define RightMotorPinA  PD5
#define RightMotorPinB  PD6


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

void robotForward(){
	
	//left motor
	MOTOR_PORT |= (1<<LeftMotorPinA);		// High
	MOTOR_PORT &= ~(1<<LeftMotorPinB);		// Low
	
	//right motor
	MOTOR_PORT |= (1<<RightMotorPinA);		// High
	MOTOR_PORT &= ~(1<<RightMotorPinB);		// Low
}

void robotBackward(){
	
	//left motor
	MOTOR_PORT &= ~(1<<LeftMotorPinA);		// Low
	MOTOR_PORT |= (1<<LeftMotorPinB);		// High
	
	//right motor
	MOTOR_PORT &= ~(1<<RightMotorPinA);		// Low
	MOTOR_PORT |= (1<<RightMotorPinB);		// High
}

void robotLeft(){
	
	//left motor
	MOTOR_PORT &= ~(1<<LeftMotorPinA);		// Low
	MOTOR_PORT |= (1<<LeftMotorPinB);		// High
	
	//right motor
	MOTOR_PORT |= (1<<RightMotorPinA);		// High
	MOTOR_PORT &= ~(1<<RightMotorPinB);		// Low
}

void robotRight(){
	
	//left motor
	MOTOR_PORT &= ~(1<<LeftMotorPinA);		// High
	MOTOR_PORT |= (1<<LeftMotorPinB);		// Low
	
	//right motor
	MOTOR_PORT &= ~(1<<RightMotorPinA);		// Low
	MOTOR_PORT |= (1<<RightMotorPinB);		// High
}

void robotStop(){
	
	//left motor
	MOTOR_PORT &= ~(1<<LeftMotorPinA);		// Low
	MOTOR_PORT &= ~(1<<LeftMotorPinB);		// Low
	
	//right motor
	MOTOR_PORT &= ~(1<<RightMotorPinA);		// Low
	MOTOR_PORT &= ~(1<<RightMotorPinB);		// Low
}

long calcDistance(uint8_t pingPin, uint8_t echoPin){
	
	long time;
	uint32_t i;
	
	//give a 15us High pulse on trig pin
	USS_DDR |= (1<<pingPin);
	USS_PORT |= (1<<pingPin);
	_delay_us(15);
	USS_PORT &= ~(1<<pingPin);
	_delay_us(20);
	
	//Wait for the rising edge
	USS_DDR &= ~(1<<echoPin);
	for(i=0;i<600000;i++){
		
		if(!(USS_PIN & (1<<echoPin))){
		 
			continue;
		}
		else{ 
			
			break;
		}
	}
	
	//out of range or device error
	if(i==600000){
		
		return -1;
	}
	
	//High Edge Found
	TCCR1A = 0x00;					// setup Timer1
	TCNT1 = 0x00;					// reset Timer1
	TCCR1B |= (1<<CS10);			// timer run in 1MHz, i.e F_CPU 1MHz/1
	
	//Now wait for the falling edge
	for(i=0;i<600000;i++){
		
		if(USS_PIN & (1<<echoPin)){
			
			if(TCNT1 > 60000){ 
				
				break; 
			}
			else{ 
				
				continue; 
			}
		}
		else{ 
			
			break; 
		}
	}
	
	//out of range or device error
	if(i==600000){ 
		
		return -2;
	}
	
	//Falling edge found
	time  = TCNT1;					//timer value
	TCCR1B = 0x00;					//Stop Timer
	
	//return time;					//for debugging
	
	if(time > 30700){ 
		
		return -3;
	}		//No obstacle
	else{ 
		
		return(time/58.0);
	}			//convert to cm
}

int main(void){
	
	USS_DDR |= (1<<TRIG_PIN);	// USS trig pin output
	USS_DDR &= ~(1<<ECHO_PIN);	//USS Echo pin input
	
	MOTOR_DDR |= (1<<LeftMotorPinA)|(1<<LeftMotorPinB); //left motor pins as output
	MOTOR_DDR |= (1<<RightMotorPinA)|(1<<RightMotorPinB); //right motor pins as output
	
	robotForward();
	_delay_ms(500);
	
	while (1){
		
		long obstacle = calcDistance(TRIG_PIN, ECHO_PIN);
		
		if(obstacle < 20){
			
			robotBackward();
			_delay_ms(500);
			robotLeft();
			_delay_ms(150);
		}
		else{
			
			robotForward();
		}
		
		_delay_ms(100);
	}
}
