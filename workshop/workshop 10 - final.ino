/********* ********* ********* ********* ********* ********* ********* ********* *********

Title:			Workshop Final Project - Temperature Controller
Board:			Arduino Uno R3

Author:			Ang Li
E-mail:			ang#ang.im	(substitute @ for #)
Blog:			http://blog.leeang.com/
Github:			https://github.com/leeang/Electronic-System-Implementation

********* ********* ********* ********* ********* ********* ********* ********* *********/

#include <LiquidCrystal.h>
#include <IRremote.h>

#define IR_PIN		4
#define TEC_P_PIN	5
#define TEC_N_PIN	6
#define LCD_PIN		9

#define FAST 		112
#define SLOW 		80

LiquidCrystal lcd(7, 8, 10, 11, 12, 13);
// lcd(RS, Enable, D4, D5, D6, D7)

IRrecv irrecv(IR_PIN);
decode_results results;
// IR remote configuarion

float set = 25;
unsigned long T;

void setup() {
	Serial.begin(9600);
	// UART

	irrecv.enableIRIn();
	// IR remote

	pinMode(TEC_P_PIN, OUTPUT);
	pinMode(TEC_N_PIN, OUTPUT);
	// H bridge control

	pinMode(LCD_PIN, OUTPUT);
	analogWrite(LCD_PIN, 102);
	// LCD display constrast

	lcd.begin(16, 2);
	// LCD initialization

	delay(1000);
}

void loop() {
/* --------- UART Rx --------- --------- */
	char inChar = 0;
	while (Serial.available() > 0) {
		inChar = Serial.read();
	}

	if (inChar) {
		switch (inChar) {
			case 'U':	// Up
				set += 1;
				break;
			case 'D':	// Down
				set -= 1;
				break;
			case 'L':	// Left
				set -= 5;
				break;
			case 'R':	// Right
				set += 5;
				break;
		}
		set = constrain(set, 5, 45);
	}
/* --------- /UART Rx --------- */

/* --------- IR remote --------- --------- */
	for (long i=0; i<10000; i++) {
		if (irrecv.decode(&results)) {
			long value = results.value;
			switch (value) {
				case 0x2FD9867:	//Up
					set += 1;
					break;
				case 0x2FDB847:	//Down
					set -= 1;
					break;
				case 0x2FD42BD:	//Left
					set -= 5;
					break;
				case 0x2FD02FD:	//Right
					set += 5;
					break;
			}
			irrecv.resume();

			set = constrain(set, 5, 45);
		}
	}
/* --------- /IR remote --------- */
	unsigned long TSum = 0;
	for (int i = 0; i < 100; ++i) {
		while (digitalRead(2) == LOW) { }
		while (digitalRead(2) == HIGH) { }
		
		T = micros();
		while (digitalRead(2) == LOW) { }
		while (digitalRead(2) == HIGH) { }
		T = micros() - T;
		TSum += T;
	}
	T = TSum / 100;

	double frequency = 1.0E6 / T;
	float real = 2.57636E-07 * pow(frequency, 3.0) - 8.12036E-04 * pow(frequency, 2.0) + 9.74482E-01 * frequency - 3.65980E+02;

	float difference = real - set;

	if (fabs(difference) <= 0.5) {
		analogWrite(TEC_P_PIN, 0);
		analogWrite(TEC_N_PIN, 0);
	} else if (difference > 3) {
		if (set > 15) {
			analogWrite(TEC_P_PIN, FAST);
		} else {
			analogWrite(TEC_P_PIN, 1.5 * FAST);
		}
		analogWrite(TEC_N_PIN, 0);
	} else if (difference > 0.5) {
		if (set > 15) {
			analogWrite(TEC_P_PIN, SLOW);
		} else {
			analogWrite(TEC_P_PIN, 1.5 * SLOW);
		}
		analogWrite(TEC_N_PIN, 0);
	} else if (difference < -3) {
		analogWrite(TEC_P_PIN, 0);
		analogWrite(TEC_N_PIN, FAST);
	} else if (difference < -0.5) {
		analogWrite(TEC_P_PIN, 0);
		analogWrite(TEC_N_PIN, SLOW);
	}
	
/* --------- UART Tx --------- --------- */
	Serial.print(frequency);
	Serial.print("\t");
	Serial.print(real, 1);
	Serial.print("\t");
	Serial.print(set, 1);
	Serial.print("\t");
	Serial.println(difference);
/* --------- /UART Tx --------- */

/* --------- LCD --------- --------- */
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Set  ");
	lcd.print(set, 1);
	lcd.setCursor(0, 1);
	lcd.print("Real ");
	lcd.print(real, 1);
/* --------- /LCD --------- */
}
