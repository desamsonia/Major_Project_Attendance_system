#define LCD_DATA 8 //p0.8 to p0.15
#define	LCD_RS 16  //p0.16
#define LCD_EN 17  //p0.17
#define LCD_RW 18  //p0.18

//HD44780 Commands

#define CLEAR_LCD         0X01
#define RET_CUR_HOME      0X02 
#define SHIFT_CUR_RIGHT	  0X06
#define SHIFT_CUR_LEFT    0X07
#define DSP_OFF           0X08
#define DSP_ON_CUR_OFF    0X0C
#define DSP_ON_CUR_ON     0X0E
#define	DSP_ON_CUR_BLINK  0X0F
#define	MODE_8BIT_1LINE   0X30
#define MODE_8BIT_2LINE   0X38
#define GOTO_LINE1_POS0   0X80
#define GOTO_LINE2_POS0   0Xc0
#define GOTO_LINE3_POS0   0X94
#define GOTO_LINE4_POS0   0Xd4
#define GOTO_CGRAM_START  0X40
