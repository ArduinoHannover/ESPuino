#ifndef TINY_H
#define TINY_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "Wire.h"

#ifndef A1
#define A1  1
#else
#warning "A1 is already defined. Use TA1 to address the right pin on the ATtiny."
#endif
#ifndef A2
#define A2  2
#else
#warning "A2 is already defined. Use TA2 to address the right pin on the ATtiny."
#endif
#ifndef A3
#define A3  3
#else
#warning "A3 is already defined. Use TA3 to address the right pin on the ATtiny."
#endif
#ifndef A4
#define A4  4
#else
#warning "A4 is already defined. Use TA4 to address the right pin on the ATtiny."
#endif
#ifndef A5
#define A5  5
#else
#warning "A5 is already defined. Use TA5 to address the right pin on the ATtiny."
#endif

#define TINY24_ADDR 0x10

#define TA1  1
#define TA2  2
#define TA3  3
#define TA4  4
#define TA5  5

#define LED_BUILTIN 14

class ATtinyExtender {
	private:
		void write8(uint8_t, uint8_t);
		uint8_t read8(uint8_t);
		uint16_t read16(uint8_t);
	public:
		ATtinyExtender(void);
		void begin(void);
		void pinMode(uint8_t, uint8_t);
		boolean digitalRead(uint8_t);
		void digitalWrite(uint8_t, boolean);
		uint16_t analogRead(uint8_t);
		void analogWrite(uint8_t, uint8_t);
		void analogReference(uint8_t);
};
extern ATtinyExtender Tiny;
#endif //TINY_H
