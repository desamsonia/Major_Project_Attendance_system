#ifndef __KEYPAD_H__
#define __KEYPAD_H__

#include "types.h"

void initkpm(void);
u32 colscan(void);
u32 rowcheck(void);
u32 colcheck(void);
u32 keyscan(void);

#endif
