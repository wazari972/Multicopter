#include "/usr/share/arduino/hardware/arduino/cores/arduino/WString.h"

#ifdef __cplusplus
extern "C"{
#endif

#include "ardu.h"

//#include <unistd.h>

void pinMode(uint8_t p, uint8_t m){}
void digitalWrite(uint8_t v, uint8_t w){}
int digitalRead(uint8_t w){return 0;}
int analogRead(uint8_t w){}
void analogReference(uint8_t mode){}

void delay(unsigned long d){
 
}
unsigned long millis(void){return 0;}
void delayMicroseconds(unsigned int us){
 
}

#ifdef __cplusplus
}
#endif
