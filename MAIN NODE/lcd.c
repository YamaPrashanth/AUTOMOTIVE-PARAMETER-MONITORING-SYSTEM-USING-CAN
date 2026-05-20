#include "headers.h"

#define LCD_DAT 8
#define RS 17
#define RW 19
#define EN 18

void LCD_Init(void)
{
        WRITEBYTE(IODIR0,LCD_DAT,0xFF);
        WRITEBIT(IODIR0,RS,1);
        WRITEBIT(IODIR0,RW,1);
        WRITEBIT(IODIR0,EN,1);
        delay_ms(16);
    Write_CMD_LCD(0x30);
    delay_ms(6);
        Write_CMD_LCD(0x30);
    delay_ms(1);
    Write_CMD_LCD(0x30);
    delay_ms(1);
    Write_CMD_LCD(0x38);//set 8-bit mode of operation with 2 lines
                                                // and 5X7 character font
        Write_CMD_LCD(0x10);//Turning OFF the display
        Write_CMD_LCD(0x01);//clearing the display
    Write_CMD_LCD(0x06);//Shifting the cursor to the right side
                        //after writing each byte onto the display
        //Write_CMD_LCD(0x0f);//Enabling the display with blinking cursor^M
        Write_CMD_LCD(0x0c);//Enabling the display with blinking& cursor off
}

void Write_CMD_LCD(char cmd)
{
    WRITEBIT(IOCLR0,RS,1);
    Write_LCD(cmd);
}

void Write_DAT_LCD(char dat)
{
        WRITEBIT(IOSET0,RS,1);
        Write_LCD(dat);
}

void Write_LCD(char ch)
{
        WRITEBIT(IOCLR0,RW,1);
        WRITEBYTE(IOPIN0,LCD_DAT,ch);
        WRITEBIT(IOSET0,EN,1);
        WRITEBIT(IOCLR0,EN,1);
        delay_ms(2);
}

void Write_str_LCD(char *p)
{
        while(*p)
                Write_DAT_LCD(*p++);
}

void Write_int_LCD(signed int n)
{
        char a[10],i=0;
    if(n<0)
        {
                Write_DAT_LCD('-');
                n=-n;
        }
        do
        {
                a[i++]=n%10+48;
                n=n/10;
        }while(n);
  for(;i>0;i--)
                Write_DAT_LCD(a[i-1]);
}

void Write_float_LCD(float f,char i)
//1st arg(f) is the float number to be displayed  on LCD
//2nd arg(i) is number digits to be displayed after the dot('.')
{
  unsigned long int n=f;
        Write_int_LCD(n);
        Write_DAT_LCD('.');
  for(;i>0;i--)
        {
                f=f*10;
    n=f;
                Write_DAT_LCD(n%10+48);
        }
}

//degree symbol
void Degree(void)
{
        u8 i,LUT[]={0x07,0x09,0x07,0x00,0x00,0x00,0x00,0x00};
        for(i=0;i<8;i++)
                Write_DAT_LCD(LUT[i]);
}

//FuelBar
void FuelBar_(void)
{
    u8 i;

    u8 empty[8] = {0x1f,0x11,0x11,0x11,0x11,0x11,0x1f,0x00};
    u8 half[8]  = {0x1f,0x11,0x11,0x11,0x1f,0x1f,0x1f,0x00};
    u8 full[8]  = {0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x00};

    // CGRAM start location
    Write_CMD_LCD(0x40);

    // Store EMPTY at location 0
    for(i=0;i<8;i++) Write_DAT_LCD(empty[i]);

    // Store HALF at location 1
    for(i=0;i<8;i++) Write_DAT_LCD(half[i]);

    // Store FULL at location 2
    for(i=0;i<8;i++) Write_DAT_LCD(full[i]);
}
void FuelBar(u8 fuel)
{
    u8 blocks = fuel / 20;     // full blocks
    u8 rem    = fuel % 20;     // remaining
    u8 i;

    // Print FULL blocks
    for(i=0;i<blocks;i++)
        Write_DAT_LCD(2);

    // Print HALF block
    if(rem >= 10)
    {
        Write_DAT_LCD(1);
        blocks++;
    }

    // Print EMPTY blocks
    for(i=blocks;i<5;i++)
        Write_DAT_LCD(0);
}


//Left Indicator
void LI(void)
{
        u8 j,LUT1[]={0x03,0x07,0x0F,0x1F,0x0F,0x07,0x03};
        for(j=0;j<8;j++)
          Write_DAT_LCD(LUT1[j]);
}

//Right Indicator
void RI(void)
{
        u8 k,LUT2[]={0x18,0x1C,0x1E,0x1F,0x0E,0x1C,0x18};
        for(k=0;k<8;k++)
          Write_DAT_LCD(LUT2[k]);
}
