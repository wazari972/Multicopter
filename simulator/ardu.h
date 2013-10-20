#include <stdint.h>


#ifdef __cplusplus
extern "C"{
#endif
  
typedef char byte;
//typedef char uint8_t;
#define PROGMEM

#define HIGH 1
#define LOW 1
#define EXTERNAL 1

#include "/usr/share/arduino/hardware/arduino/cores/arduino/WString.h"
void pinMode(uint8_t p, uint8_t m);
void digitalWrite(uint8_t v, uint8_t w);
int digitalRead(uint8_t w);
int analogRead(uint8_t w);
void analogReference(uint8_t mode);

void delay(unsigned long d);
unsigned long millis(void);
void delayMicroseconds(unsigned int us);

#define PSTR(x) x

#ifdef __cplusplus
}
#endif
