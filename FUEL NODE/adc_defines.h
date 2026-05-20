#ifndef _ADC_DEFINES_H_
#define _ADC_DEFINES_H_

//defines for ADCR
#define CH0                0x01 //P0.27
#define CH1                0x02 //P0.28
#define CH2                0x04 //P0.29
#define CH3                0x08 //P0.30

#define CHANNEL_SEL        CH0|CH1
#define FOSC               12000000
#define CCLK               (5 * FOSC)
//#define PCLK               CCLK/4
#define ADCLK              3750000
#define CLKDIV             (((PCLK/ADCLK)-1)<<8)

#define PDN_BIT            (1<<21)
#define ADC_START_BIT      24

//defines for ADDR
#define DONE_BIT           31

#endif
