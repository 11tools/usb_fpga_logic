//-----------------------------------------------------------------------------
//   File:      bulkloop.c
//   Contents:  Hooks required to implement USB peripheral function.
//
// $Archive: /USB/Examples/FX2LP/bulkloop/bulkloop.c $
// $Date: 3/23/05 2:55p $
// $Revision: 4 $
//
//
//-----------------------------------------------------------------------------
// Copyright 2003, Cypress Semiconductor Corporation
//-----------------------------------------------------------------------------
#pragma NOIV               // Do not generate interrupt vectors

#include "fx2.h"
#include "fx2regs.h"
#include "syncdly.h"            // SYNCDELAY macro
#include "twi.h"

extern BOOL GotSUD;             // Received setup data flag
extern BOOL Sleep;
extern BOOL Rwuen;
extern BOOL Selfpwr;

BYTE Configuration;             // Current configuration
BYTE AlternateSetting;          // Alternate settings

#define VR_NAKALL_ON    0xD0
#define VR_NAKALL_OFF   0xD1

//-----------------------------------------------------------------------------
// Task Dispatcher hooks
//   The following hooks are called by the task dispatcher.
//-----------------------------------------------------------------------------

sbit led = IOA^3;



void TD_Init(void)             // Called once at startup
{
   // set the CPU clock to 48MHz
   CPUCS = ((CPUCS & ~bmCLKSPD) | bmCLKSPD1) ;

   // Set Slave sync FIFO mode  
   //IFCONFIG |=  0x43;           

  // Registers which require a synchronization delay, see section 15.14
  // FIFORESET        FIFOPINPOLAR
  // INPKTEND         OUTPKTEND
  // EPxBCH:L         REVCTL
  // GPIFTCB3         GPIFTCB2
  // GPIFTCB1         GPIFTCB0
  // EPxFIFOPFH:L     EPxAUTOINLENH:L
  // EPxFIFOCFG       EPxGPIFFLGSEL
  // PINFLAGSxx       EPxFIFOIRQ
  // EPxFIFOIE        GPIFIRQ
  // GPIFIE           GPIFADRH:L
  // UDMACRCH:L       EPxGPIFTRIG
  // GPIFTRIG
  
  // Note: The pre-REVE EPxGPIFTCH/L register are affected, as well...
  //      ...these have been replaced by GPIFTC[B3:B0] registers

	IFCONFIG =0x43;//那1車?赤a2?那㊣?車㏒?IFCLK那?豕?2?﹞∩?辰
	
	SYNCDELAY;
	EP2CFG=0xA0; //D豕辰a谷豕?“?a???o3?㏒??????o3???∩車D??a512℅??迆
	SYNCDELAY;
	EP4CFG=0x00;
	SYNCDELAY;
	EP6CFG=0xE0;
	SYNCDELAY;
	EP8CFG=0x00;
	
	SYNCDELAY;
	FIFORESET = 0x80;             // activate NAK-ALL to avoid race conditions
	SYNCDELAY;                    // see TRM section 15.14
	FIFORESET = 0x02;             // reset, FIFO 2
	SYNCDELAY;                    // 
	FIFORESET = 0x06;             // reset, FIFO 6
	SYNCDELAY;                    // 
	FIFORESET = 0x00;             // deactivate NAK-ALL
	
	SYNCDELAY;
	PINFLAGSAB = 0xE6;          // FLAGA - fixed EP6PF, FLAGB - fixed EP6FF
	SYNCDELAY;
	PINFLAGSCD = 0xDE;          // FLAGC - fixed EP2EF, FLAGD - reserved
	SYNCDELAY;
	PORTACFG |=  0x00;  //0x40;             // SLCS, set alt. func. of PA7 pin
	SYNCDELAY;
	FIFOPINPOLAR = 0x00;          // all signals active low㏒?
	SYNCDELAY;

	 OEA|=0x0F;
    //D?車迆64℅??迆車DD∫
    //EP6FIFOPFH=0x00; //DEIS PKSTAT  PK2 PK1 PK0 0 PFC9 PFC8
    //EP6FIFOPFL=0x40; //PFC7 PFC6 PFC5 PFC4 PFC3 PFC2 PFC1 PFC0
	
	// handle the case where we were already in AUTO mode...
	EP2FIFOCFG = 0x01;            // AUTOOUT=0, WORDWIDE=1
	SYNCDELAY;
	
	EP2FIFOCFG = 0x11;            // AUTOOUT=1, WORDWIDE=1
	SYNCDELAY;
	
	
	EP6FIFOCFG = 0x09;            // AUTOIN=1, ZEROLENIN=0, WORDWIDE=1
	SYNCDELAY;

	//IO谷豕??
	PORTCCFG=0x00;
	PORTECFG=0x00;
	OEC=0x00;
	OEE=0xff;

	PA0=1;

  

}





