#include <LPC21xx.H>  /* LPC21xx definitions */
#include <string.h>
#include "delay.h"
#include "defines.h"
#include "uart.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "rtc.h"
#include "i2c.h"
#include "ext_int.h"
#include "i2c_eeprom.h"
#include"keypad.h"
//#define SW 6
#define CFGPIN(WORD,PIN,FUNC)\
                (WORD=(PIN<16)?\
                ((WORD&~(3<<(PIN*2))) | (FUNC<<(PIN*2))):\
                ((WORD&~(3<<((PIN-16)*2))) | (FUNC<<((PIN-16)*2))))

#define UART_INT_ENABLE 1

typedef struct
{
char id[10];
char name[20];
}RFID;

void init(RFID *cards)
{
strcpy(cards[0].id,"00326553");
strcpy(cards[0].name,"mani");

strcpy(cards[1].id,"12534588");
strcpy(cards[1].name,"raji");

strcpy(cards[2].id,"12531606");
strcpy(cards[2].name,"naveen");
} 

char buff[11],dummy;
unsigned char i = 0,j , ch, r_flag;

void UART0_isr(void) __irq
{
        if ((U0IIR & 0x04)) // Check if receive interrupt
        {
                ch = U0RBR;  /* Read to Clear Receive Interrupt */
                if (ch != 0x03)
                {
                        buff[i++] = ch;
                }
                else
                {
                        buff[i] = '\0';
                        i = 0;
                        r_flag = 1;
                }
        }
        else
{
                dummy = U0IIR; // Read to Clear transmit interrupt
        }
        VICVectAddr = 0; /* Dummy write */
}

void InitUART0_int(void) /* Initialize Serial Interface */
{
        CFGPIN(PINSEL0,0,1);
        CFGPIN(PINSEL0,1,1); /* Enable RxD0 and TxD0 */
        U0LCR = 0x83;         /* 8 bits, no Parity, 1 Stop bit */
        U0DLL = 97;           /* 9600 Baud Rate @ CCLK/4 VPB Clock */
        U0LCR = 0x03;         /* DLAB = 0 */

#if UART_INT_ENABLE > 0
        VICIntSelect = 0x00000000; // IRQ
        VICVectAddr0 = (unsigned)UART0_isr;
        VICVectCntl0 = 0x20 | 6; /* UART0 Interrupt */
        VICIntEnable = 1 << 6;   /* Enable UART0 Interrupt */
        U0IER = 0x03;       /* Enable UART0 RX and THRE Interrupts */
#endif
}

int main()
{		  
        char rdat;
    	int flag;
        RFID cards[3];
        init(cards);
        InitUART0_int();
        rtc_init();
        init_i2c();
		initlcd();
		initkpm();
		strlcd("waiting for input");
	for(j=0;j<3;j++)
	{
		i2c_eeprom_write(0x50,0+j,'$');
	} 
        while(1)
        {
		i=0;r_flag=0,flag=0;
		Enable_eint0();
		while(r_flag == 0);
                for(j=0;j<3;j++)
                {
                        if(strstr(buff,cards[j].id))
                        {
			    cmdlcd(0x01);
				//UART0_Str("VALID");
				//UART0_Str("\r\n");
				cmdlcd(GOTO_LINE1_POS0);
				strlcd("VALID");
				flag=1;
                                rdat=i2c_eeprom_read(0x50,j);
                                if(rdat=='$')
				{
					rdat='0';
				}
                                if(rdat=='0')
                                {
                                        i2c_eeprom_write(0x50,j,'1');
                                        
					UART0_Str(cards[j].name);
					UART0_Tx(',');
					UART0_Tx('"');
					UART0_Str(cards[j].id);
					UART0_Tx('"');
					UART0_Tx(',');
					UART0_Str("IN");
					UART0_Tx(',');
					rtc_uart();
				//	UART0_Tx(',');
					UART0_Str("\r\n");

					cmdlcd(CLEAR_LCD);
					cmdlcd(GOTO_LINE1_POS0);
					strlcd(cards[j].name);
					charlcd(':');
					strlcd(cards[j].id);
					cmdlcd(GOTO_LINE2_POS0);
					strlcd("IN");
					cmdlcd(GOTO_LINE3_POS0);
					rtc_lcd();
					delay_ms(500);
				}
				if(rdat=='1')
				{
					i2c_eeprom_write(0x50,j,'0');

					UART0_Str(cards[j].name);
					UART0_Tx(',');
					UART0_Tx('"');
					UART0_Str(cards[j].id);
					UART0_Tx('"');
					UART0_Tx(',');
					UART0_Str("OUT");
					UART0_Tx(',');
					rtc_uart();
					UART0_Str("\r\n");
					//strlcd("\r\n");
					cmdlcd(CLEAR_LCD);
					cmdlcd(GOTO_LINE1_POS0);
             		strlcd(cards[j].name);
					charlcd(':');
					strlcd(cards[j].id);
					cmdlcd(GOTO_LINE2_POS0);
					strlcd("OUT");
					cmdlcd(GOTO_LINE3_POS0);
					rtc_lcd();
					delay_ms(500);
				}
			}
		}
		if(flag==0)
		{
			cmdlcd(CLEAR_LCD);
			strlcd("INVALID");
			delay_ms(500);
			cmdlcd(CLEAR_LCD);
		} 
	}
}
  




/*
int main()
{

char key;
initkpm();
initlcd();
while(1)
{
key=keyscan()+48;
charlcd(key);
 }
 }

*/
