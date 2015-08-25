import getpass
import sys
import telnetlib

tn = telnetlib.Telnet('192.168.1.168', 2000)

while 1:
	print tn.read_some().strip()
