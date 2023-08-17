// arduinoCode.ino | Main code for the MechPad project by AdriTeixeHax.

//#define GET_I2C_DEVICES

#include "Coordinator.h"

void setup(void)
{
	Coordinator coordinator;
	Serial.begin(9600);

	while(true) // Main loop
	{
		coordinator.loop();
	}
}

void loop(void) { /* UNUSED LOOP */ }

#ifdef GET_I2C_DEVICES

#include <Wire.h>

void setup()
{
	Wire.begin();
	Serial.begin(9600);
}

void loop()
{
	byte returnCode, address;
	int devicesFound = 0;
	Serial.println("\nSearching for devices...");

	for (address = 1; address < 127; address++ )
	{
		Wire.beginTransmission(address);
		returnCode = Wire.endTransmission();

		if (returnCode == 0)
		{
			Serial.print("Device found at address 0x");
			if (address < 16) Serial.print("0");
			Serial.print(address, HEX);

			devicesFound++;
		}
		else if (returnCode == 4)
		{
			Serial.print("Unknown error at adress 0x");
			if (address < 16) Serial.print("0");
			Serial.println(address, HEX);
		}
	}
	if (devicesFound == 0) Serial.println("No devices were found.");
	delay(1000);
}

#endif