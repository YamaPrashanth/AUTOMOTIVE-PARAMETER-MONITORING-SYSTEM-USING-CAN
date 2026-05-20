#include <lpc21xx.h>

#include "types.h"
#include "can.h"
#include "can_defines.h"

/*------------------------------------------------------------
Function : Init_CAN1
Purpose  : Initialize CAN Controller 1
------------------------------------------------------------*/
void Init_CAN1(void)
{
        /*----------------------------------------------------
        Configure CAN1 RX Pin
        ----------------------------------------------------*/

        // Configure P0.25 as CAN1_RX (RD1)
        // TD1 (CAN1_TX) is dedicated automatically
        PINSEL1 |= RD1_PIN;

        /*----------------------------------------------------
        Reset CAN Controller
        ----------------------------------------------------*/

        C1MOD = 1;               // Enter reset mode

        /*----------------------------------------------------
        Acceptance Filter Configuration
        ----------------------------------------------------*/

        // Accept all received CAN messages
        AFMR = 2;

        /*----------------------------------------------------
        Set CAN Baud Rate
        ----------------------------------------------------*/

        // Configure baud rate using predefined value
        C1BTR = BTR_LVAL;

        /*----------------------------------------------------
        Enable CAN Controller
        ----------------------------------------------------*/

        C1MOD = 0;               // Exit reset mode
}


/*------------------------------------------------------------
Function : CAN1_Tx
Purpose  : Transmit CAN frame using CAN1 controller
------------------------------------------------------------*/
void CAN1_Tx(struct CAN_Frame txFrame)
{
        /*----------------------------------------------------
        Wait Until TX Buffer is Empty
        ----------------------------------------------------*/

        // Check transmit buffer status in C1GSR
        while((C1GSR & TBS1_BIT_READ) == 0);

        /*----------------------------------------------------
        Load CAN Identifier
        ----------------------------------------------------*/

        // Place 11-bit CAN ID into transmit identifier register
        C1TID1 = txFrame.ID;

        /*----------------------------------------------------
        Configure Frame Information
        ----------------------------------------------------*/

        // Configure RTR bit and DLC field
        C1TFI1 = txFrame.vbf.RTR << 30 |
                 txFrame.vbf.DLC << 16;

        /*----------------------------------------------------
        Load Data Bytes for Data Frame
        ----------------------------------------------------*/

        // If frame is not remote frame
        if(txFrame.vbf.RTR != 1)
        {
                // Place data bytes 1-4
                C1TDA1 = txFrame.Data1;

                // Place data bytes 5-8
                C1TDB1 = txFrame.Data2;
        }

        /*----------------------------------------------------
        Start CAN Transmission
        ----------------------------------------------------*/

        // Select transmit buffer 1 and start transmission
        C1CMR = STB1_BIT_SET | TR_BIT_SET;

        /*----------------------------------------------------
        Wait for Transmission Completion
        ----------------------------------------------------*/

        while((C1GSR & TCS1_BIT_READ) == 0);
}


/*------------------------------------------------------------
Function : CAN1_Rx
Purpose  : Receive CAN frame using CAN1 controller
------------------------------------------------------------*/
void CAN1_Rx(struct CAN_Frame *rxFrame)
{
        /*----------------------------------------------------
        Wait Until CAN Frame is Received
        ----------------------------------------------------*/

        while((C1GSR & RBS_BIT_READ) == 0);

        /*----------------------------------------------------
        Read CAN Identifier
        ----------------------------------------------------*/

        // Read received 11-bit CAN ID
        rxFrame->ID = C1RID;

        /*----------------------------------------------------
        Read Frame Status Information
        ----------------------------------------------------*/

        // Extract RTR (Remote Transmission Request) bit
        rxFrame->vbf.RTR = (C1RFS >> 30) & 1;

        // Extract Data Length Code (DLC)
        rxFrame->vbf.DLC = (C1RFS >> 16) & 0x0F;

        /*----------------------------------------------------
        Read Data Bytes for Data Frame
        ----------------------------------------------------*/

        // Check if received frame is a data frame
        if(rxFrame->vbf.RTR == 0)
        {
                // Read data bytes 1-4
                rxFrame->Data1 = C1RDA;

                // Read data bytes 5-8
                rxFrame->Data2 = C1RDB;
        }

        /*----------------------------------------------------
        Release Receive Buffer
        ----------------------------------------------------*/

        // Release receive buffer after frame processing
        C1CMR = RRB_BIT_SET;
}
