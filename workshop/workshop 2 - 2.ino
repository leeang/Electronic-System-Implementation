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
	/* mode 1 */
	int sensorValue0 = analogRead(A0);
	double Rt0 = sensorValue0 * (R / (1023.0 - sensorValue0));
	double ratio0 = Rt0 / R25;
	float temperature0 = 1.0 / (constA + constB * log(ratio0)  + constC * log(ratio0 * ratio0) + constD * log(ratio0 * ratio0 * ratio0)) - 273.15;
	Serial.print("T0: ");
	Serial.println(temperature0);
	/* /mode 1 */

	/* mode 2 */
	int sensorValue1 = analogRead(A1);
	double Rt1 = sensorValue1 * (R / (1023.0 - sensorValue1));
	double ratio1 = Rt1 / R25;
	float temperature1 = 1.0 / (constA + constB * log(ratio1)  + constC * log(ratio1 * ratio1) + constD * log(ratio1 * ratio1 * ratio1)) - 273.15;
	Serial.print("T1: ");
	Serial.println(temperature1);
	/* /mode 2 */
}
