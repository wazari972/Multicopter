#include "ardu.h"

#include <unistd.h>

void pinMode(uint8_t, uint8_t){}
void digitalWrite(uint8_t, uint8_t){}
int digitalRead(uint8_t){return 0;}
int analogRead(uint8_t){}
void analogReference(uint8_t mode){}

void delay(unsigned long d){
  sleep(d/1000);
}
unsigned long millis(void){return 0;}
void delayMicroseconds(unsigned int us){
  sleep(us/100000);
}

void setup(void);
void loop(void);

int main(int argc, char *argv[]) {
  setup();
  loop();
  return 0;
}
