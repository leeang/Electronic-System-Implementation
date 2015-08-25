#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);

void setup() {
	mySerial.begin(9600);
}

void loop() {
	int vol = millis() / 1000;
	
	mySerial.print("?realTemp=");
	mySerial.print(vol);
	mySerial.println(" HTTP/1.1");
	
	delay(2000);
}
