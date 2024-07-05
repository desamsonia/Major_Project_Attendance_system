#include<LPC21XX.h>
#include "uart.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "delay.h"

#define FOSC      12000000

#define CCLK  	  5*FOSC

#define PCLK  	  CCLK/4

#define PREINT_VAL ((PCLK/32768)-1)

#define PREFRAC_VAL (PCLK - ((PREINT_VAL + 1) * 32768))

void rtc_lcd(void)
{
	u32lcd(HOUR/10);

    u32lcd(HOUR%10);

    charlcd(':');

    u32lcd(MIN/10);

    u32lcd(MIN%10);

    charlcd(':');

    u32lcd(SEC/10);

    u32lcd(SEC%10);


    cmdlcd(GOTO_LINE4_POS0);

	u32lcd(DOM/10);

    u32lcd(DOM%10);

    charlcd('/');

    u32lcd(MONTH/10);

    u32lcd(MONTH%10);

    charlcd('/');

    u32lcd(YEAR/10);

    u32lcd(YEAR%10);

	delay_ms(1000);

	cmdlcd(0x01);
}
void rtc_uart(void)
{
    UART0_Tx(HOUR/10+'0');

    UART0_Tx(HOUR%10+'0');

    UART0_Tx(':');

    UART0_Tx(MIN/10+'0');

    UART0_Tx(MIN%10+'0');

    UART0_Tx(':');

    UART0_Tx(SEC/10+'0');

    UART0_Tx(SEC%10+'0');

    UART0_Str(",");

		

	UART0_Tx(DOM/10+'0');

    UART0_Tx(DOM%10+'0');

    UART0_Tx('/');

    UART0_Tx(MONTH/10+'0');

    UART0_Tx(MONTH%10+'0');

    UART0_Tx('/');

    UART0_Tx(YEAR/10+'0');

    UART0_Tx(YEAR%10+'0');
}
void rtc_init()

{

  SEC=00; //Initialized seconds

  MIN=00; //Initialized minutes

  HOUR=8;//Initialized hour
  
  DOM=18;
  
  MONTH=05;
  
  YEAR=24;
  
  PREINT=PREINT_VAL;

  PREFRAC=PREFRAC_VAL;
  
  CCR=0x01; //timer started

}
