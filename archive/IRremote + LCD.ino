#include <LiquidCrystal.h>
#include <IRremote.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

int RECV_PIN = 5;
IRrecv irrecv(RECV_PIN);
decode_results results;

float set = 25;

void setup() {
	Serial.begin(9600);
	irrecv.enableIRIn();

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
	if (irrecv.decode(&results)) {
		long value = results.value;
		switch (value) {
			case 0x40BFB04F:	//Up
				set += 0.5;
				break;
			case 0x40BF708F:	//Down
				set -= 0.5;
				break;
			case 0x40BF50AF:	//Left
				set -= 2;
				break;
			case 0x40BFA857:	//Right
				set += 2;
				break;
			case 0x40BF30CF:	//Central
				break;
		}
		irrecv.resume();
		if (set>45)
			set = 45;
		else if (set < 5)
			set = 5;
	}

	lcd.setCursor(5, 0);
	lcd.print(set);

	delay(100);
}
