#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
//lcd(RS, Enable, D4, D5, D6, D7)

void setup() {
	pinMode(6, OUTPUT);
	analogWrite(6, 102);
	//display constrast pin (Vo)

	lcd.begin(16, 2);
}

void loop() {
	lcd.setCursor(0, 0);
	lcd.print(millis()/1000);
}
