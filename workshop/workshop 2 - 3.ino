#include <math.h>

float R1 = 9960.0;
float R2 = 9940.0;
float R25 = 10000.0;
float temperature;

double constA = 3.3540154e-03;
double constB = 2.5627725e-04;
double constC = 2.0829210e-06;
double constD = 7.3003206e-08;

void setup() {
	Serial.begin(9600);
}

void loop() {
	temperature = getTemperature(A0, R1, 1);
	Serial.print("T0: ");
	Serial.print(temperature);
	Serial.print(" ");

	temperature = getTemperature(A1, R2, 2);
	Serial.print("T1: ");
	Serial.print(temperature);
	Serial.println("");

	delay(100);
}

float getTemperature(int pinNo, float R, int mode) {
	float Rt;

	int sensorValue = analogRead(pinNo);

	if (mode == 1) {
		Rt = sensorValue * R / (1023.0 - sensorValue);
	}
	if (mode == 2) {
		Rt = (1023.0 - sensorValue) * R / sensorValue;
	}

	double ratio = Rt / R25;
	float temperature = 1.0 / (constA + constB * log(ratio)  + constC * log(ratio * ratio) + constD * log(ratio * ratio * ratio)) - 273.15;
	return temperature;
}
