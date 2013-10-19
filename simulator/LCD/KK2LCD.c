#include <stdint.h>
#include <avr/io.h>  
#include <stdio.h>

#include "include/fonts.h"

void st7565WriteLogo() {}

void st7565Init( FONT_DEF_STRUCT * font ){}
void st7565SetBrightness( uint8_t val ){}
void st7565SetFont( FONT_DEF_STRUCT * font ){}
void st7565DrawString_P(uint16_t x, uint16_t y, char* text ){}
void st7565DrawString(uint16_t x, uint16_t y, char* text ){
printf("(%d, %d) %s\n", x, y, text);
}
void st7565Refresh( void ){}
void st7565ClearBuffer( void ){}
void st7565DrawChar(uint16_t x, uint16_t y, uint8_t c ){}


