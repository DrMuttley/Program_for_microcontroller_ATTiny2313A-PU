#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

/*obsługa rejestrów*/
#define SER PB0
#define G PB1  //rck
#define RCK PB2//SCK
#define SCK PB3 //SCLR
#define SCLR PB4

/*obsługa multiplekser*/
#define S0 PD1  //PD0
#define S1 PD2  //PD1
#define S2 PD4  //PD2
#define S3 PD3  //PD3
#define BUTTON (1<<PD0)  //PD4

void setS0S3_AsOut();
void setButtonAsIn();

void startApp();
void buttonZero();
void buttonOne();
void buttonTwo();
void buttonThree();
void buttonFour();
void buttonFive();
void buttonSix();
void buttonSeven();
void buttonEight();
void buttonNine();
void buttonCalculate();
void buttonResutl();
void alert();
void cleanDiodeStatus(unsigned char mode);
void cleanAll();
void divideAndDisplay(short int value);
void show(unsigned char value);


void setS0S3_0();
void setS0S3_1();
void setS0S3_2();
void setS0S3_3();
void setS0S3_4();
void setS0S3_5();
void setS0S3_6();
void setS0S3_7();
void setS0S3_8();
void setS0S3_9();
void setS0S3_10();
void setS0S3_11();
void setS0S3_12();
void setS0S3_13();

char diodeStatus[5] = "    \0";
char firstNumber[5] = "    \0";
unsigned char sign = 0; // 0 - add, 1 - subtract
unsigned char firstNumberSign = 0;
unsigned char buttonNumberUsed = 0; // 0-no 1-yes

short int result = 0;
short int resultInMemory = 0;
short int fisrtNumberInDecimal = 0;
short int secondNumberInDecimal = 0;
short int multiplier = 100;
short int temp = 0;

unsigned char mathCounter = 0;
unsigned char buttonCounter = 1;

int main(void)
{
	startApp();

	setS0S3_AsOut();
	setButtonAsIn();

	while (1)
	{
		if(buttonCounter<4){
		
			setS0S3_3();

				if(!(PIND & BUTTON)){
					diodeStatus[buttonCounter] = '0';
				}
		
			setS0S3_2();

				if(!(PIND & BUTTON)){
					diodeStatus[buttonCounter] = '1';
				}
				
			setS0S3_1();

				if(!(PIND & BUTTON)){
					diodeStatus[buttonCounter] = '2';
				}
				
 			setS0S3_8();
 
 				if(!(PIND & BUTTON)){
 					diodeStatus[buttonCounter] = '3';
 				}
 
 			setS0S3_9();
 
 				if(!(PIND & BUTTON)){
 					diodeStatus[buttonCounter] = '4';
 				}
 
 			setS0S3_10();
 
 				if(!(PIND & BUTTON)){
 					diodeStatus[buttonCounter] = '5';
 				}

			setS0S3_11();

				if(!(PIND & BUTTON)){
					diodeStatus[buttonCounter] = '6';
				}

			setS0S3_12();

				if(!(PIND & BUTTON)){
					diodeStatus[buttonCounter] = '7';
				}

			setS0S3_13();

				if(!(PIND & BUTTON)){
					diodeStatus[buttonCounter] = '8';
				}

			setS0S3_0();

				if(!(PIND & BUTTON)){
					diodeStatus[buttonCounter] = '9';
				}

			if(diodeStatus[buttonCounter] != ' '){
				buttonCounter++;
				buttonNumberUsed = 1;

				if(firstNumberSign == 1){
					buttonEight();
				}else{
					buttonZero();
				}

				temp = atoi(diodeStatus);

				divideAndDisplay(temp);
			}
		}
		
		setS0S3_7();

			if(!(PIND & BUTTON)){
				buttonResutl();
				firstNumberSign = 0;
				buttonCalculate();
				sign = 0;	
			}

		setS0S3_6();

			if(!(PIND & BUTTON)){

				if (buttonNumberUsed == 0)
				{
					firstNumberSign = 1;
				}else{
					buttonResutl();
					firstNumberSign = 0;
				}
				buttonCalculate();
				sign = 1;
			}

		setS0S3_5();

			if(!(PIND & BUTTON)){
				buttonResutl();
			}

		setS0S3_4();

			if(!(PIND & BUTTON)){
				cleanDiodeStatus(0);
				resultInMemory = 0;
				cleanAll();
			}
	}
}

void setS0S3_AsOut(){
	DDRD |= (1<<S0) | (1<<S1) | (1<<S2) | (1<<S3);
}

void setButtonAsIn(){
	DDRD &= ~BUTTON;
	PORTD |= BUTTON;
}

