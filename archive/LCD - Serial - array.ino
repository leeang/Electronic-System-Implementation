#include <LiquidCrystal.h>

char inString[20], setTemp[20];
int index, sizeStr;

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

void setup() {
	Serial.begin(9600);
	pinMode(6, OUTPUT);
	analogWrite(6, 102);
	lcd.begin(16, 2);
	randomSeed(analogRead(0));
	sizeStr = sizeof(inString);
}

void loop() {
	lcd.clear();
	index = 0;
	memset(inString, '\0', sizeStr);

	float realTemp = random(5, 45);
	Serial.println(realTemp);

	while (Serial.available() > 0 && index < sizeStr) {
		inString[index] = Serial.read();
		index++;
		inString[index] = '\0';
	}

	if (inString[0]) {
		strcpy(setTemp, inString);
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
