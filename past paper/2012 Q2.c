/********* ********* ********* ********* ********* ********* ********* ********* *********

Title:			2012 Q2
Board:			Arduino Uno R3
Author:			Ang Li
E-mail:			ang#ang.im	(substitute @ for #)
Blog:			http://angli.me/
Github:			https://github.com/leeang/Electronic-System-Implementation

********* ********* ********* ********* ********* ********* ********* ********* *********/

float gain = -310;
// gain of instrumentation amplifier

void setup() {
	pinMode(6, OUTPUT);
}

void loop() {
	int sensorValue = analogRead(A0);
	float voltage = sensorValue * 5.0 / 1023.0;
	float difference = (voltage - 2.5) / gain;
	
	difference = fabs(difference);
	// absolute value of a float

	int output = (difference / 7.8E-3) * 255;
	output = constrain(output, 0, 255);

	analogWrite(6, output);
	delay(100);
}
