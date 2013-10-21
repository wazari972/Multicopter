
#ifdef __cplusplus
extern "C"{
#endif
  
#include "../ardu.h"

#include "/usr/share/arduino/hardware/arduino/cores/arduino/WString.h"

#include "include/io_cfg.h"

#include "include/st7565.h"

#include "include/font5x7.c"

#include "include/font12x16.c"

#include "include/font12x24Number.c"

void st7565WriteLogo();
  
#ifdef __cplusplus
}
#endif
g++ -c -I. -I/usr/share/arduino/hardware/arduino/variants/kk2/ -fpermissive -g -O0 -I../simulator/LCD project.c -o project.o
