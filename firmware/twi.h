#ifndef __TWI_H_
#define __TWI_H_



void I2C_Init();
unsigned char ProbeSlaveAddr(void);
void WriteI2CByte(char b)reentrant;
char ReadI2CByte(void)reentrant;

unsigned char Read_One_Byte(unsigned char addr, unsigned char reg);
void Write_One_Byte( char addr, char reg, char thedata);

#endif

