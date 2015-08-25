import random
import urllib, urllib2
import json

realTemp = random.randint(0, 5);

url = ''

values = {
	'realTemp' : realTemp,
}
data = urllib.urlencode(values)

req = urllib2.Request(url, data)
response = urllib2.urlopen(req)
data = response.read()
print data
