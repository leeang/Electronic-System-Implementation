float Varef = 5.035;

void setup() {
	Serial.begin(9600);
	analogReference(EXTERNAL);
}

void loop() {
	float voltageSum = 0.0;

	for (int i=0; i<100; i++) {
		int sensorValue = analogRead(A0);
		float voltage = sensorValue * (Varef / 1023.0);
		voltageSum += voltage;
	}
	
	Serial.println(voltageSum / 100);
	delay(500);
}
