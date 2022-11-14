#include "lcd.h"
#include "ascii.h"

uint16_t CH_SIZE=0;
/*oo¡Á?¡ä¨®D?*/
uint16_t CH_HEIGHT=16	;			/* oo¡Á??¨ª?¨¨ */
uint16_t CH_WIDTH=16	;			/* oo¡Á??¨ª?¨¨ */

void LCD_delay(uint16_t count)   /* X10ms */
{
	 uint16_t i,j;
		for(i=0;i<count;i++)        
				for(j=0;j<50;j++);             
}



void  LCD_ILI9341_CMD(uint16_t c)
{
	uint16_t i;
	LCD_DC=0;
	for(i=0;i<8;i++)
	{
		if(c &0x80)
			LCD_SDA=1;
		else 
			LCD_SDA=0;
		
		LCD_SCL=0;
		LCD_SCL=1;
		c <<=1;
	} 
}

void LCD_ILI9341_Parameter(uint16_t dat)
{
	uint16_t i;
	LCD_DC=1;
	for(i=0;i<8;i++)
	{
		if(dat&0x80)
			LCD_SDA=1;
		else 
			LCD_SDA=0;
		LCD_SCL=0;
		LCD_SCL=1;
		dat<<=1;
	}
}

void LCD_Write_Data(uint16_t dat16)
{
  LCD_ILI9341_Parameter(dat16>>8);
  LCD_ILI9341_Parameter(dat16);
}

void  LCD_9341init(void)
{ 
	LCD_RST=1; 
	LCD_delay(10);                                                              //Delay 1ms 
	LCD_RST=0; 
	LCD_delay(200);                                                              //Delay 1ms 
	LCD_RST=1; 
	LCD_delay(200);                                                              //Delay 120ms 
	//************* Start Initial Sequence **********//
	/*  Power control B (CFh)  */
	LCD_delay(50);
	LCD_ILI9341_CMD(0xCF);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0xC1);
	LCD_ILI9341_Parameter(0X30);
		 
	LCD_ILI9341_CMD(0xED);
	LCD_ILI9341_Parameter(0x64);
	LCD_ILI9341_Parameter(0x03);
	LCD_ILI9341_Parameter(0X12);
	LCD_ILI9341_Parameter(0X81);
		 
	LCD_ILI9341_CMD(0xE8);
	LCD_ILI9341_Parameter(0x85);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x79);

	LCD_ILI9341_CMD(0xCB);
	LCD_ILI9341_Parameter(0x39);
	LCD_ILI9341_Parameter(0x2C);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x34);
	LCD_ILI9341_Parameter(0x02);

	LCD_ILI9341_CMD(0xF7);
	LCD_ILI9341_Parameter(0x20);

	LCD_ILI9341_CMD(0xEA);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x00);

	LCD_ILI9341_CMD(0xC0); //Power control
	LCD_ILI9341_Parameter(0x1D);

	LCD_ILI9341_CMD(0xC1); 
	LCD_ILI9341_Parameter(0x12);

	LCD_ILI9341_CMD(0xC5); 
	LCD_ILI9341_Parameter(0x33);
	LCD_ILI9341_Parameter(0x3F);

	LCD_ILI9341_CMD(0xC7); 
	LCD_ILI9341_Parameter(0x92);

	LCD_ILI9341_CMD(0x3A); // Memory Access Control
	LCD_ILI9341_Parameter(0x55);

	LCD_ILI9341_CMD(0x36); // Memory Access Control
	#if HV_mode
	LCD_ILI9341_Parameter(0x08);
	#else
	LCD_ILI9341_Parameter(0x6b);
	
	#endif
	
	LCD_ILI9341_CMD(0xB1);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x12);

	LCD_ILI9341_CMD(0xB6); // Display Function Control
	LCD_ILI9341_Parameter(0x0A);
	LCD_ILI9341_Parameter(0xA2);

	LCD_ILI9341_CMD(0x44);
	LCD_ILI9341_Parameter(0x02);

	LCD_ILI9341_CMD(0xF2); // 3Gamma Function Disable
	LCD_ILI9341_Parameter(0x00);

	LCD_ILI9341_CMD(0x26); //Gamma curve selected
	LCD_ILI9341_Parameter(0x01);

	LCD_ILI9341_CMD(0xE0); //Set Gamma
	LCD_ILI9341_Parameter(0x0F);
	LCD_ILI9341_Parameter(0x22);
	LCD_ILI9341_Parameter(0x1C);
	LCD_ILI9341_Parameter(0x1B);
	LCD_ILI9341_Parameter(0x08);
	LCD_ILI9341_Parameter(0x0F);
	LCD_ILI9341_Parameter(0x48);
	LCD_ILI9341_Parameter(0xB8);
	LCD_ILI9341_Parameter(0x34);
	LCD_ILI9341_Parameter(0x05);
	LCD_ILI9341_Parameter(0x0C);
	LCD_ILI9341_Parameter(0x09);
	LCD_ILI9341_Parameter(0x0F);
	LCD_ILI9341_Parameter(0x07);
	LCD_ILI9341_Parameter(0x00);

	LCD_ILI9341_CMD(0XE1); //Set Gamma
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x23);
	LCD_ILI9341_Parameter(0x24);
	LCD_ILI9341_Parameter(0x07);
	LCD_ILI9341_Parameter(0x10);
	LCD_ILI9341_Parameter(0x07);
	LCD_ILI9341_Parameter(0x38);
	LCD_ILI9341_Parameter(0x47);
	LCD_ILI9341_Parameter(0x4B);
	LCD_ILI9341_Parameter(0x0A);
	LCD_ILI9341_Parameter(0x13);
	LCD_ILI9341_Parameter(0x06);
	LCD_ILI9341_Parameter(0x30);
	LCD_ILI9341_Parameter(0x38);
	LCD_ILI9341_Parameter(0x0F);
	LCD_ILI9341_CMD(0x11); //Exit Sleep
	LCD_delay(120);
	LCD_ILI9341_CMD(0x29); //Display on 
} 

