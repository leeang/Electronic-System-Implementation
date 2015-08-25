import serial

import urllib, urllib2

ser = serial.Serial('com4', 9600)
realTemp = ser.readline().strip()

while realTemp:
	url = ''

	values = {
		'realTemp' : realTemp,
	}
	data = urllib.urlencode(values)

	req = urllib2.Request(url, data)
	response = urllib2.urlopen(req)
	setTemp = response.read().strip()
	ser.write(setTemp + "\n")
	print "Set: " + setTemp + " Real: " + realTemp

	realTemp = ser.readline().strip()
