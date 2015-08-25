/********* ********* ********* ********* ********* ********* ********* ********* *********

Title:			2013 Q2
Board:			Arduino Uno R3
Author:			Ang Li
E-mail:			ang#ang.im	(substitute @ for #)
Blog:			http://angli.me/
Github:			https://github.com/leeang/Electronic-System-Implementation

********* ********* ********* ********* ********* ********* ********* ********* *********/

/*
double	log (double __x)		// natural logarithm of x
double	log10 (double __x)		// logarithm of x to base 10.
*/

long t;
double C1 = 0.01E-6;
float temperature;
int Vthreshold = 3;
/* When a pin is configured as an INPUT with pinMode, and read with digitalRead, the microcontroller will report HIGH if a voltage of 3 volts or more is present at the pin. */

void setup() {
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	digitalWrite(2, LOW);
	digitalWrite(3, LOW);
}

void loop() {
	t = micros();
	// get the first timestamp
	digitalWrite(2, HIGH);
	// set D2 = 5V
	while (digitalRead(1)!=HIGH) {};
	// loop until D1 reaches 3V
	t = t - micros();
	// get the second timestamp, calculate the charging time, unit: microsecond

	digitalWrite(2, LOW);
	// set D2 = 0V, the capacitor wil discharge.

	double I = C1 * Vthreshold * 1000000 / t;
	// unit: Ampere

	temperature = 18.87 * log(I) + 640.19;
	// unit: Kelvin

	temperature = temperature - 273.15;
	// unit: Celsius

	temperature = constrain(temperature, 100, 200);
	// http://arduino.cc/en/reference/constrain

	int Vout = map(temperature, 100, 200, 0, 255);
	// map(value, fromLow, fromHigh, toLow, toHigh)
	// http://arduino.cc/en/reference/map

	analogWrite(3, Vout);

	delay(500);
	// ensure the capacitor can discharge completely
}
