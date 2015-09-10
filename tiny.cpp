#include "Tiny.h"
#include "Wire.h"

//PRIVATE

void ATtinyExtender::write8(uint8_t reg, uint8_t data) {
	Wire.beginTransmission(TINY24_ADDR);
	Wire.write((byte)reg);
	Wire.write((byte)data);
	Wire.endTransmission();
}
uint8_t ATtinyExtender::read8(uint8_t reg) {
	Wire.beginTransmission(TINY24_ADDR);
	Wire.write((byte)reg);
	Wire.endTransmission();
	Wire.requestFrom(TINY24_ADDR, 1);
	return Wire.read();
}
uint16_t ATtinyExtender::read16(uint8_t reg) {
	Wire.beginTransmission(TINY24_ADDR);
	Wire.write((byte)reg);
	Wire.endTransmission();
	Wire.requestFrom(TINY24_ADDR, 2);
	return (Wire.read()<<8)|Wire.read();
}

//PUBLIC

ATtinyExtender::ATtinyExtender(void) {}

void ATtinyExtender::begin(void) {
	Wire.begin(0, 2);
}

void ATtinyExtender::pinMode(uint8_t pin, uint8_t mode) {
	ATtinyExtender::write8(pin-1, mode);
}
boolean ATtinyExtender::digitalRead(uint8_t pin) {
	return ATtinyExtender::read8(8+((pin-1)&7));
}
void ATtinyExtender::digitalWrite(uint8_t pin, boolean onoff) {
	ATtinyExtender::write8(16+((pin-1)&7), onoff);
}
uint16_t ATtinyExtender::analogRead(uint8_t pin) {
	return ATtinyExtender::read16(23+pin);//24+pin-1
}
void ATtinyExtender::analogWrite(uint8_t pin, uint8_t value) {
	uint8_t reg;
	switch (pin) {
		case 8: reg=29;break;
		case TA4: reg=30;break;
		case TA5: reg=31;break;
		default: return;
	}
	ATtinyExtender::pinMode(pin, OUTPUT);
	ATtinyExtender::write8(reg, value);
}
void ATtinyExtender::analogReference(uint8_t mode) {
	ATtinyExtender::write8(32, mode);
}
ATtinyExtender Tiny = ATtinyExtender();
