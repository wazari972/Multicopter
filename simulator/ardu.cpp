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
  if (v == 13) {
    this->kkcom->ledState(w);
    return;
  }
  printf("digitalWrite %d %d\n", v, w);
}

int Arduino::digitalRead(uint8_t w) {
  if (w >= 14 && w <=18) {
    return this->kkcom->buttonPressed(w % 14);
  }
  printf("digitalRead %d\n", w);
  return 0;
}

int Arduino::analogRead(uint8_t w) {
  if (w >= 1 && w <= 7) {
    return -1;
  }
  printf("analogRead %d\n", w);
  return 0;
}

void Arduino::analogReference(uint8_t mode) {
  printf("analogReference, mode\n", mode);
}

void Arduino::delay(unsigned long d) {
  printf("delay %d\n", d);
  usleep(d*1000);
  printf("delay %d done\n", d);
}

unsigned long Arduino::millis(void) {
  printf("millis\n");
  return 0;
}

void Arduino::delayMicroseconds(unsigned int us) {
  //printf("delayMicroseconds, %u\n", us);
  usleep(us);
}

extern "C" {
  void setup(void);
  void loop();

  void prepare(Arduino *ardu);
}

void Arduino::ssetup(void) {
  prepare(this);
  printf("setup\n");
  setup();
}


void Arduino::lloop(void) {
  printf("loop\n");
  loop();
}
