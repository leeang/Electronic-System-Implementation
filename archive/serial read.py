import serial
ser = serial.Serial('com5', 9600)
line = ser.readline()

while line:
	print line,
	line = ser.readline()
