#include "/usr/share/arduino/hardware/arduino/cores/arduino/WString.h"

#include "ardu.hpp"

#ifdef __cplusplus
extern "C" {
#endif
  
#include "ardu.h"

  Arduino *arduino;
  
  void pinMode(uint8_t p, uint8_t m){
  return arduino->pinMode(p, m);
}
  
  void digitalWrite(uint8_t v, uint8_t w){
  return arduino->digitalWrite(v, w);
}
  
  int digitalRead(uint8_t w){
  return arduino->digitalRead(w);
}
  
  int analogRead(uint8_t w){
  return arduino->analogRead(w);
}
  
  void analogReference(uint8_t mode){
  arduino->analogReference(mode);
}
  
  void delay(unsigned long d){
  return arduino->delay(d);
}
  unsigned long millis(void){
  return arduino->millis();
}
  void delayMicroseconds(unsigned int us){
    return arduino->delayMicroseconds(us);
}

#ifdef __cplusplus
}
#endif
