#ifndef __LCD_H__

#define __LCD_H__

#include "types.h"

void writelcd(u8 dat);
void cmdlcd(u8 cmd);
void charlcd(u8 asciival);
void initlcd(void);
void strlcd(s8 *);
void u32lcd(u32);
void s32lcd(s32);
void f32lcd(f32,u8);
void binlcd(u32,u8);
void hexlcd(u32);
void octlcd(u32);

#endif
