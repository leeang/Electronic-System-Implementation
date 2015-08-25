/********* ********* ********* ********* ********* ********* ********* ********* *********

Title:			2013 Q3
Board:			Arduino Uno R3
Author:			Ang Li
E-mail:			ang#ang.im	(substitute @ for #)
Blog:			http://angli.me/
Github:			https://github.com/leeang/Electronic-System-Implementation

********* ********* ********* ********* ********* ********* ********* ********* *********/

/*
PWM: 3, 5, 6, 9, 10, and 11. Provide 8-bit PWM output with the analogWrite() function.
The Arduino board can be supplied with power either from the DC power jack (7 ~ 12V), the USB connector (5V), or the VIN pin of the board (7-12V). Supplying voltage via the 5V or 3.3V pins bypasses the regulator, and can damage your board. We don't advise it.
*/
unsigned long T;


void setup() {
	pinMode(6, OUTPUT);
}

void loop() {
	unsigned long TSum = 0;
	for (int i = 0; i < 100; ++i) {
		while (digitalRead(2) == LOW) { }
		while (digitalRead(2) == HIGH) { }
		
		T = micros();
		while (digitalRead(2) == LOW) { }
		while (digitalRead(2) == HIGH) { }
		T = micros() - T;
		TSum += T;
	}
	T = TSum / 100;

	double frequency = 1.0E6 / T;
	float temperature = 2.57636E-07 * pow(frequency, 3.0) - 8.12036E-04 * pow(frequency, 2.0) + 9.74482E-01 * frequency - 3.65980E+02;
	// equation we got when calibrating

	if (temperature < 35) {
		analogWrite(6, 255);
	}
	delay(100);
	// 0.1Hz sampling rate
}
