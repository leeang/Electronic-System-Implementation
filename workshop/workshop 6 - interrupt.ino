int divider[6] = {0, 1, 8, 64, 256, 1024};
int prescaler = 5;
unsigned int count = 0;
char x = 0;

double period, frequency;

ISR(TIMER1_OVF_vect) {
	if (prescaler < 5) {
		prescaler++;
	}
}

void setup() {
	Serial.begin(9600);

	TIMSK1 = 0x01;
	TCCR1A = 0x00;
	attachInterrupt(0, interrupt, RISING);
}

void loop() {
	period = 0.0000625 * divider[prescaler] * count;
	frequency = 16000000.0 / divider[prescaler] / count;

	if (period) {
		Serial.print("Period: ");
		Serial.print(period);
		Serial.print(" ms\tFreq: ");
		Serial.print(frequency);
		Serial.print(" Hz\tPrescaler: ");
		Serial.println(prescaler);

		if (prescaler > 1) {
			prescaler--;
			delay(100);
		}
	}
	
	delay(100);
}

void interrupt() {
	if (!x) {
		count = TCNT1;
		TCNT1 = 0x0000;
		TCCR1B = prescaler;
		attachInterrupt(0, interrupt, FALLING);
	} else {
		attachInterrupt(0, interrupt, RISING);
	}
	x = ~x;
}
