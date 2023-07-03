// arduinoCode.ino | Main code for the MechPad project by AdriTeixeHax.

#include "Coordinator.hpp"

void setup(void)
{
	Coordinator coordinator;

	while(true) // Main loop
	{
		coordinator.loop();
	}
}

void loop(void) { /* UNUSED LOOP */ }