void LCD_Clear(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)
{
	uint16_t i = 0,j=0;
	
	/* column address control set */
	LCD_ILI9341_CMD(0X2a);
	LCD_ILI9341_Parameter( x >> 8 );	 /* ?¨¨??8??¡ê?¨¨?o¨®¦Ì¨ª8?? */
	LCD_ILI9341_Parameter( x & 0xff );	         /* column start   */ 
	LCD_ILI9341_Parameter( (x+width-1) >> 8 );   /* column end   */
	LCD_ILI9341_Parameter( (x+width-1) & 0xff );
	
	/* page address control set */	
  LCD_ILI9341_CMD(0X2b); 			     
	LCD_ILI9341_Parameter( y >> 8 );			/* page start   */
	LCD_ILI9341_Parameter( y & 0xff );
	LCD_ILI9341_Parameter( (y+height-1) >> 8);  /* page end     */
	LCD_ILI9341_Parameter( (y+height-1) & 0xff);

	LCD_ILI9341_CMD(0x2c);	
	for( i=0; i < height ; i++ )
	{
		for(j=0;	j < width;	j++)
			{
				LCD_Write_Data( color );
			}
			
	}	
}
void LCD_SetCursor(uint16_t x, uint16_t y)	
{	
	LCD_ILI9341_CMD(0X2a); 				 /* ¨¦¨¨??X¡Á?¡À¨º */
	LCD_ILI9341_Parameter(x>>8);	 /* ?¨¨??8??¡ê?¨¨?o¨®¦Ì¨ª8?? */
	LCD_ILI9341_Parameter(x&0xff);	 /* ¨¦¨¨???e¨º?¦Ì?o¨ª?¨¢¨º?¦Ì?*/
	LCD_ILI9341_Parameter(x>>8);
	LCD_ILI9341_Parameter(x&0xff);

  LCD_ILI9341_CMD(0X2b); 			     /* ¨¦¨¨??Y¡Á?¡À¨º*/
	LCD_ILI9341_Parameter(y>>8);
	LCD_ILI9341_Parameter(y&0xff);
	LCD_ILI9341_Parameter(y>>8);
	LCD_ILI9341_Parameter(y&0xff);
	

	//delay(50);	
}

