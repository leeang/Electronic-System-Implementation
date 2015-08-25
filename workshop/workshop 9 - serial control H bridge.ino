/*
+	pin3	Yellow	Orange
-	pin5	Green	Green
*/
char inChar;

void setup() {
	Serial.begin(9600);

	pinMode(3, OUTPUT);
	pinMode(5, OUTPUT);
}

void loop() {
	String inString = "";

	while (Serial.available() > 0) {
		inChar = Serial.read();
		if (inChar == '\n') {
			break;
		}
		inString += inChar;
	}

	if (inString != "") {
		int space = inString.indexOf(' ');

		int vol1 = inString.substring(0, space).toInt();
		int vol2 = inString.substring(space).toInt();

		analogWrite(3, vol1);
		analogWrite(5, vol2);

		Serial.print(vol1);
		Serial.print("\t");
		Serial.println(vol2);
	}

	delay(1000);
}
