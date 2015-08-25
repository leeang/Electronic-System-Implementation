/********* ********* ********* ********* ********* ********* ********* ********* *********

Title:			2010 Q3
Board:			Arduino Uno R3
Author:			Ang Li
E-mail:			ang#ang.im	(substitute @ for #)
Blog:			http://angli.me/
Github:			https://github.com/leeang/Electronic-System-Implementation

********* ********* ********* ********* ********* ********* ********* ********* *********/

int lampState = 0;
int counter = 0;
float voltage;

void setup() {
	pinMode(6, OUTPUT);
}

void loop() {
	if (lampState == 0) {
		double voltageSum = 0;
		for (int i = 0; i<100; i++) {
			int sensorValue = analogRead(A0);
			voltage = sensorValue * 5.0 / 1023.0;
			voltageSum += voltage;
		}
		voltage = voltageSum / 100;
		// Moving average algorithm, a low-pass filter.

		if (voltage >= 3) {
			digitalWrite(6, HIGH);
			lampState = 1;
		}
	} else {
		if (counter == 60) {
			digitalWrite(6, LOW);
			lampState = 0;
			counter = 0;
		}
		counter++;
		delay(1000);
	}
}
