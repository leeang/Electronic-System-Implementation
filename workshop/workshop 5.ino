/*
http://www.circuitstoday.com/transistor-phase-shift-oscillator

micros()
Returns the number of microseconds since the Arduino board began running the current program. This number will overflow (go back to zero), after approximately 70 minutes. On 16 MHz Arduino boards, this function has a resolution of four microseconds (i.e. the value returned is always a multiple of four). On 8 MHz Arduino boards, this function has a resolution of eight microseconds.
*/

#include <math.h>
/* LCD */
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
/* /LCD */

unsigned long T;
double frequency;

void setup() {
	Serial.begin(9600);	// Serial
	/* LCD */
	pinMode(6, OUTPUT);
	analogWrite(6, 102);
	lcd.begin(16, 2);
	/* /LCD */
}

void loop() {
	lcd.clear();

	while (digitalRead(2) == LOW) { }
	while (digitalRead(2) == HIGH) { }	// in order to ensure an entire cycle

	T = micros();	// time stamp (microsecond μs)
	while (digitalRead(2) == LOW) { }
	while (digitalRead(2) == HIGH) { }
	T = micros() - T;
	
	frequency = 1.0E6 / T;

	/* Serial */
	Serial.println(frequency, 6);
	/* /Serial */

	/* LCD */
	lcd.setCursor(0, 0);
	lcd.print(frequency);
	/* /LCD */
	
	delay(100);
}
