#include "headers.h"

void Init_ADC(void)
{
  ADCR=PDN_BIT|CLKDIV|CHANNEL_SEL;
}

f32 Read_ADC(u8 chNo)
{
  u16 adcVal=0;
	WRITEBYTE(ADCR,0,chNo);
	SETBIT(ADCR,ADC_START_BIT);
	delay_us(3);
	while(!READBIT(ADDR,DONE_BIT));
	CLRBIT(ADCR,ADC_START_BIT);
	adcVal=(ADDR>>6)&0x3FF;
	return adcVal;
}
