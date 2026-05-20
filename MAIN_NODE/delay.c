//delay.c

/*------------------------------------------------------------
Function : delay_us
Purpose  : Generate blocking delay in microseconds using software loop
------------------------------------------------------------*/
void delay_us(unsigned int tdly)
{
        tdly*=12;                 // Scale delay count for approximate 1µs timing (60MHz / 12 iterations ˜ 1µs)
        while(tdly--);           // Busy-wait loop, holds execution for tdly microseconds
}

/*------------------------------------------------------------
Function : delay_ms
Purpose  : Generate blocking delay in milliseconds using software loop
------------------------------------------------------------*/
void delay_ms(unsigned int tdly)
{
        tdly*=12000;             // Scale delay count for approximate 1ms timing (60MHz / 12000 iterations ˜ 1ms)
        while(tdly--);           // Busy-wait loop, holds execution for tdly milliseconds
}

/*------------------------------------------------------------
Function : delay_s
Purpose  : Generate blocking delay in seconds using software loop
------------------------------------------------------------*/
void delay_s(unsigned int tdly)
{
        tdly*=12000000;          // Scale delay count for approximate 1s timing (60MHz / 12M iterations ˜ 1s)
        while(tdly--);           // Busy-wait loop, holds execution for tdly seconds
}
