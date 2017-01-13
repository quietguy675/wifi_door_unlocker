# Wifi enabled door unlocker

**To setup:**
You'll need an FTDI USB to TTL serial adapter to program the ESP8266 (I used an ESP8266-01).
Arduino
	-With the additional board manager added: http://arduino.esp8266.com/stable/package_esp8266com_index.json
	-Add the esp8266 in boards manager
	-Select generic ESP8266
Helpful website for 8266:
	-https://www.hackster.io/rayburne/esp8266-01-using-arduino-ide-67a124

**To program:**
	-Make sure the jumper on the FTDI adapter is set to 3.3v
	-8266 can be powered off of the FTDI VCC & GND, be sure to put at least a 470uF cap between VCC and GND
	-Connect 8266 Tx to FTDI Rx, 8266 Rx to FTDI Tx
	-Add pull-down resistor to 8266 GPIO0 (200 - 1k work fine, 10k prob ok also)
	-Power up 8266 (or reset by shorting the RST to GND)
	-Program via Arduino
	-Program will begin to run following programming, but if reset will go back into programming mode. Recommend removing the pull-down on GPIO0 (pull-up)