void TD_Poll(void)              // Called repeatedly while the device is idle
{
	
	   int i;

/*   // if there is some data in EP2 OUT, re-arm it
   if(!(EP2468STAT & bmEP2EMPTY))
   {
      SYNCDELAY;                // 
      EP2BCL = 0x80;
   }

   // if EP6 IN is available, re-arm it
   if(!(EP2468STAT & bmEP6FULL))
   {
      SYNCDELAY;                // 
      EP6BCH = 0x02;
      SYNCDELAY;                // 
      EP6BCL = 0x00;
   }
*/

}

BOOL TD_Suspend(void)          // Called before the device goes into suspend mode
{
   return(TRUE);
}

BOOL TD_Resume(void)          // Called after the device resumes
{
   return(TRUE);
}

//-----------------------------------------------------------------------------
// Device Request hooks
//   The following hooks are called by the end point 0 device request parser.
//-----------------------------------------------------------------------------

BOOL DR_GetDescriptor(void)
{
   return(TRUE);
}

BOOL DR_SetConfiguration(void)   // Called when a Set Configuration command is received
{
   Configuration = SETUPDAT[2];
   return(TRUE);            // Handled by user code
}

BOOL DR_GetConfiguration(void)   // Called when a Get Configuration command is received
{
   EP0BUF[0] = Configuration;
   EP0BCH = 0;
   EP0BCL = 1;
   return(TRUE);            // Handled by user code
}

BOOL DR_SetInterface(void)       // Called when a Set Interface command is received
{
   AlternateSetting = SETUPDAT[2];
   return(TRUE);            // Handled by user code
}

BOOL DR_GetInterface(void)       // Called when a Set Interface command is received
{
   EP0BUF[0] = AlternateSetting;
   EP0BCH = 0;
   EP0BCL = 1;
   return(TRUE);            // Handled by user code
}

BOOL DR_GetStatus(void)
{
   return(TRUE);
}

BOOL DR_ClearFeature(void)
{
   return(TRUE);
}

BOOL DR_SetFeature(void)
{
   return(TRUE);
}

BOOL DR_VendorCmnd(void)
{
  BYTE tmp;
  
  switch (SETUPDAT[1])
  {
     case VR_NAKALL_ON:
        tmp = FIFORESET;
        tmp |= bmNAKALL;      
        SYNCDELAY;                    
        FIFORESET = tmp;
        break;
     case VR_NAKALL_OFF:
        tmp = FIFORESET;
        tmp &= ~bmNAKALL;      
        SYNCDELAY;                    
        FIFORESET = tmp;
        break;
     default:
        return(TRUE);
  }

  return(FALSE);
}

//-----------------------------------------------------------------------------
// USB Interrupt Handlers
//   The following functions are called by the USB interrupt jump table.
//-----------------------------------------------------------------------------

// Setup Data Available Interrupt Handler
void ISR_Sudav(void) interrupt 0
{
   GotSUD = TRUE;            // Set flag
   EZUSB_IRQ_CLEAR();
   USBIRQ = bmSUDAV;         // Clear SUDAV IRQ
}

