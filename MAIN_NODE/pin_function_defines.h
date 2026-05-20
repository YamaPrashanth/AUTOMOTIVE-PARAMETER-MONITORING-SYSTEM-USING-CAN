/* pin_function_defines.h */

#ifndef __PIN_FUNCTION_DEFINES_H__
#define __PIN_FUNCTION_DEFINES_H__

/*------------------------------------------------------------
Pin Function Selection Macros
Purpose : Configure LPC21xx pin functions using PINSEL registers
------------------------------------------------------------*/

/*------------------------------------------------------------
Macro    : FUNC1
Purpose  : Select Function 1 (GPIO Function)
------------------------------------------------------------*/
#define FUNC1 0

/*------------------------------------------------------------
Macro    : FUNC2
Purpose  : Select Function 2 (Alternate Function 1)
------------------------------------------------------------*/
#define FUNC2 1

/*------------------------------------------------------------
Macro    : FUNC3
Purpose  : Select Function 3 (Alternate Function 2)
------------------------------------------------------------*/
#define FUNC3 2

/*------------------------------------------------------------
Macro    : FUNC4
Purpose  : Select Function 4 (Alternate Function 3)
------------------------------------------------------------*/
#define FUNC4 3

/*------------------------------------------------------------
Macro    : CFGPIN
Purpose  : Configure pin function in PINSEL0/PINSEL1 register

Arguments:
        WORD -> PINSEL register (PINSEL0 or PINSEL1)
        PIN  -> Pin number
        FUNC -> Function selection value

Description:
        - Pins 0 to 15 are configured using PINSEL0
        - Pins 16 to 31 are configured using PINSEL1
------------------------------------------------------------*/

//#define CFGPIN(WORD,PIN,FUNC) ((WORD=WORD&~((unsigned)0x00000003)<<(PIN*2))|(FUNC<<(PIN*2)))

#define CFGPIN(WORD,PIN,FUNC) WORD=((PIN<16)?((WORD&~(3<<(PIN*2)))|(FUNC<<(PIN*2))):((WORD&~(3<<((PIN-16)*2)))|(FUNC<<((PIN-16)*2))));

#endif
