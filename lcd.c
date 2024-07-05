#include<LPC21XX.H>
#include "types.h"
#include "delay.h"
#include "defines.h"
#include "lcd_defines.h"

void writelcd(u8 dat)
{
WRITEBYTE(IOPIN0,LCD_DATA,dat);
IOSET0=1<<LCD_EN;
delay_us(1);
IOCLR0=1<<LCD_EN;
delay_ms(2);
}

void cmdlcd(u8 cmd)
{
IOCLR0=1<<LCD_RS;
writelcd(cmd);
}

void charlcd(u8 asciival)
{
IOSET0=1<<LCD_RS;
writelcd(asciival);
}

void initlcd(void)
{
IODIR0|=0XFF<<LCD_DATA|1<<LCD_RS|1<<LCD_RW|1<<LCD_EN;
delay_ms(15);
cmdlcd(0x30);
delay_ms(5);
cmdlcd(0x30);
delay_us(100);
cmdlcd(0x30);
cmdlcd(MODE_8BIT_2LINE);
cmdlcd(DSP_ON_CUR_ON);
cmdlcd(CLEAR_LCD);
cmdlcd(SHIFT_CUR_RIGHT);
}

void strlcd(s8 *p)
{
while(*p)
charlcd(*p++);
}

void u32lcd(u32 n)
{
s32 i=0;
u8 a[10];
if(n==0)
charlcd('0');
else
{
while(n>0)
{
a[i++]=(n%10)+48;
n/=10;
}
for(--i;i>=0;i--)
charlcd(a[i]);
}
}

void s32lcd(s32 n)
{
if(n<0)
{
charlcd('-');
n=-n;
}
u32lcd(n);
}

void f32lcd(f32 f,u8 ndp)
{
u32 n,i;
if(f<0.0)
{
charlcd('-');
f=-f;
}
n=f;
u32lcd(n);
charlcd('.');
for(i=0;i<ndp;i++)
{
f=(f-n)*10;
n=f;
charlcd(n+48);
}
}

void binlcd(u32 n,u8 nbd)
{
s32 i;
for(i=nbd;i>=0;i--)
{
charlcd(((n>>i)&1)+48);
}
}

void hexlcd(u32 n)
{
s32 i=0;
u8 a[8],t;
if(n==0)
charlcd('0');
else
{
while(n>0)
{
((t=(n%16))<10)?(t=t+48):(t=(t-10)+'A');
a[i++]=t;
n/=16;
}
for(--i;i>=0;i--)
charlcd(a[i]);
}
}

void octlcd(u32 n)
{
s32 i=0;
u8 a[12],t;
if(n==0)
charlcd('0');
else
{
while(n>0)
{
t=n%8+48;
a[i++]=t;
n/=8;
}
for(--i;i>=0;i--)
charlcd(a[i]);
}
}

void buildcgram(u8 *p,u8 nbytes)
{
u32 i;
cmdlcd(GOTO_CGRAM_START);
for(i=0;i<nbytes;i++)
{
charlcd(p[i]);
}
cmdlcd(GOTO_LINE1_POS0);
}
