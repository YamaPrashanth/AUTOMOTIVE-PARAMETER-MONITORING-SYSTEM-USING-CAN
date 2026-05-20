#include "headers.h"

/*------------------------------------------------------------
CAN Configuration Macros
Purpose : Define CAN baud rate settings and control bits
------------------------------------------------------------*/

/*------------------------------------------------------------
Macro    : RD1_PIN
Purpose  : Configure P0.25 as CAN1_RX (RD1)
------------------------------------------------------------*/
#define RD1_PIN 0x00040000


/*------------------------------------------------------------
CAN Bit Timing Configuration
------------------------------------------------------------*/

// Desired CAN baud rate = 125 kbps
#define BIT_RATE   125000

// Number of Time Quanta per bit
#define QUANTA     16

// Baud Rate Prescaler value
#define BRP        (PCLK/(BIT_RATE*QUANTA))

// CAN sample point location (70% of bit time)
#define SAMPLE_POINT  (0.7 * QUANTA)

/*------------------------------------------------------------
Time Segment Configuration
------------------------------------------------------------*/

// TSEG1 = Propagation Segment + Phase Segment 1
#define TSEG1        ((int)SAMPLE_POINT-1)

// TSEG2 = Phase Segment 2
#define TSEG2        (QUANTA-(1+TSEG1))

/*------------------------------------------------------------
Synchronization Jump Width (SJW)
------------------------------------------------------------*/

// Maximum SJW allowed based on TSEG2
#define SJW          ((TSEG2 >= 5) ? 4 : (TSEG2-1))

/*------------------------------------------------------------
Sampling Mode
------------------------------------------------------------*/

// 0 -> Single sampling
// 1 -> Triple sampling
#define SAM          0


/*------------------------------------------------------------
Macro    : BTR_LVAL
Purpose  : Generate value for CAN Bit Timing Register (C1BTR)

Fields:
        SAM   -> Sampling mode
        TSEG2 -> Time Segment 2
        TSEG1 -> Time Segment 1
        SJW   -> Synchronization Jump Width
        BRP   -> Baud Rate Prescaler
------------------------------------------------------------*/
#define BTR_LVAL (SAM<<23 | \
                 (TSEG2-1)<<20 | \
                 (TSEG1-1)<<16 | \
                 (SJW-1)<<14 | \
                 (BRP-1))


/*------------------------------------------------------------
C1CMR (CAN Command Register) Bit Definitions
------------------------------------------------------------*/

// Transmission Request bit
#define TR_BIT_SET   1<<0

// Release Receive Buffer bit
#define RRB_BIT_SET  1<<2

// Select Transmit Buffer 1 bit
#define STB1_BIT_SET 1<<5


/*------------------------------------------------------------
C1GSR (CAN Global Status Register) Bit Definitions
------------------------------------------------------------*/

// Receive Buffer Status bit
#define RBS_BIT_READ  1<<0

// Transmit Buffer 1 Status bit
#define TBS1_BIT_READ 1<<2

// Transmission Complete Status bit
#define TCS1_BIT_READ 1<<3
