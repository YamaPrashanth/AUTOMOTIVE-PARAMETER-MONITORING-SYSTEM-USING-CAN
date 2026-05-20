#include <LPC21xx.h>

#include "types.h"
#include "defines.h"
#include "delay.h"

#include "pin_function_defines.h"

#define PCLK       60000000  //Hz

//adc P0.16 to adc for fuel gauge
void Init_ADC(void);
f32 Read_ADC(u8 chNo);

//lcd
void Write_CMD_LCD(char);
void Write_DAT_LCD(char);
void Write_LCD(char);
void LCD_Init(void);
void Write_str_LCD(char *);
void Write_int_LCD(signed int);//signed int(2 byte)-> -32768 to 32767
void Write_float_LCD(float f,char );
void Degree(void);
void LI(void);
void RI(void);
void FuelBar_(void);
void FuelBar(u8);

//DS18B20  P0.16 as data pin
/**DS18B20 FUNCTION DECLARATION**/
unsigned char ResetDS18b20(void);
unsigned char ReadBit(void);
void WriteBit(unsigned char);
unsigned char ReadByte(void);
void WriteByte(unsigned char);
int ReadTemp(void);

//External Interrupts
void eint0_isr(void) __irq;
void eint1_isr(void) __irq;
void Enable_EINT0(void);
void Enable_EINT1(void);