void LCD_OpenWindow(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{	
	
	LCD_ILI9341_CMD(0X2a); 				 /* ¨¦¨¨??X¡Á?¡À¨º */
	LCD_ILI9341_Parameter( x >> 8 );	 /* ?¨¨??8??¡ê?¨¨?o¨®¦Ì¨ª8?? */
	LCD_ILI9341_Parameter( x & 0xff );	 /* ¨¦¨¨???e¨º?¦Ì?o¨ª?¨¢¨º?¦Ì?*/
	LCD_ILI9341_Parameter( (x+width-1) >> 8 );
	LCD_ILI9341_Parameter( (x+width-1) & 0xff );

	LCD_ILI9341_CMD(0X2b); 			     /* ¨¦¨¨??Y¡Á?¡À¨º*/
	LCD_ILI9341_Parameter( y >> 8 );
	LCD_ILI9341_Parameter( y & 0xff );
	LCD_ILI9341_Parameter( (y+height-1) >> 8);
	LCD_ILI9341_Parameter( (y+height-1) & 0xff);	

	/* write gram start */
	LCD_ILI9341_CMD(0x2C);
}

void LCD_SetPoint(uint16_t x , uint16_t y , uint16_t color)	
{	
	LCD_SetCursor(x, y);
	
	LCD_ILI9341_CMD(0x2c);	         /* D¡ä¨ºy?Y */
	LCD_Write_Data(color);
}

void LCD_DispChar(uint16_t x, uint16_t y, uint8_t ascii, uint16_t color,uint8_t mode,uint8_t Char_size)
{
	unsigned long  page, column, temp, i;
	i = ascii - ' ';
	
	LCD_OpenWindow(x, y, STR_WIDTH*Char_size, STR_HEIGHT*Char_size);
	LCD_ILI9341_CMD(0X2C);	
	
	if(mode==COVER)
	{
		for( page=0; page < STR_HEIGHT*Char_size; page++ )
		{
			temp  =  asc2_2412[i][(page/Char_size)*2+1];
			temp  =  temp<<8;
			temp |=  asc2_2412[i][(page/Char_size)*2];
			for( column=0; column < STR_WIDTH*Char_size; column++ )
			{
				if( temp & (0x000001<<(column/Char_size) ))
				{
					LCD_Write_Data( color );
				}
				else
				{
					LCD_Write_Data( BACKGROUND );	
				}
				//temp >>= 1;		
				
			}/* ¨°?DDD¡ä¨ª¨º */
		}/* ¨¨?2?D¡ä¨ª¨º */
	}
	
	if(mode==TRANS)
	{
		for( page=0; page < STR_HEIGHT*Char_size; page++ )
		{
			temp  =  asc2_2412[i][(page/Char_size)*2+1];
			temp  =  temp<<8;
			temp |=  asc2_2412[i][(page/Char_size)*2];
			for( column=0; column < STR_WIDTH*Char_size; column++ )
			{
				if( temp & (0x00000001<<(column/Char_size)) )
					LCD_SetPoint(x+column,y+page,color);
							
			}/* ¨°?DDD¡ä¨ª¨º */
		}/* ¨¨?2?D¡ä¨ª¨º */
	}
}

void LCD_Show_String(uint16_t x, uint16_t y, uint8_t *p, uint8_t len, uint16_t color,uint8_t mode,uint8_t Char_size)
{
    uint8_t size = len;
	while(*p && size >= 0)
	{
		LCD_DispChar(x,y,*p++,color,mode,Char_size);
		x+=(STR_WIDTH*Char_size);
		size--;
	}
}

void LCD_Show_CH_Atcode(uint16_t x,uint16_t y,uint8_t zimo[],uint16_t color,uint8_t Char_size)
{
	uint32_t page, column;
	unsigned long temp;
	unsigned long  a,b,c;
	for( page=0; page < CH_HEIGHT*Char_size; page++ )
		{		
			if(CH_SIZE==1)
			{
				a=zimo[((page/Char_size)*3)];
				b=zimo[((page/Char_size)*3+1)];
				c=zimo[((page/Char_size)*3+2)];	
				temp=c<<16 | b<<8 | a<<0;

			}
			else
			{
				a=zimo[((page/Char_size)*2)];
				b=zimo[((page/Char_size)*2+1)];
				temp= b<<8 | a<<0;
			}
			for( column=0; column < CH_WIDTH*Char_size; column++ )
			{
				if( temp & ((unsigned long)0x00000001<<(column/Char_size) ) )
					LCD_SetPoint(x+column,y+page,color);					
			}/* ¨°?DDD¡ä¨ª¨º */
		}/* ¨¨?2?D¡ä¨ª¨º */
}

void LCD_Show_ImageAtInterior(uint16_t x, uint16_t y,uint16_t m, uint16_t n,const unsigned char zimo[])
{

	long i=0;
	LCD_OpenWindow(x, y, m, n);
	LCD_ILI9341_CMD(0X2C);	
	
	for(i=0;i<(long)(m*n);i++)
		LCD_Write_Data( ( (unsigned int)((zimo[2*i])<<8)| (zimo[2*i+1]) ) );
	
}

void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 , uint16_t color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //????¡Á?¡À¨º??¨¢? 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //¨¦¨¨??¦Ì£¤2?¡¤??¨° 
	else if(delta_x==0)incx=0;//¡ä1?¡À?? 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//?????? 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //??¨¨??¨´¡À???¨¢?¡Á?¡À¨º?¨¢ 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//?-??¨º?3? 
	{  
		LCD_SetPoint(uRow,uCol,color);//?-¦Ì? 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}    

void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	LCD_DrawLine(x1,y1,x2,y1,color);
	LCD_DrawLine(x1,y1,x1,y2,color);
	LCD_DrawLine(x1,y2,x2,y2,color);
	LCD_DrawLine(x2,y1,x2,y2,color);
}


void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //?D??????¦Ì?????¦Ì?¡À¨º??
	while(a<=b)
	{
		LCD_SetPoint(x0-b,y0-a,color);             //3           
		LCD_SetPoint(x0+b,y0-a,color);             //0           
		LCD_SetPoint(x0-a,y0+b,color);             //1       
		LCD_SetPoint(x0-b,y0-a,color);             //7           
		LCD_SetPoint(x0-a,y0-b,color);             //2             
		LCD_SetPoint(x0+b,y0+a,color);             //4               
		LCD_SetPoint(x0+a,y0-b,color);             //5
		LCD_SetPoint(x0+a,y0+b,color);             //6 
		LCD_SetPoint(x0-b,y0+a,color);             
		a++;
		//¨º1¨®?Bresenham??¡¤¡§?-?2     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 
		LCD_SetPoint(x0+a,y0+b,color);
	}
} 

static uint32_t mypow(uint8_t m,uint8_t n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}	

void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint16_t color,uint8_t Char_size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_DispChar(x+(STR_WIDTH*Char_size)*t,y,' ',color,COVER,Char_size);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_DispChar(x+(STR_WIDTH*Char_size)*t,y,temp+'0',color,COVER,Char_size); 
	}
} 











