/*
 * Copyright (c) 2015, Majenko Technologies
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 * 
 * * Neither the name of Majenko Technologies nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// Companion sketch for the MagicScope example in ViSi-Genie.
// Requires a PRO license for ViSi-Genie to operate.

#include <genieArduino.h>
#include <SoftwareSerial.h>

Genie genie;

// Use softwrae serial on pins 2 and 3, which means set the RX and TX jumpers on 
// the Arduino breakout board to use D2 and D3.
SoftwareSerial serial(2, 3);

// This is the "Refresh" size on the scope widget
const int REFRESH = 20;

// We need one more value, which is the ID of the scope object
// the data is being sent to.
uint16_t valueBuffer[REFRESH+1];

void setup() {
	serial.begin(9600);
	genie.Begin(serial);
}

void loop() {
	static float j = 0.0;

	valueBuffer[0] = 0;	// Talking to scope number 0

	// Fill the rest of the buffer with a sine wave
	for(int i = 0; i < REFRESH; i++) {
		valueBuffer[i+1] = 50 + (sin((i/3.0)+j)*50.0);
	}

	// Send it to the Magic component 0
	genie.WriteMagicDBytes(0, valueBuffer, REFRESH+1);

	j += 0.1;
}
