#ifndef __CAN_H__
#define __CAN_H__

#include "types.h"

/*------------------------------------------------------------
Structure : CAN_Frame
Purpose   : Store CAN message frame information
------------------------------------------------------------*/
struct CAN_Frame
{
        u32 ID;                  // 11-bit CAN Identifier

        /*----------------------------------------------------
        BitField Structure
        Purpose : Store CAN frame control information
        ----------------------------------------------------*/
        struct BitField
        {
                u8 RTR : 1;      // Remote Transmission Request bit
                u8 DLC : 4;      // Data Length Code (0 to 8 bytes)

        }vbf;

        // Data bytes (supports up to 8 bytes total)
        u32 Data1,Data2;
};


/*------------------------------------------------------------
Function : Init_CAN1
Purpose  : Initialize CAN1 controller
------------------------------------------------------------*/
void Init_CAN1(void);


/*------------------------------------------------------------
Function : CAN1_Tx
Purpose  : Transmit CAN frame using CAN1
------------------------------------------------------------*/
void CAN1_Tx(struct CAN_Frame);


/*------------------------------------------------------------
Function : CAN1_Rx
Purpose  : Receive CAN frame using CAN1
------------------------------------------------------------*/
void CAN1_Rx(struct CAN_Frame *);

#endif
