#include <math.h>

unsigned int count = 0;
char x = 0;

unsigned long T;
double frequency1, frequency2;

void setup() {
	Serial.begin(9600);

	TIMSK1 = 0x01;	// Enabled global and timer overflow interrupt
	TCCR1A = 0x00;	// Reset all bits to enable normal timer mode
	TCCR1B = 0x01;	// 3 first bits saves value of counter clock prescaler
	attachInterrupt(0, interrupt, RISING);
}

void loop() {
	/* Algorithm 1: digitalRead */
	while (digitalRead(2) == LOW) { }
	while (digitalRead(2) == HIGH) { }

	T = micros();
	while (digitalRead(2) == LOW) { }
	while (digitalRead(2) == HIGH) { }
	T = micros() - T;
	
	frequency1 = 1.0E6 / T;
	/* /Algorithm 1: digitalRead */

	/* Algorithm 2: interrupt */
	frequency2 = 16000000.0 / count;
	/* /Algorithm 2: interrupt */

	if (count) {
		Serial.print(frequency1);
		Serial.print("\t");
		Serial.println(frequency2);
	}

	delay(100);
}

void interrupt() {
	if (!x) {
		count = TCNT1;
		TCNT1 = 0x0000;		// 16bit counter register
		attachInterrupt(0, interrupt, FALLING);
	} else {
		attachInterrupt(0, interrupt, RISING);
	}
	x = ~x;
}
