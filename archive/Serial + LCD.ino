#include <LiquidCrystal.h>

char inChar;
String inString, setTemp;
int i;
float realTemp;

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

void setup() {
	Serial.begin(9600);
	pinMode(6, OUTPUT);
	analogWrite(6, 102);
	lcd.begin(16, 2);
	randomSeed(analogRead(0));
}

void loop() {
	lcd.clear();
	inChar = '\0';
	inString = "";

	if (i%5 == 0)
		realTemp = random(10, 90) / 2.0;
	i++;

	Serial.println(realTemp);

	while (Serial.available() > 0) {
		inChar = Serial.read();
		if (inChar == '\n') {
			break;
		}
		inString += inChar;
	}

	if (inString[0]) {
		setTemp = inString;
	}
	
	lcd.setCursor(0, 0);
	lcd.print("Set");
	lcd.setCursor(5, 0);
	lcd.print(setTemp);

	lcd.setCursor(0, 1);
	lcd.print("Real");
	lcd.setCursor(5, 1);
	lcd.print(realTemp);

	delay(1000);
}
