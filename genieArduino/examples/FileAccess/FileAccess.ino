
// Companion sketch for the FileAccess example in ViSi-Genie Samples.
// Requires a PRO license for ViSi-Genie Magic to operate.

#include <genieArduino.h>

#define RESETLINE 4  // Change this if you are not using an Arduino Adaptor Shield Version 2 (see code below)

#define MFILE_READ 0
#define MFILE_WRITE 1
#define MFILE_APPEND 2
#define MFILE_ERASE 3
#define MFILE_DIR 4
#define MFILE_SCREEN_CAPTURE 5
#define MFILE_SIZE 6
#define NULL 0x00

Genie genie;


void setup() {
	Serial1.begin(9600);
	genie.Begin(Serial1); // Display attached to Serial1
	Serial.begin(9600); // Console in Arduino IDE on Serial0
//  genie.AttachEventHandler(myGenieEventHandler); // Attach the user function Event Handler for processing events
	genie.AttachMagicByteReader(myGenieByteHandler);
	
	// Reset the Display (change D4 to D2 if you have original 4D Arduino Adaptor)
	// THIS IS IMPORTANT AND CAN PREVENT OUT OF SYNC ISSUES, SLOW SPEED RESPONSE ETC
	// If NOT using a 4D Arduino Adaptor, digitalWrites must be reversed as Display Reset is Active Low, and
	// the 4D Arduino Adaptors invert this signal so must be Active High.
	pinMode(RESETLINE, OUTPUT);  // Set D4 on Arduino to Output (4D Arduino Adaptor V2 - Display Reset)
	digitalWrite(RESETLINE, 1);  // Reset the Display via D4
	delay(100);
	digitalWrite(RESETLINE, 0);  // unReset the Display via D4
	
	delay(5000);  //let the display start up after the reset (This is important)
}

void loop() {
	static uint32_t lastRun = 0;

	if (millis() > lastRun) {
		//Search for TESTDI~1.GCI on the microSD card in the Display
		byte searchString[] = {MFILE_DIR, 'F', 'I', 'L', 'E', 'A', 'C', '~', '1', '.', 'G', 'C', 'I', NULL};
		byte searchStringLength = sizeof(searchString);
		Serial.println("Sending test request...");
		// Request FileAccess Data
		genie.WriteMagicBytes(0, searchString, searchStringLength);
		lastRun = millis() + 5000;
	}

	genie.DoEvents(); // This calls the library each loop to process the queued responses from the display
}

void myGenieByteHandler(uint8_t index, uint8_t length) {
	Serial.print("Received ");
	Serial.print(length, DEC);
	Serial.print(" bytes from magic object ");
	Serial.println(index, DEC);

	for (int i = 0; i < length; i++) {
		uint8_t b = genie.GetNextByte();
		Serial.write(b);
	}

	Serial.println();
}