void startApp(){

	DDRB |= (1<<SER) | (1<<RCK) | (1<<SCK) | (1<<SCLR) | (1<<G);

	PORTB |= (1<<G);

	PORTB |= (1<<SCLR);

	PORTB &= ~(1<<SER);

	for(unsigned char i=0; i<=15; i++){

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);
	}

	PORTB &= ~(1<<G);
	
	PORTB |= (1<<RCK);
	PORTB ^= (1<<RCK);
	
	//_delay_ms(1000);
	/*
	PORTB |= (1<<SER);

	for(unsigned char i=0; i<=15; i++){

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

		PORTB |= (1<<RCK);
		PORTB ^= (1<<RCK);

		_delay_ms(100);
	}
	cleanDiodeStatus(0);	*/	
}

void buttonZero(){

	PORTB &= ~(1<<SER);

	for(unsigned char i=0; i<4; i++){
		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);
	}
	
	PORTB |= (1<<RCK);
	PORTB ^= (1<<RCK);
}

void buttonOne(){

	PORTB &= ~(1<<SER);

	for(unsigned char i=0; i<3; i++){
		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);
	}

	PORTB |= (1<<SER);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

	PORTB |= (1<<RCK);
	PORTB ^= (1<<RCK);
}

void buttonTwo(){

	PORTB &= ~(1<<SER);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

	PORTB |= (1<<SER);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

	PORTB &= ~(1<<SER);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

	PORTB |= (1<<RCK);
	PORTB ^= (1<<RCK);
}

void buttonThree(){

	PORTB &= ~(1<<SER);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

 		PORTB |= (1<<SCK);
 		PORTB ^= (1<<SCK);

	PORTB |= (1<<SER);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

	PORTB |= (1<<RCK);
	PORTB ^= (1<<RCK);
}

void buttonFour(){

	PORTB &= ~(1<<SER);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

	PORTB |= (1<<SER);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

	PORTB &= ~(1<<SER);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

	PORTB |= (1<<RCK);
	PORTB ^= (1<<RCK);
}

void buttonFive(){

	PORTB &= ~(1<<SER);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

	PORTB |= (1<<SER);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

	PORTB &= ~(1<<SER);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

	PORTB |= (1<<SER);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

	PORTB |= (1<<RCK);
	PORTB ^= (1<<RCK);
}

void buttonSix(){
	
	PORTB &= ~(1<<SER);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

	PORTB |= (1<<SER);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

	PORTB &= ~(1<<SER);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

	PORTB |= (1<<RCK);
	PORTB ^= (1<<RCK);
}

void buttonSeven(){

	PORTB &= ~(1<<SER);
	
		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

	PORTB |= (1<<SER);

	for(unsigned char i=0; i<3; i++){
		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);
	}
	
	PORTB |= (1<<RCK);
	PORTB ^= (1<<RCK);
}

void buttonEight(){

	PORTB |= (1<<SER);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

	PORTB &= ~(1<<SER);
	
	for(unsigned char i=0; i<3; i++){
		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);
	}

	PORTB |= (1<<RCK);
	PORTB ^= (1<<RCK);
}

void buttonNine(){

	PORTB |= (1<<SER);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

	PORTB &= ~(1<<SER);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

	PORTB |= (1<<SER);

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);

	PORTB |= (1<<RCK);
	PORTB ^= (1<<RCK);
}

void buttonCalculate(){

	buttonCounter = 1;

	for(unsigned char i=1; i<4; i++){
		firstNumber[i] = ' ';
	}

	if(mathCounter == 0){
		for(unsigned char i=1; i<4; i++){
			firstNumber[i] = diodeStatus[i];
		}
	}
	mathCounter = 1;

	cleanDiodeStatus(0);

	_delay_ms(300);
}

void buttonResutl(){

	fisrtNumberInDecimal = atoi(firstNumber);
	if(firstNumberSign == 1){
		fisrtNumberInDecimal = fisrtNumberInDecimal * (-1);
	}
	secondNumberInDecimal = atoi(diodeStatus);

	if(sign == 0){
		result = fisrtNumberInDecimal + secondNumberInDecimal;
	}else{
		result = fisrtNumberInDecimal - secondNumberInDecimal;
	}
	result += resultInMemory;

	resultInMemory = result;

	cleanDiodeStatus(1);

	if(result < 0){
		result = result * (-1);
		buttonEight();
	}else{
		buttonZero();
	}

	if(result <= 999){
		divideAndDisplay(result);
	}else{
		alert();
	}

	for(unsigned char i=0; i<4; i++)
	{
		diodeStatus[i] = ' ';
		firstNumber[i] = ' ';
	}
	cleanAll();
}

