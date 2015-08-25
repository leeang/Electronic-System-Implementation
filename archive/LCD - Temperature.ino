#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
//lcd(RS, Enable, D4, D5, D6, D7)

void setup() {
	pinMode(6, OUTPUT);
	analogWrite(6, 102);
	//display constrast pin (Vo)

	lcd.begin(16, 2);
	lcd.setCursor(0, 0);
	lcd.print("Set");
	lcd.setCursor(0, 1);
	lcd.print("Real");
}

void loop() {
	lcd.setCursor(5, 0);
	lcd.print(millis()/1000);
	
	lcd.setCursor(5, 1);
	lcd.print(millis()/1000);
}
