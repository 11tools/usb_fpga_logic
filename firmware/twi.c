 #include <string.h>
 #include <reg52.h>
 #include <intrins.h>
 
 #include "twi.h"


 #define DELAY_TIME 60
 #define TRUE 1
 #define FALSE 0

 sbit SCL=0x80 + 0;
 sbit SDA=0x80 + 1;



void DELAY(unsigned int t) 
{
        while(t!=0)
            t--;
}

void I2C_Start(void)
{
        SDA=1;
        SCL=1;
        DELAY(DELAY_TIME);
        SDA=0;
        DELAY(DELAY_TIME);
        SCL=0;
        DELAY(DELAY_TIME);
}

void I2C_Stop(void)
{
        SDA=0;
        SCL=1;
        DELAY(DELAY_TIME);
        SDA=1;
        DELAY(DELAY_TIME);
        SCL=0;
        DELAY(DELAY_TIME);
}

void SEND_0(void) 
{
        SDA=0;
        SCL=1;
        DELAY(DELAY_TIME);
        SCL=0;
        DELAY(DELAY_TIME);
}

void SEND_1(void)
{

        SDA=1;
        SCL=1;
        DELAY(DELAY_TIME);
        SCL=0;
        DELAY(DELAY_TIME);
}

bit Check_Acknowledge(void)
{
        /*?????????????????*/
        SDA=1;
        SCL=1;
        DELAY(DELAY_TIME/2);
        F0=SDA;
        DELAY(DELAY_TIME/2);
        SCL=0;
        DELAY(DELAY_TIME);
        if(F0==1)
            return FALSE;
        return TRUE;
}

bit Check_NAcknowledge(void)
{
        /*?????????????????*/
        SDA=1;
        SCL=1;
        DELAY(DELAY_TIME/2);
        F0=SDA;
        DELAY(DELAY_TIME/2);
        SCL=0;
        DELAY(DELAY_TIME);
        if(F0==1)
            return TRUE;
        return FALSE;
}


unsigned char ProbeSlaveAddr(void)
{
	unsigned char i = 0;
	bit ack;
  for (i = 0; i < 255; i++)
  {

    I2C_Start();
		WriteI2CByte(i);
    ack = Check_Acknowledge();
		I2C_Stop();
    if (ack == TRUE) {
			return i;
    }
  }
}



void WriteI2CByte(char b)reentrant
{
        char i;
        for(i=0;i<8;i++)
            if((b<<i)&0x80)
                SEND_1();
            else
                SEND_0();
}

 

char ReadI2CByte(void)reentrant
{
        char b=0,i;
        for(i=0;i<8;i++)
        {
            SDA=1;
            SCL=1;
            DELAY(10);
            F0=SDA;
            DELAY(10);
            SCL=0;
            if(F0==1)
                {
                    b=b<<1;
                    b=b|0x01;
                }
            else
                b=b<<1;
        }
        return b;
} 



void Write_One_Byte(unsigned char addr, unsigned char reg, unsigned char thedata)
{
          bit acktemp=1;
          I2C_Start();
          WriteI2CByte(addr);
          acktemp=Check_Acknowledge();
          WriteI2CByte(reg);/*address*/
          acktemp=Check_Acknowledge();
          WriteI2CByte(thedata);/*thedata*/
          acktemp=Check_Acknowledge();
          I2C_Stop();
}



unsigned char Read_One_Byte(unsigned char addr, unsigned char reg)
{         bit acktemp=1;
          unsigned char mydata;
           /*read a byte from mem*/
          I2C_Start();
          WriteI2CByte(addr);/*address*/
          acktemp=Check_Acknowledge();

          WriteI2CByte(reg);
          acktemp=Check_Acknowledge();
	        I2C_Stop();
	
	        I2C_Start();
	        WriteI2CByte(addr);/*address*/
          acktemp=Check_Acknowledge();
	
          mydata=ReadI2CByte();
          acktemp=Check_NAcknowledge();
	        I2C_Stop();
          return mydata;
}

