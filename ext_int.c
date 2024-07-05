#include<LPC21XX.H>
#include<stdlib.h>
#include "delay.h"
#include "defines.h"
#include "types.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "keypad.h"
//#define SW 6
#define CFGPIN(WORD,PIN,FUNC)\
        (WORD=((PIN<16)?((WORD&~(3<<(PIN*2)))|(FUNC<<(PIN*2))):\
		      ((WORD&~(3<<((PIN-16)*2)))|(FUNC<<((PIN-16)*2)))))
int edit(void)
{
int i=0,p;
while(1)
{
p=keyscan();
while(colscan()==0);
delay_ms(100);
if(p<=9)
{
i=i*10+p;
}
else
{
break;
}
}
u32lcd(i);
return i;
}
void eint0_isr(void)__irq
{
int ch,n;
cmdlcd(CLEAR_LCD);
cmdlcd(GOTO_LINE1_POS0);
strlcd("1.HOUR 2.MIN 3.SEC");
cmdlcd(GOTO_LINE2_POS0);
strlcd("4.DOM 5.MON 6.YEAR");  
cmdlcd(GOTO_LINE3_POS0);
strlcd("enter your choice:");
ch=keyscan();
u32lcd(ch);
while(colscan()==0);
delay_ms(1000);
cmdlcd(CLEAR_LCD);

switch(ch)
{
case 1:strlcd("HOUR:");
	   n=edit();
	   if(n>=0 && n<=23)
	   		HOUR=n;
	   else
	   	  	strlcd("invalid");
	   while(colscan()==0);
	   break;
case 2:strlcd("MIN:");
	   n=edit();
	   if(n>=0 && n<=59)
	   		MIN=n;
	   else
	   		strlcd("invalid");
	   while(colscan()==0);
	   break;
case 3:strlcd("SEC:");
	   n=edit();
	   if(n>=0 && n<=59)
	   		SEC=n;
	   else
	   		strlcd("invalid");
	   while(colscan()==0);
	   break;
case 4:strlcd("DOM:");
	   n=edit();
	   if(n>=0 && n<=31)
	   		DOM=n;
	   else
	   		strlcd("invalid");
	   while(colscan()==0);
	   break;
case 5:strlcd("MONTH:");
	   n=edit();
	   if(n>=1 && n<=12)
	   		MONTH=n;
	   else
	   		strlcd("invalid");
	   while(colscan()==0);
	   break;
case 6:strlcd("YEAR:");
	   n=edit();
	   if(n>=0 && n<=4095)
	   		YEAR=n;
	   else
	   		strlcd("invalid");
	   while(colscan()==0);
	   break;
}

EXTINT=1<<2;
VICVectAddr=0;
} 
void Enable_eint0(void)
{
CFGPIN(PINSEL0,7,3);
//VICIntSelect=0;
VICIntEnable=1<<16;
VICVectCntl1=0x20|16;
VICVectAddr1=(u32)eint0_isr;
EXTINT=1<<2;
EXTMODE=1<<2;
//EXTPOLAR=0;
}


