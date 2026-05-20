#ifndef _ADC_DEFINES_H_
#define _ADC_DEFINES_H_

/*------------------------------------------------------------
ADC Configuration Macros
Purpose : Define ADC channels, clock settings, and control bits
------------------------------------------------------------*/

/*------------------------------------------------------------
ADC Channel Selection Macros
Purpose : Select ADC input channels
------------------------------------------------------------*/

// ADC Channel 0 connected to P0.27
#define CH0                0x01

// ADC Channel 1 connected to P0.28
#define CH1                0x02

// ADC Channel 2 connected to P0.29
#define CH2                0x04

// ADC Channel 3 connected to P0.30
#define CH3                0x08

/*------------------------------------------------------------
Macro    : CHANNEL_SEL
Purpose  : Enable ADC channels CH0 and CH1
------------------------------------------------------------*/
#define CHANNEL_SEL        CH0|CH1

/*------------------------------------------------------------
Clock Configuration Macros
------------------------------------------------------------*/

// Crystal Oscillator Frequency = 12MHz
#define FOSC               12000000

// CPU Clock Frequency = 5 × FOSC = 60MHz
#define CCLK               (5 * FOSC)

// Peripheral Clock Frequency
//#define PCLK               CCLK/4

// ADC Operating Clock Frequency = 3.75MHz
#define ADCLK              3750000

/*------------------------------------------------------------
Macro    : CLKDIV
Purpose  : ADC clock divider value calculation

Formula:
        ADC Clock = PCLK / (CLKDIV + 1)
------------------------------------------------------------*/
#define CLKDIV             (((PCLK/ADCLK)-1)<<8)

/*------------------------------------------------------------
ADCR Register Bit Definitions
------------------------------------------------------------*/

// Power Down Bit (Enable ADC when set)
#define PDN_BIT            (1<<21)

// ADC Start Conversion Bit Position
#define ADC_START_BIT      24

/*------------------------------------------------------------
ADDR Register Bit Definitions
------------------------------------------------------------*/

// ADC Conversion Complete Flag Bit
#define DONE_BIT           31

#endif
