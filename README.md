# Wifi enabled door unlocker

## To setup:

You'll need an FTDI USB to TTL serial adapter to program the ESP8266 (I used an ESP8266-01).

**Arduino**

	* With the additional board manager added: http://arduino.esp8266.com/stable/package_esp8266com_index.json
	* Add the esp8266 in boards manager
	* Select generic ESP8266

**Helpful website for 8266:**

	* https://www.hackster.io/rayburne/esp8266-01-using-arduino-ide-67a124

![a picture of 8266 pinout]
(https://hackster.imgix.net/uploads/image/file/53985/Step%201%20-%20Locate%20Image.jpg?w=680&h=510&fit=max&fm=jpg)

## To program:

	1. Make sure the jumper on the FTDI adapter is set to 3.3v
	2. 8266 can be powered off of the FTDI VCC & GND, be sure to put at least a 470uF cap between VCC and GND
	3. Connect 8266 Tx to FTDI Rx, 8266 Rx to FTDI Tx
	4. Add pull-down resistor to 8266 GPIO0 (200 - 1k work fine, 10k prob ok also)
	5. Power up 8266 (or reset by shorting the RST to GND)
	6. Program via Arduino
	7. Program will begin to run following programming, but if reset will go back into programming mode. Recommend removing the pull-down on GPIO0 (add pull-up to GPIO0 and GPIO2)