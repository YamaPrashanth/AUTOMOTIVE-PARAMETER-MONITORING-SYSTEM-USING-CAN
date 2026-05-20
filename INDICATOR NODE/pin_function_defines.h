                    /* pin_function_defines.h */
#ifndef __PIN_FUNCTION_DEFINES_H__
#define __PIN_FUNCTION_DEFINES_H__

#define FUNC1 0
#define FUNC2 1
#define FUNC3 2
#define FUNC4 3

//#define CFGPIN(WORD,PIN,FUNC) ((WORD=WORD&~((unsigned)0x00000003)<<(PIN*2))|(FUNC<<(PIN*2)))
#define CFGPIN(WORD,PIN,FUNC) WORD=((PIN<16)?((WORD&~(3<<(PIN*2)))|(FUNC<<(PIN*2))):((WORD&~(3<<((PIN-16)*2)))|(FUNC<<((PIN-16)*2))));

#endif
