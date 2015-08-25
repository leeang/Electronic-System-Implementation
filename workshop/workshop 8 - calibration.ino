double Varef = 5.035;
double R = 12.9E3;

unsigned long count = 0;
char x = 0;
double voltage;

void setup() {
	Serial.begin(9600);
	analogReference(EXTERNAL);

	TIMSK1 = 0x01;
	TCCR1A = 0x00;
	TCCR1B = 0x01;
	attachInterrupt(0, interrupt, RISING);

	delay(1000);
}

void loop() {
	double voltageSum = 0.0;
	for (int i=0; i<100; i++) {
		int sensorValue = analogRead(A0);
		voltage = sensorValue * (Varef / 1023.0);
		voltageSum += voltage;
	}
	voltage = voltageSum / 100;
	double temperature = voltage * 1E6 / R - 273.15;

	float frequency = 16000000.0 / count;
	
	Serial.print(voltage, 6);
	Serial.print("\t");
	Serial.print(temperature, 6);
	Serial.print("\t");
	Serial.println(frequency);

	delay(500);
}

void interrupt() {
	if (!x) {
		count = TCNT1;
		TCNT1 = 0x0000;
		attachInterrupt(0, interrupt, FALLING);
	} else {
		attachInterrupt(0, interrupt, RISING);
	}
	x = ~x;
}
