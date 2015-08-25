#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
	Serial.begin(9600);
	irrecv.enableIRIn();
}

void loop() {
	if (irrecv.decode(&results)) {
		long value = results.value;
		switch (value) {
			case 0x2FD9867:	//Up
				Serial.println("up");
				break;
			case 0x2FDB847:	//Down
				Serial.println("down");
				break;
			case 0x2FD42BD:	//Left
				Serial.println("left");
				break;
			case 0x2FD02FD:	//Right
				Serial.println("right");
				break;
		}
		irrecv.resume();
	}
	delay(100);
}
