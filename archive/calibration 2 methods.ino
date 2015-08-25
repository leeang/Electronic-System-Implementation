double Varef = 5.025;
double R = 12.85E3;

unsigned long T;
unsigned long count = 0;
char x = 0;
float frequency1, frequency2;
double voltage, temperature;

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
	temperature = voltage * 1E6 / R - 273.15;

	while (digitalRead(2) == LOW) { }
	while (digitalRead(2) == HIGH) { }
	T = micros();
	while (digitalRead(2) == LOW) { }
	while (digitalRead(2) == HIGH) { }
	T = micros() - T;
	frequency1 = 1.0E6 / T;

	frequency2 = 16000000.0 / count;
	
	Serial.print(voltage, 6);
	Serial.print("\t");
	Serial.print(temperature, 6);
	Serial.print("\t");
	Serial.print(frequency1);
	Serial.print("\t");
	Serial.println(frequency2);

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
