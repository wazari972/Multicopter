#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/time.h>

#include "ardu.hpp"

Arduino::Arduino(KKComm *kkcom) {
  this->kkcom = kkcom;
}

void Arduino::pinMode(uint8_t p, uint8_t m) {
  //printf("pinMode %d %d\n", p, m);
}

void Arduino::digitalWrite(uint8_t v, uint8_t w) {
  if (v >= 0 && v <= 13) {
    this->kkcom->setPinState(v, w);
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
  if (w == 3) {
    return this->kkcom->getBat();
  }
  if (w == 1 || w == 2 || w == 4) {
    return this->kkcom->getGyro(w);
  }
  if (w == 5 || w == 6 || w == 7) {
    return this->kkcom->getAcc(w);
  }
  printf("analogRead %d\n", w);
  return 0;
}

void Arduino::analogReference(uint8_t mode) {
  printf("analogReference %d\n", mode);
}

void Arduino::delay(unsigned long d) {
  //printf("delay %d\n", d);
  usleep(d*1000);
  //printf("delay %d done\n", d);
}

unsigned long Arduino::millis(void) {
  struct timeval  tv;
  gettimeofday(&tv, NULL);
  
  unsigned long time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
  return time_in_mill;
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
