/* defines.h */

#ifndef __DEFINES_H__
#define __DEFINES_H__

/*------------------------------------------------------------
Bit Manipulation Macros
Purpose : Perform common bit-level operations efficiently
------------------------------------------------------------*/

/*------------------------------------------------------------
Macro    : SETBIT
Purpose  : Set a specific bit to 1
------------------------------------------------------------*/
#define SETBIT(WORD,BITPOS)            (WORD|=(1<<BITPOS))

/*------------------------------------------------------------
Macro    : CLRBIT
Purpose  : Clear a specific bit to 0
------------------------------------------------------------*/
#define CLRBIT(WORD,BITPOS)            (WORD&=~(1<<BITPOS))

/*------------------------------------------------------------
Macro    : CPLBIT
Purpose  : Toggle/Complement a specific bit
------------------------------------------------------------*/
#define CPLBIT(WORD,BITPOS)            (WORD^=(1<<BITPOS))

/*------------------------------------------------------------
Macro    : WRITEBIT
Purpose  : Write a value (0 or 1) to specific bit position
------------------------------------------------------------*/
#define WRITEBIT(WORD,BITPOS,BIT)      (BIT?SETBIT(WORD,BITPOS):CLRBIT(WORD,BITPOS))

/*------------------------------------------------------------
Macro    : READBIT
Purpose  : Read the value of a specific bit
------------------------------------------------------------*/
#define READBIT(WORD,BITPOS)           ((WORD>>BITPOS)&1)

/*------------------------------------------------------------
Macro    : READWRITEBIT
Purpose  : Copy one bit value into another bit position
------------------------------------------------------------*/
#define READWRITEBIT(WORD,WBIT,RBIT)   (WORD=((WORD&~(1<<WBIT))|(((WORD>>RBIT)&1)<<WBIT)))

/*------------------------------------------------------------
Macro    : WRITEUNIBBLE
Purpose  : Write upper nibble (4 bits) of byte into word
------------------------------------------------------------*/
#define WRITEUNIBBLE(WORD,BITPOS,BYTE) (WORD=(WORD&~(0x0000000F<<BITPOS))|((BYTE>>4)<<BITPOS))

/*------------------------------------------------------------
Macro    : WRITELNIBBLE
Purpose  : Write lower nibble (4 bits) of byte into word
------------------------------------------------------------*/
#define WRITELNIBBLE(WORD,BITPOS,BYTE) (WORD=(WORD&~(0x0000000F<<BITPOS))|((BYTE&0X0F)<<BITPOS))

/*------------------------------------------------------------
Macro    : READNIBBLE
Purpose  : Read 4-bit nibble from word
------------------------------------------------------------*/
#define READNIBBLE(WORD,BITPOS)        ((WORD>>BITPOS)&0x0000000F)

/*------------------------------------------------------------
Macro    : WRITEBYTE
Purpose  : Write one byte into specified bit position
------------------------------------------------------------*/
#define WRITEBYTE(WORD,BITPOS,BYTE)    (WORD=(WORD&~(0x000000FF<<BITPOS))|(BYTE<<BITPOS))

/*------------------------------------------------------------
Macro    : READBYTE
Purpose  : Read one byte from specified bit position
------------------------------------------------------------*/
#define READBYTE(WORD,BITPOS)          ((WORD>>BITPOS)&0x000000FF)

/*------------------------------------------------------------
Macro    : SSETBIT
Purpose  : Set only one specific bit and clear others
------------------------------------------------------------*/
#define SSETBIT(WORD,BITPOS)           (WORD=1<<BITPOS)

/*------------------------------------------------------------
Macro    : SCLRBIT
Purpose  : Alias for SSETBIT
------------------------------------------------------------*/
#define SCLRBIT SSETBIT

#endif
