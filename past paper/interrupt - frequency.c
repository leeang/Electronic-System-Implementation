/********* ********* ********* ********* ********* ********* ********* ********* *********

Title:			2013 Q3
Board:			Arduino Uno R3
Author:			Ang Li
E-mail:			ang#ang.im	(substitute @ for #)
Blog:			http://angli.me/
ESI Project:	https://github.com/leeang/Electronic-System-Implementation
ESD Project:	https://github.com/leeang/Embedded-System-Design

********* ********* ********* ********* ********* ********* ********* ********* *********/

/*
	Please connect the oscillator output to digital pin 2
*/

unsigned int count = 0;
char flag = 0;
double frequency;

void setup() {
	Serial.begin(9600);

	TCCR1B = (1<<CS10);
/*
	Page 136 of ATmega 328P
	Timer/Counter1 Control Register B - TCCR1B

	Bit 2:0 - CS12:0: Clock Select
		001	clkI/O/1 (No prescaling)
*/

	TCNT1  = 0;
	// Set initial value of the counter = 0. Max: 65535.

	attachInterrupt(0, interrupt, RISING);
	// Rising edge of INT0 (digital pin 2) triggers interrupt.
}

void loop() {
	frequency = 16000000.0 / count;
	// Crystal frequency = 16MHz
	Serial.print(frequency, 2);
	delay(100);
}

void interrupt() {
	if (!flag) {
		count = TCNT1;
		// Read the counter value
		TCNT1 = 0;
		// Reset the counter value
		attachInterrupt(0, interrupt, FALLING);
		// Falling edge of INT0 (digital pin 2) triggers interrupt.
	} else {
		attachInterrupt(0, interrupt, RISING);
		// Rising edge of INT0 (digital pin 2) triggers interrupt.
	}
	flag = ~flag;
}
