#include <stdint.h>
#include <stdio.h>

#include "ardu.hpp"
#include "emulino-gui.h"

#define CHECKBIT(ADDRESS,BIT) ((uint32_t)(ADDRESS & (1<<BIT)))

#ifdef __cplusplus
extern "C"{
#endif

#include "include/fonts.h"

  #include "logo.c"
  
  extern Arduino *arduino;
  
  static FONT_DEF_STRUCT *currentFont;

  void st7565DrawChar(uint16_t x, uint16_t y, uint8_t c );
  
  void st7565DrawPixel(int x, int y){
    if ((x >= 128) || (y >= 64)) return;
    arduino->kkcom->drawPixel(x, y);
  }
  
  void st7565Init(FONT_DEF_STRUCT *font ){
    printf("init\n");
    currentFont = font;
  }
  
  void st7565SetBrightness(uint8_t val ){}
  void st7565SetFont( FONT_DEF_STRUCT *font ){
    currentFont = font;
  }
  
  void st7565DrawString_P(uint16_t x, uint16_t y, char *text){
    for (unsigned int l = 0; l < strlen(text); l++) {
      st7565DrawChar(x + (l * (currentFont->Width + 1)), y, text[l] );
    }
  }
  void st7565DrawString(uint16_t x, uint16_t y, char* text ){
    st7565DrawString_P(x, y, text);
  }
  
  void st7565Refresh( void ){}
  void st7565ClearBuffer( void ){
    arduino->kkcom->clearScreen();
  }
  
  void st7565DrawChar(uint16_t x, uint16_t y, uint8_t c ){
    uint8_t bpc, b;
    uint8_t bytesPerChar = ((currentFont->Height-1) / 8 + 1 );	// calc how many bytes we need to read

    // Render each column
    uint16_t xoffset, yoffset;
    for (xoffset = 0; xoffset < currentFont->Width; xoffset++) {
      for (bpc = 0; bpc < bytesPerChar; bpc++) {
	b = currentFont->FontTable[((c - currentFont->FirstChar) * currentFont->Width * bytesPerChar)
				    + (xoffset * bytesPerChar) + bytesPerChar - bpc - 1]; 
	
	// not super-happy with this, but it works....	
	for (yoffset = 0; yoffset < currentFont->Height; yoffset++) {
	  if (yoffset/8 == bpc && CHECKBIT(b , yoffset%8)) {
	    st7565DrawPixel(x + xoffset,  y + currentFont->Height - yoffset);
	  }
	}
      }
    }
  }

  void st7565WriteLogo(void){
    for (int p = 0; p < 8; p++) {
      for (int c = 0; c < 128; c++) {
	for (int i = 0; i < 8; i++) {
	  if (buffer[128*p + c] & (0x80 >> i)) {
	    st7565DrawPixel(p+8*i, c);
	  }
	}
      }
    }
  }
  
#ifdef __cplusplus
}
#endif
