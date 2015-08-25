/********* ********* ********* ********* ********* ********* ********* ********* *********

Title:			2014 Q2
Board:			Arduino Uno R3
Author:			Ang Li
E-mail:			ang#ang.im	(substitute @ for #)
Blog:			http://angli.me/
Github:			https://github.com/leeang/Electronic-System-Implementation

********* ********* ********* ********* ********* ********* ********* ********* *********/

/*
	millis() Returns the number of milliseconds since the Arduino board began running the current program. This number will overflow (go back to zero), after approximately 50 days.
	http://arduino.cc/en/reference/millis

	attachInterrupt() Specifies a named Interrupt Service Routine (ISR) to call when an interrupt occurs. Replaces any previous function that was attached to the interrupt. Most Arduino boards have two external interrupts: numbers 0 (on digital pin 2) and 1 (on digital pin 3).
	http://arduino.cc/en/Reference/attachInterrupt
*/

long timestamp1, timestamp2;

void setup() {
	pinMode(6, OUTPUT);
	attachInterrupt(0, ISR0, RISING);
	attachInterrupt(1, ISR1, RISING);
	// connect digital inputs to D2 and D3
}

void loop() {
	if ( (millis() - timestamp2) > 10000 ) {
		digitalWrite(6, LOW);
	}
	// turn off the alarm after approximately 10 seconds, counting from it was truned on.
	delay(100);
}

/****** Interrupt Service Routine ******/
void ISR0() {
	timestamp1 = millis();
	digitalWrite(6, LOW);
	// turn off the alarm when the next car comes.
}
void ISR1() {
	timestamp2 = millis();
	if ( (timestamp2 - timestamp1) < 4800 ) {
		digitalWrite(6, HIGH);
	}
	// if time is shorter than 4.8 seconds, turn on the alarm.
}
/****** /Interrupt Service Routine ******/
