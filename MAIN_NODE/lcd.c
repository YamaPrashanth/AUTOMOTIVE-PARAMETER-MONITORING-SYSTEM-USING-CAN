#include "headers.h"

#define LCD_DAT 8
#define RS 17
#define RW 19
#define EN 18

/*------------------------------------------------------------
Function : LCD_Init
Purpose  : Initialize LCD in 8-bit mode with required configuration
------------------------------------------------------------*/
void LCD_Init(void)
{
        WRITEBYTE(IODIR0,LCD_DAT,0xFF);   // Configure LCD data pins as output
        WRITEBIT(IODIR0,RS,1);            // Configure RS pin as output
        WRITEBIT(IODIR0,RW,1);            // Configure RW pin as output
        WRITEBIT(IODIR0,EN,1);            // Configure EN pin as output

        delay_ms(16);                     // Initial power-on delay

        Write_CMD_LCD(0x30);              // Wake-up command
        delay_ms(6);

        Write_CMD_LCD(0x30);              // Wake-up command repeated
        delay_ms(1);

        Write_CMD_LCD(0x30);              // Wake-up command repeated
        delay_ms(1);

        Write_CMD_LCD(0x38);              // Set 8-bit mode, 2-line display, 5x7 font
        Write_CMD_LCD(0x10);              // Turn OFF display
        Write_CMD_LCD(0x01);              // Clear LCD display
        Write_CMD_LCD(0x06);              // Auto increment cursor position
        //Write_CMD_LCD(0x0f);            // Enable display with blinking cursor
        Write_CMD_LCD(0x0c);              // Enable display, cursor OFF
}

/*------------------------------------------------------------
Function : Write_CMD_LCD
Purpose  : Send command byte to LCD
------------------------------------------------------------*/
void Write_CMD_LCD(char cmd)
{
        WRITEBIT(IOCLR0,RS,1);            // Select command register
        Write_LCD(cmd);                   // Send command to LCD
}

/*------------------------------------------------------------
Function : Write_DAT_LCD
Purpose  : Send data byte/character to LCD
------------------------------------------------------------*/
void Write_DAT_LCD(char dat)
{
        WRITEBIT(IOSET0,RS,1);            // Select data register
        Write_LCD(dat);                   // Send data to LCD
}

/*------------------------------------------------------------
Function : Write_LCD
Purpose  : Write a byte to LCD with enable pulse
------------------------------------------------------------*/
void Write_LCD(char ch)
{
        WRITEBIT(IOCLR0,RW,1);            // Select write operation
        WRITEBYTE(IOPIN0,LCD_DAT,ch);     // Place data on LCD data pins

        WRITEBIT(IOSET0,EN,1);            // Generate enable HIGH pulse
        WRITEBIT(IOCLR0,EN,1);            // Generate enable LOW pulse

        delay_ms(2);                      // Wait for LCD execution time
}

/*------------------------------------------------------------
Function : Write_str_LCD
Purpose  : Display string on LCD
------------------------------------------------------------*/
void Write_str_LCD(char *p)
{
        while(*p)
                Write_DAT_LCD(*p++);      // Send characters one by one
}

/*------------------------------------------------------------
Function : Write_int_LCD
Purpose  : Display signed integer value on LCD
------------------------------------------------------------*/
void Write_int_LCD(signed int n)
{
        char a[10],i=0;

        if(n<0)
        {
                Write_DAT_LCD('-');       // Display negative sign
                n=-n;
        }

        do
        {
                a[i++]=n%10+48;           // Convert digit to ASCII
                n=n/10;
        }while(n);

        for(;i>0;i--)
                Write_DAT_LCD(a[i-1]);   // Display digits in correct order
}

/*------------------------------------------------------------
Function : Write_float_LCD
Purpose  : Display floating-point value on LCD
------------------------------------------------------------*/
//1st arg(f) is the float number to be displayed on LCD
//2nd arg(i) is number of digits to be displayed after decimal point
void Write_float_LCD(float f,char i)
{
        unsigned long int n=f;

        Write_int_LCD(n);                 // Display integer part
        Write_DAT_LCD('.');               // Display decimal point

        for(;i>0;i--)
        {
                f=f*10;
                n=f;
                Write_DAT_LCD(n%10+48);  // Display fractional digits
        }
}

/*------------------------------------------------------------
Function : Degree
Purpose  : Create custom degree symbol in LCD CGRAM
------------------------------------------------------------*/
void Degree(void)
{
        u8 i,LUT[]={0x07,0x09,0x07,0x00,0x00,0x00,0x00,0x00};

        for(i=0;i<8;i++)
                Write_DAT_LCD(LUT[i]);    // Store degree symbol pattern
}

/*------------------------------------------------------------
Function : FuelBar_
Purpose  : Create custom fuel bar characters in LCD CGRAM
------------------------------------------------------------*/
void FuelBar_(void)
{
        u8 i;

        u8 empty[8] = {0x1f,0x11,0x11,0x11,0x11,0x11,0x1f,0x00};
        u8 half[8]  = {0x1f,0x11,0x11,0x11,0x1f,0x1f,0x1f,0x00};
        u8 full[8]  = {0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x00};

        Write_CMD_LCD(0x40);              // Set CGRAM start address

        // Store EMPTY fuel bar at location 0
        for(i=0;i<8;i++)
                Write_DAT_LCD(empty[i]);

        // Store HALF fuel bar at location 1
        for(i=0;i<8;i++)
                Write_DAT_LCD(half[i]);

        // Store FULL fuel bar at location 2
        for(i=0;i<8;i++)
                Write_DAT_LCD(full[i]);
}

/*------------------------------------------------------------
Function : FuelBar
Purpose  : Display fuel level using custom bar characters
------------------------------------------------------------*/
void FuelBar(u8 fuel)
{
        u8 blocks = fuel / 20;            // Calculate full blocks
        u8 rem    = fuel % 20;            // Remaining percentage
        u8 i;

        // Display FULL blocks
        for(i=0;i<blocks;i++)
                Write_DAT_LCD(2);

        // Display HALF block if needed
        if(rem >= 10)
        {
                Write_DAT_LCD(1);
                blocks++;
        }

        // Display EMPTY blocks
        for(i=blocks;i<5;i++)
                Write_DAT_LCD(0);
}

/*------------------------------------------------------------
Function : LI
Purpose  : Create/display custom left indicator symbol
------------------------------------------------------------*/
void LI(void)
{
        u8 j,LUT1[]={0x03,0x07,0x0F,0x1F,0x0F,0x07,0x03};

        for(j=0;j<8;j++)
                Write_DAT_LCD(LUT1[j]);   // Store left arrow pattern
}

/*------------------------------------------------------------
Function : RI
Purpose  : Create/display custom right indicator symbol
------------------------------------------------------------*/
void RI(void)
{
        u8 k,LUT2[]={0x18,0x1C,0x1E,0x1F,0x1E,0x1C,0x18};

        for(k=0;k<8;k++)
                Write_DAT_LCD(LUT2[k]);   // Store right arrow pattern
}
