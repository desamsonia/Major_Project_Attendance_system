#include <LPC21XX.H>
#include "types.h"
#include "defines.h"
#include "kpm_defines.h"

u32 KPMLUT[4][4]={{1,2,3,'a'},{4,5,6,'b'},{7,8,9,'c'},{'*','0','#','d'}};

void initkpm(void)
{
WRITENIBBLE(IODIR1,ROW0,15);
}

u32 colscan(void)
{
return(READNIBBLE(IOPIN1,COL0)==15)?1:0;
}

u32 rowcheck(void)
{
u32 r;
for(r=0;r<4;r++)
{
WRITENIBBLE(IOPIN1,ROW0,~(1<<r));
if(colscan()==0)
break;
}
WRITENIBBLE(IOPIN1,ROW0,0);
return r;
}

u32 colcheck(void)
{
u32 c;
for(c=0;c<4;c++)
{
if(READBIT(IOPIN1,COL0+c)==0)
break;
}
return c;
}

u32 keyscan(void)
{
u32 keyv,r,c;
while(colscan()==1);
r=rowcheck();
c=colcheck();
keyv=KPMLUT[r][c];
return keyv;
}
