#include <math.h>

float R = 9960.0;
float R25 = 10000.0;

double constA = 3.3540154e-03;
double constB = 2.5627725e-04;
double constC = 2.0829210e-06;
double constD = 7.3003206e-08;

void setup() {
	Serial.begin(9600);
}

void loop() {
	int sensorValue = analogRead(A0);
	double Rt = sensorValue * (R / (1023.0 - sensorValue));
	double ratio = Rt / R25;
	float temperature = 1.0 / (constA + constB * log(ratio)  + constC * log(ratio * ratio) + constD * log(ratio * ratio * ratio)) - 273.15;
	Serial.println(temperature);
}