void alert(){

	PORTB |= (1<<SER);

	for(unsigned char i=0; i<5; i++){
		
		PORTB ^= (1<<SER);

		for(unsigned char i=0; i<=15; i++){

			PORTB |= (1<<SCK);
			PORTB ^= (1<<SCK);
		}
		
		PORTB |= (1<<RCK);
		PORTB ^= (1<<RCK);

		_delay_ms(300);
	}
	resultInMemory = 0;
	cleanAll();
}

void cleanDiodeStatus(unsigned char mode){

	buttonCounter = 1;

	PORTB &= ~(1<<SER);

	for(unsigned char i=0; i<=15; i++){

		PORTB |= (1<<SCK);
		PORTB ^= (1<<SCK);
	}

	PORTB |= (1<<RCK);
	PORTB ^= (1<<RCK);
	
	if(mode == 0){
		for(unsigned char i=0; i<4; i++){
			diodeStatus[i]=' ';
		}
	}
}

void cleanAll(){

	result = 0;
	mathCounter = 0;
	fisrtNumberInDecimal = 0;
	secondNumberInDecimal = 0;
	firstNumberSign = 0;
	buttonNumberUsed = 0;
	sign = 0;
}

void divideAndDisplay(short int value){

	multiplier = 100;
			
	for(unsigned char i=1; i<4; i++){

		show(value/multiplier);
		value %= multiplier;
		multiplier /= 10;
	}
	_delay_ms(300);
}

void show(unsigned char value){

	if(value == 0){
		buttonZero();
	}else if (value == 1){
		buttonOne();
	}else if(value == 2){
		buttonTwo();
	}else if(value == 3){
		buttonThree();
	}else if(value == 4){
		buttonFour();
	}else if(value == 5){
		buttonFive();
	}else if(value == 6){
		buttonSix();
	}else if(value == 7){
		buttonSeven();
	}else if(value == 8){
		buttonEight();
	}else if(value == 9){
		buttonNine();
	}
}

void setS0S3_0(){
	PORTD &= ~(1<<S0);
	PORTD &= ~(1<<S1);
	PORTD &= ~(1<<S2);
	PORTD &= ~(1<<S3);
}

void setS0S3_1(){
	PORTD |= (1<<S0);
	PORTD &= ~(1<<S1);
	PORTD &= ~(1<<S2);
	PORTD &= ~(1<<S3);
}

void setS0S3_2(){
	PORTD &= ~(1<<S0);
	PORTD |= (1<<S1);
	PORTD &= ~(1<<S2);
	PORTD &= ~(1<<S3);
}

void setS0S3_3(){
	PORTD |= (1<<S0);
	PORTD |= (1<<S1);
	PORTD &= ~(1<<S2);
	PORTD &= ~(1<<S3);
}

void setS0S3_4(){
	PORTD &= ~(1<<S0);
	PORTD &= ~(1<<S1);
	PORTD |= (1<<S2);
	PORTD &= ~(1<<S3);
}

void setS0S3_5(){
	PORTD |= (1<<S0);
	PORTD &= ~(1<<S1);
	PORTD |= (1<<S2);
	PORTD &= ~(1<<S3);
}

void setS0S3_6(){
	PORTD &= ~(1<<S0);
	PORTD |= (1<<S1);
	PORTD |= (1<<S2);
	PORTD &= ~(1<<S3);
}

void setS0S3_7(){
	PORTD |= (1<<S0);
	PORTD |= (1<<S1);
	PORTD |= (1<<S2);
	PORTD &= ~(1<<S3);
}

void setS0S3_8(){
	PORTD &= ~(1<<S0);
	PORTD &= ~(1<<S1);
	PORTD &= ~(1<<S2);
	PORTD |= (1<<S3);
}

void setS0S3_9(){
	PORTD |= (1<<S0);
	PORTD &= ~(1<<S1);
	PORTD &= ~(1<<S2);
	PORTD |= (1<<S3);
}

void setS0S3_10(){
	PORTD &= ~(1<<S0);
	PORTD |= (1<<S1);
	PORTD &= ~(1<<S2);
	PORTD |= (1<<S3);
}

void setS0S3_11(){
	PORTD |= (1<<S0);
	PORTD |= (1<<S1);
	PORTD &= ~(1<<S2);
	PORTD |= (1<<S3);
}

void setS0S3_12(){
	PORTD &= ~(1<<S0);
	PORTD &= ~(1<<S1);
	PORTD |= (1<<S2);
	PORTD |= (1<<S3);
}

void setS0S3_13(){
	PORTD |= (1<<S0);
	PORTD &= ~(1<<S1);
	PORTD |= (1<<S2);
	PORTD |= (1<<S3);
}
