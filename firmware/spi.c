 #include <string.h>
 #include <reg52.h>
 #include <intrins.h>
 
 #include "spi.h"
 
 
 sbit CS=0x80 + 0;
 sbit MOSI=0x80 + 1;
 sbit MISO=0x80 + 0;
 sbit DC=0x80 + 1;
 sbit RST=0x80 + 1;