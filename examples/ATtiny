/*
 * Copy this program to an ATtiny24 (44 or 84 are also suitable but oversized in Flash) using a ISP-Programmer.
 * A modified Library to support ATtiny24 is available in the GitHub repo, aswell as TinyWireS.
 * First copy the attiny folder to ~/hardware/ and the TinyWireS to ~/libraries/
 * Select ATtiny under Tools>Boards, ATtiny24 from Tools>Processor and 1 or 8 MHz (internal) from Tools>Clock.
 * Burn the bootloader (which will set the fuses for the right oscillation).
 * Now you can press Upload.
 * Files can be found at github.com/ArduinoHannover
*/
#define I2C_SLAVE_ADDRESS 0x10
#include <TinyWireS.h>
#ifndef TWI_RX_BUFFER_SIZE
#define TWI_RX_BUFFER_SIZE ( 16 )
#endif

#define ESP_D6  10
#define ESP_D7  9
#define ESP_D8  8  //PWM
//ANALOG
#define ESP_1 1
#define ESP_2 2
#define ESP_3 3
#define ESP_4 5
#define ESP_5 7
//ANALOG as DIGITAL
#define ESP_A1 A1
#define ESP_A2 A2
#define ESP_A3 A3
#define ESP_A4 A5  //PWM
#define ESP_A5 A7  //PWM

uint8_t pins[] = {
  ESP_A1,
  ESP_A2,
  ESP_A3,
  ESP_A4,
  ESP_A5,
  ESP_D6,
  ESP_D7,
  ESP_D8
}, arpins[] = {
  ESP_1,
  ESP_2,
  ESP_3,
  ESP_4,
  ESP_5
}, awpins[] = {
  ESP_D8,
  ESP_A4,
  ESP_A5
};

uint8_t reg;
volatile boolean isOn, fBit;
volatile uint16_t aVal;

void setup() {
  TinyWireS.begin(I2C_SLAVE_ADDRESS);
  TinyWireS.onReceive(receiveEvent);
  TinyWireS.onRequest(requestEvent);
}

void requestEvent() {
  if (reg >= 16) {
    if (fBit) TinyWireS.send(highByte(aVal));
    else TinyWireS.send(lowByte(aVal));
    fBit = false;
  } else {
    TinyWireS.send((byte)isOn);
  }
}

void receiveEvent(uint8_t bytesReceived) {
  if (bytesReceived < 1 || bytesReceived > TWI_RX_BUFFER_SIZE))return;
  reg = TinyWireS.receive();
  uint8_t val;
  bytesReceived--;
  uint8_t value; //will be zero [off/input] if missing the value param in transmission
  if (bytesReceived) {
    value = TinyWireS.receive(); //will discard second param if sent and not needed (read action)
    bytesReceived--;
  }
  if (reg < 8) {
    pinMode(pins[reg], value);return;
  } else if (reg < 16) {
    isOn = digitalRead(pins[reg-8]);return;
  } else if (reg < 24) {
    digitalWrite(pins[reg-16], value);return;
  } else if (reg < 29) {
    aVal = analogRead(arpins[reg-24]);fBit=true;return;
  } else if (reg < 32) {
     analogWrite(awpins[reg-29], value);return;
  }
  while (bytesReceived) {
    TinyWireS.receive(); //discard
    bytesReceived--;
  }
}
void loop() {
  TinyWireS_stop_check();
}
