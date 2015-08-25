/*
analogRead()
Reads the value from the specified analog pin. The Arduino board contains a 6 channel, 10-bit analog to digital converter. This means that it will map input voltages between 0 and 5 volts into integer values between 0 and 1023. This yields a resolution between readings of: 5 volts / 1024 units or, .0049 volts (4.9 mV) per unit. The input range and resolution can be changed using analogReference().
It takes about 100 microseconds (0.0001 s) to read an analog input, so the maximum reading rate is about 10,000 times a second.
*/

#include <math.h>

float gain = -2.25;	// gain of instrumentation amplifier
float R = 10000.0;	// resistor in Wheatstone Bridge

float Rt, temperature, Vab, tmp;
int sensorValue;

double constA = 3.3540154e-03;
double constB = 2.5627725e-04;
double constC = 2.0829210e-06;
double constD = 7.3003206e-08;

void setup() {
	Serial.begin(9600);
}

void loop() {
	sensorValue = analogRead(A1);
	Vab = (sensorValue * 5.0 / 1023.0 - 2.5) / gain;

	/* Wheatstone Bridge */
	tmp = Vab / 5.0 + 0.5;
	Rt = R * tmp / (1 - tmp);
	/* /Wheatstone Bridge */

	temperature = Rt2Temperature(Rt);

	Serial.println(temperature);

	delay(100);
}

float Rt2Temperature(float Rt) {
	float R25 = 10000.0;
	double ratio = Rt / R25;
	float temperature = 1.0 / (constA + constB * log(ratio)  + constC * log(ratio * ratio) + constD * log(ratio * ratio * ratio)) - 273.15;
	return temperature;
}
