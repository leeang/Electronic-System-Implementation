/********* ********* ********* ********* ********* ********* ********* ********* *********

Title:			2013 Q1 - Timer
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

	moving average - smoothing algorithm
	http://arduino.cc/en/Tutorial/Smoothing
*/

#define VoltageRatio	16
#define CurrentRatio	2
#define	LoopAmount		500

float voltageBuffer[LoopAmount];
float currentBuffer[LoopAmount];

double voltageSum;
double currentSum;
int index = 0;

void setup() {
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(10, OUTPUT);

	while (index < LoopAmount) {
		voltageBuffer[index] = 0;
		currentBuffer[index] = 0;
		index++;
	}
	index = 0;

	/* set Timer1 interrupt at 10Hz */
	TCCR1A = 0;
	// reset TCCR1A
	TCCR1B = 0;
	// reset TCCR1B
	TCNT1  = 0;
	// counter initial value = 0
	TCCR1B |= (1 << WGM12);
	// turn on CTC mode
	TCCR1B |= (1 << CS12) | (1 << CS10);
	// set CS12 and CS10 bits for 1024 prescaler
	TIMSK1 |= (1 << OCIE1A);
	// enable timer compare interrupt
	OCR1A = 1561;
	// 16MHz / (10 * 1024) - 1
	// set compare match register for 0.1Hz

	sei();	// enable all interrupts
}

void loop() {
	voltageSum -= voltageBuffer[index];
	currentSum -= currentBuffer[index];
	// substract values that we got in last round

	int sensorValue0 = analogRead(A0);
	int sensorValue1 = analogRead(A1);

	float voltage = sensorValue0 * 5.0 / 1023.0;
	float current = sensorValue1 * 5.0 / 1023.0;

	voltage = (voltage - 2.5) * VoltageRatio;
	current = (voltage - 2.5) * CurrentRatio;
	
	voltageBuffer[index] = voltage * voltage;
	currentBuffer[index] = current * current;

	voltageSum += voltageBuffer[index];
	currentSum += currentBuffer[index];
	// add values that we got in this round

	index++;
	(index >= LoopAmount) && (index = 0);
}

int log2(float num) {
	int result = log(num) / log(2);
	return result;
}

ISR(TIMER1_COMPA_vect) {
	float voltage = sqrt(voltageSum / LoopAmount);
	float current = sqrt(currentSum / LoopAmount);
	float power = voltage * current;
	int LED_Amount = log2(power / 3.125);
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
