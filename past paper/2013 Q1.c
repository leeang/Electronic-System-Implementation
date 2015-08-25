/********* ********* ********* ********* ********* ********* ********* ********* *********

Title:			2013 Q1
Board:			Arduino Uno R3
Author:			Ang Li
E-mail:			ang#ang.im	(substitute @ for #)
Blog:			http://angli.me/
Github:			https://github.com/leeang/Electronic-System-Implementation

********* ********* ********* ********* ********* ********* ********* ********* *********/

/*
	analogRead()
	It takes about 100 microseconds (0.0001 s) to read an analog input, so the maximum reading rate is about 10,000 times a second.
	http://arduino.cc/en/Reference/analogRead
*/

float current, voltage;
int voltageRatio = 16;
int currentRatio = 2;
int LED_Amount = 0;

double unitPower = 3.125;

void setup() {
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(10, OUTPUT);
}

void loop() {
	double voltageSum = 0;
	double currentSum = 0;
	for (int i=0; i<500; i++) {
		int sensorValue0 = analogRead(A0);
		int sensorValue1 = analogRead(A1);

		voltage = sensorValue0 * 5.0 / 1023.0;
		current = sensorValue1 * 5.0 / 1023.0;

		voltage = (voltage - 2.5) * voltageRatio;
		current = (voltage - 2.5) * currentRatio;
		
		voltageSum += (voltage * voltage);
		// root-mean-square voltage
		currentSum += (current * current);
		// root-mean-square current
	}

	voltage = sqrt(voltageSum / 500);
	// root-mean-square voltage
	current = sqrt(currentSum / 500);
	// root-mean-square current

	float power = voltage * current;

	LED_Amount = log2(power / unitPower);
/*
	=100W		6 diodes
	>=50W		5 diodes
	>=25W		4 diodes
	>=12.5W		3 diodes
	>=6.25W		2 diodes
	>=3.125W	1 diodes
	<3.125W		0 diode
*/

	for (int i=1; i<=6; i++) {
		int pin = i + 4;
		// pin5 ~ pin10
		LED_Amount >= i ? digitalWrite(pin, HIGH) : digitalWrite(pin, LOW);
	}
}

int log2(float num) {
	int result = log(num) / log(2);
	return result;
}
