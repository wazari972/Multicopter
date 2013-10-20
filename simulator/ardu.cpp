#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "ardu.hpp"

Arduino::Arduino(KKComm *kkcom) {
  this->kkcom = kkcom;
}

void Arduino::pinMode(uint8_t p, uint8_t m) {
  printf("pinMode %d %d\n", p, m);
}

void Arduino::digitalWrite(uint8_t v, uint8_t w) {
  printf("digitalWrite %d %d\n", v, w);
}

int Arduino::digitalRead(uint8_t w) {
  printf("digitalRead %d\n", w);
  return 0;
}

int Arduino::analogRead(uint8_t w) {
  printf("analogRead %d\n", w);
  return 0;
}

void Arduino::analogReference(uint8_t mode) {
  printf("analogReference, mode\n", mode);
}

void Arduino::delay(unsigned long d) {
  printf("delay %d\n", d);
  sleep(d);
}

unsigned long Arduino::millis(void) {
  printf("millis\n");
  return 0;
}

void Arduino::delayMicroseconds(unsigned int us) {
  printf("delayMicroseconds, %ud\n", us);
}

extern "C" {
  void setup(void);
  void loop();
}

void Arduino::ssetup(void) {
  printf("setup\n");
  setup();
}


void Arduino::lloop(void) {
  printf("loop\n");
  loop();
}