// Setup Token Interrupt Handler
void ISR_Sutok(void) interrupt 0
{
   EZUSB_IRQ_CLEAR();
   USBIRQ = bmSUTOK;         // Clear SUTOK IRQ
}

void ISR_Sof(void) interrupt 0
{
   EZUSB_IRQ_CLEAR();
   USBIRQ = bmSOF;            // Clear SOF IRQ
}

void ISR_Ures(void) interrupt 0
{
   // whenever we get a USB reset, we should revert to full speed mode
   pConfigDscr = pFullSpeedConfigDscr;
   ((CONFIGDSCR xdata *) pConfigDscr)->type = CONFIG_DSCR;
   pOtherConfigDscr = pHighSpeedConfigDscr;
   ((CONFIGDSCR xdata *) pOtherConfigDscr)->type = OTHERSPEED_DSCR;

   EZUSB_IRQ_CLEAR();
   USBIRQ = bmURES;         // Clear URES IRQ
}

void ISR_Susp(void) interrupt 0
{
   Sleep = TRUE;
   EZUSB_IRQ_CLEAR();
   USBIRQ = bmSUSP;
}

void ISR_Highspeed(void) interrupt 0
{
   if (EZUSB_HIGHSPEED())
   {
      pConfigDscr = pHighSpeedConfigDscr;
      ((CONFIGDSCR xdata *) pConfigDscr)->type = CONFIG_DSCR;
      pOtherConfigDscr = pFullSpeedConfigDscr;
      ((CONFIGDSCR xdata *) pOtherConfigDscr)->type = OTHERSPEED_DSCR;
   }

   EZUSB_IRQ_CLEAR();
   USBIRQ = bmHSGRANT;
}
void ISR_Ep0ack(void) interrupt 0
{
}
void ISR_Stub(void) interrupt 0
{
}
void ISR_Ep0in(void) interrupt 0
{
}
void ISR_Ep0out(void) interrupt 0
{
}
void ISR_Ep1in(void) interrupt 0
{
}
void ISR_Ep1out(void) interrupt 0
{
}
void ISR_Ep2inout(void) interrupt 0
{
}
void ISR_Ep4inout(void) interrupt 0
{
}
void ISR_Ep6inout(void) interrupt 0
{
}
void ISR_Ep8inout(void) interrupt 0
{
}
void ISR_Ibn(void) interrupt 0
{
}
void ISR_Ep0pingnak(void) interrupt 0
{
}
void ISR_Ep1pingnak(void) interrupt 0
{
}
void ISR_Ep2pingnak(void) interrupt 0
{
}
void ISR_Ep4pingnak(void) interrupt 0
{
}
void ISR_Ep6pingnak(void) interrupt 0
{
}
void ISR_Ep8pingnak(void) interrupt 0
{
}
void ISR_Errorlimit(void) interrupt 0
{
}
void ISR_Ep2piderror(void) interrupt 0
{
}
void ISR_Ep4piderror(void) interrupt 0
{
}
void ISR_Ep6piderror(void) interrupt 0
{
}
void ISR_Ep8piderror(void) interrupt 0
{
}
void ISR_Ep2pflag(void) interrupt 0
{
}
void ISR_Ep4pflag(void) interrupt 0
{
}
void ISR_Ep6pflag(void) interrupt 0
{
}
void ISR_Ep8pflag(void) interrupt 0
{
}
void ISR_Ep2eflag(void) interrupt 0
{
}
void ISR_Ep4eflag(void) interrupt 0
{
}
void ISR_Ep6eflag(void) interrupt 0
{
}
void ISR_Ep8eflag(void) interrupt 0
{
}
void ISR_Ep2fflag(void) interrupt 0
{
}
void ISR_Ep4fflag(void) interrupt 0
{
}
void ISR_Ep6fflag(void) interrupt 0
{
}
void ISR_Ep8fflag(void) interrupt 0
{
}
void ISR_GpifComplete(void) interrupt 0
{
}
void ISR_GpifWaveform(void) interrupt 0
{
}
