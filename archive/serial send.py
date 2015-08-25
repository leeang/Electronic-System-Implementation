import serial
import time

ser = serial.Serial('com4', 9600)
i = 0

while 1 :
	ser.write(str(i))
	time.sleep(1)
	i = i + 1
	if i>10 :
		i = 0
