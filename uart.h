#ifndef __UART_H__
#define __UART_H__

void InitUART0 (void);
void UART0_Tx(char ch);
char UART0_Rx(void);
void UART0_Str(char *s);
void UART0_Int(unsigned int n);
void UART0_Float(float f);

#endif
