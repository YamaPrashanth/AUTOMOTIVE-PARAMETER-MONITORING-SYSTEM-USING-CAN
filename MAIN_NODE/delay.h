//delay.h

#ifndef DELAY_H
#define DELAY_H

/*------------------------------------------------------------
Delay Function Declarations
Purpose : Provide software-based blocking delay functions
------------------------------------------------------------*/

/*------------------------------------------------------------
Function : delay_us
Purpose  : Generate delay in microseconds
------------------------------------------------------------*/
void delay_us(unsigned int);

/*------------------------------------------------------------
Function : delay_ms
Purpose  : Generate delay in milliseconds
------------------------------------------------------------*/
void delay_ms(unsigned int);

/*------------------------------------------------------------
Function : delay_s
Purpose  : Generate delay in seconds
------------------------------------------------------------*/
void delay_s(unsigned int);

#endif
