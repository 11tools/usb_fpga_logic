#ifndef __LCD_H
#define __LCD_H

#include "fx2.h"                                                    

#define 	uint16_t	unsigned int
#define 	uint32_t  unsigned long 
#define 	uint8_t   unsigned char	
#define 	u8 				uint8_t
#define 	u32 			uint32_t
#define 	u16 			uint16_t


sbit  LCD_RST=0x80 + 2;
sbit  LCD_SCL=0x80 + 3;
sbit  LCD_DC =0x80 + 4;
sbit  LCD_SDA=0x80 + 5;



/*???????????????=1??????=0*/
#define 	HV_mode 	0

/*??????????????????????????????????????*/
#if	HV_mode
	#define  LCD_HEIGHT		320
	#define  LCD_WIDTH		240
#else
	#define  LCD_HEIGHT		240
	#define  LCD_WIDTH		320
#endif

/*?????§³*/
#define STR_WIDTH		12		    /* ??????? */
#define STR_HEIGHT	24			  /* ?????? */

#define COVER 1								/*????????????*/		
#define TRANS 0								/*???????????*/	

#define RED    0xf800
#define GREEN  0x07e0
#define BLUE   0x001f
#define YELLOW 0xffe0
#define WHITE  0xffff
#define BLACK  0x0000
#define PURPLE 0xf81f

#define	BACKGROUND	WHITE

extern uint16_t CH_HEIGHT;			/* ??????? */
extern uint16_t CH_WIDTH;			/* ??????? */
extern uint16_t CH_SIZE;

void LCD_9341init(void);
void LCD_Clear(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void LCD_OpenWindow(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
void LCD_SetPoint(uint16_t x , uint16_t y , uint16_t color)	;
void LCD_DispChar(uint16_t x, uint16_t y, uint8_t ascii, uint16_t color,uint8_t mode,uint8_t Char_size);
void LCD_Show_String(uint16_t x, uint16_t y, uint8_t *p, uint8_t len, uint16_t color,uint8_t mode,uint8_t Char_size);
void LCD_Show_CH_Atcode(uint16_t x,uint16_t y,uint8_t zimo[],uint16_t color,uint8_t Char_size);
void LCD_Show_ImageAtInterior(uint16_t x, uint16_t y,uint16_t m, uint16_t n,const unsigned char zimo[]);
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 , uint16_t color);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color);
void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint16_t color,uint8_t Char_size);


#endif


