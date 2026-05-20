#include <LPC21xx.h>             // LPC21xx register definitions

#include "types.h"               // User-defined data types
#include "defines.h"             // General macro definitions
#include "delay.h"               // Delay function declarations

#include "pin_function_defines.h"// Pin function configuration macros
#include "adc_defines.h"         // ADC-related macro definitions

#define PCLK 60000000            // Peripheral Clock Frequency = 60MHz

/*------------------------------------------------------------
ADC Section
------------------------------------------------------------*/
// ADC channel connected to Fuel Gauge sensor (P0.28 / AD1.1)

// Function : Init_ADC
// Purpose  : Initialize ADC peripheral
void Init_ADC(void);

// Function : Read_ADC
// Purpose  : Read analog value from selected ADC channel
f32 Read_ADC(u8 chNo);


/*------------------------------------------------------------
LCD Section
------------------------------------------------------------*/

// Function : Write_CMD_LCD
// Purpose  : Send command byte to LCD
void Write_CMD_LCD(char);

// Function : Write_DAT_LCD
// Purpose  : Send data/character byte to LCD
void Write_DAT_LCD(char);

// Function : Write_LCD
// Purpose  : Write raw byte to LCD
void Write_LCD(char);

// Function : LCD_Init
// Purpose  : Initialize LCD module
void LCD_Init(void);

// Function : Write_str_LCD
// Purpose  : Display string on LCD
void Write_str_LCD(char *);

// Function : Write_int_LCD
// Purpose  : Display signed integer on LCD
// Range    : signed int (2 bytes) ? -32768 to 32767
void Write_int_LCD(signed int);

// Function : Write_float_LCD
// Purpose  : Display floating-point number on LCD
void Write_float_LCD(float f,char );

// Function : Degree
// Purpose  : Create/display degree symbol on LCD
void Degree(void);

// Function : LI
// Purpose  : Display Left Indicator symbol
void LI(void);

// Function : RI
// Purpose  : Display Right Indicator symbol
void RI(void);

// Function : FuelBar_
// Purpose  : Create custom fuel bar characters
void FuelBar_(void);

// Function : FuelBar
// Purpose  : Display fuel level bar graph
void FuelBar(u8);


/*------------------------------------------------------------
DS18B20 Temperature Sensor Section
------------------------------------------------------------*/
// DS18B20 data pin connected to P0.16

// Function : ResetDS18b20
// Purpose  : Send reset pulse and detect sensor presence
unsigned char ResetDS18b20(void);

// Function : ReadBit
// Purpose  : Read single bit from DS18B20
unsigned char ReadBit(void);

// Function : WriteBit
// Purpose  : Write single bit to DS18B20
void WriteBit(unsigned char);

// Function : ReadByte
// Purpose  : Read one byte from DS18B20
unsigned char ReadByte(void);

// Function : WriteByte
// Purpose  : Write one byte to DS18B20
void WriteByte(unsigned char);

// Function : ReadTemp
// Purpose  : Read temperature from DS18B20 sensor
int ReadTemp(void);


/*------------------------------------------------------------
External Interrupt Section
------------------------------------------------------------*/

// Function : eint0_isr
// Purpose  : ISR for External Interrupt 0
void eint0_isr(void) __irq;

// Function : eint1_isr
// Purpose  : ISR for External Interrupt 1
void eint1_isr(void) __irq;

// Function : Enable_EINT0
// Purpose  : Configure and enable External Interrupt 0
void Enable_EINT0(void);

// Function : Enable_EINT1
// Purpose  : Configure and enable External Interrupt 1
void Enable_EINT1(void);
