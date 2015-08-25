/********* ********* ********* ********* ********* ********* ********* ********* *********

Title:			2011 Q1
Board:			Arduino Uno R3
Author:			Ang Li
E-mail:			ang#ang.im	(substitute @ for #)
Blog:			http://angli.me/
Github:			https://github.com/leeang/Electronic-System-Implementation

********* ********* ********* ********* ********* ********* ********* ********* *********/

#define PUMP	6
#define LOWLED	7
#define MIDLED	8
#define HIGHLED	9

double voltageSum;
int sensorValue;
int i;
float voltage1, voltage2;

void setup() {
	pinMode(6, OUTPUT);
	pinMode(9, OUTPUT);
}

void loop() {
	voltageSum = 0;
	for (i = 0; i<100; i++) {
		sensorValue = analogRead(A0);
		voltage1 = sensorValue * 5.0 / 1023.0;
		voltageSum += voltage1;
	}
	voltage1 = voltageSum / 100;
	// Moving average algorithm, a low-pass filter.

	voltageSum = 0;
	for (i = 0; i<100; i++) {
		sensorValue = analogRead(A1);
		voltage2 = sensorValue * 5.0 / 1023.0;
		voltageSum += voltage2;
	}
	voltage2 = voltageSum / 100;
	// Moving average algorithm, a low-pass filter.

	if (voltage1 > 3.2 && voltage2 > 3.2) {	// D1 < 70k, high.
		digitalWrite(PUMP, LOW);
		digitalWrite(HIGHLED, HIGH);
		digitalWrite(MIDLED, LOW);
		digitalWrite(LOWLED, LOW);
	} else if (voltage2 < 2.3 && voltage1 < 2.3) {	// D2 > 150k, low.
		digitalWrite(PUMP, HIGH);
		digitalWrite(HIGHLED, LOW);
		digitalWrite(MIDLED, LOW);
		digitalWrite(LOWLED, HIGH);
	} else if (voltage1 < 2.3) {	// D1 > 150k, middle.
		digitalWrite(PUMP, HIGH);
		digitalWrite(HIGHLED, LOW);
		digitalWrite(MIDLED, HIGH);
		digitalWrite(LOWLED, LOW);
	}
}
