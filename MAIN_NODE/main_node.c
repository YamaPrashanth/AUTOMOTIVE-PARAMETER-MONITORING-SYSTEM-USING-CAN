//main_node.c

#include "headers.h"
#include "can_defines.h"
#include "can.h"
#include "delay.h"

/*------------------------------------------------------------
Global Variables
------------------------------------------------------------*/

// CAN frame structure for transmission
struct CAN_Frame txFrame;

// CAN frame structure for reception
struct CAN_Frame rxFrame;

// Indicator status flags
volatile u8 left_flag=0,right_flag=0;

// Variable to store received fuel percentage
u8 fuel;


/*------------------------------------------------------------
Function : main
Purpose  : Main node for monitoring and displaying
           temperature, fuel level, and indicators
------------------------------------------------------------*/
int main()
{
        int temp;

        unsigned char tp,tpd;
        Enable_EINT0();          // Enable external interrupt for left indicator
        Enable_EINT1();          // Enable external interrupt for right indicator
        Init_CAN1();             // Initialize CAN peripheral
        LCD_Init();              // Initialize LCD
        FuelBar_();              // Create custom fuel bar characters


        /*----------------------------------------------------
        LCD Startup Display
        ----------------------------------------------------*/
        Write_CMD_LCD(0x80);     // Select first row, first column
        Write_str_LCD("---Project Menu---");
        delay_ms(1000);


        /*----------------------------------------------------
        Temperature Display Setup
        ----------------------------------------------------*/
        Write_CMD_LCD(0xC0);
        Write_str_LCD("Engine Temp: ");
        Write_CMD_LCD(0x40+24);
        Degree();                // Create degree symbol
        Write_CMD_LCD(0xD2);
        Write_DAT_LCD(3);        // Display degree symbol
        Write_CMD_LCD(0xD3);
        Write_str_LCD("C");


        /*----------------------------------------------------
        Fuel Display Setup
        ----------------------------------------------------*/
        Write_CMD_LCD(0x94);
        Write_str_LCD("Fuel: ");


        /*----------------------------------------------------
        Indicator Display Setup
        ----------------------------------------------------*/
        Write_CMD_LCD(0xD4);
        Write_str_LCD("INDICATOR: ");

        // Store custom left indicator symbol
        Write_CMD_LCD(0x40+32);
        LI();

        // Store custom right indicator symbol
        Write_CMD_LCD(0x40+40);
        RI();


        /*----------------------------------------------------
        CAN Frame Configuration
        ----------------------------------------------------*/
        txFrame.ID=2;            // CAN ID for indicator node
        txFrame.vbf.RTR=0;       // Data frame
        txFrame.vbf.DLC=1;       // One byte data length


        /*----------------------------------------------------
        Infinite Loop
        ----------------------------------------------------*/
        while(1)
        {
                /*--------------------------------------------
                Read Temperature from DS18B20
                --------------------------------------------*/
                if(ResetDS18b20()==0)
                {
                        // Read raw temperature value
                        temp=ReadTemp();

                        // Extract integer part
                        tp  = temp>>4;

                        // Extract fractional part
                        tpd=temp&0x08?0x35:0x30;

                        // Display temperature on LCD
                        Write_CMD_LCD(0xCD);
                        Write_int_LCD(tp);
                        Write_DAT_LCD('.');
                        Write_DAT_LCD(tpd);
                }

                /*else
                {
                        Write_CMD_LCD(0xCD);
                        Write_str_LCD(" - ");
                }*/


                /*--------------------------------------------
                Receive Fuel Data from CAN Bus
                --------------------------------------------*/
                if(C1GSR & RBS_BIT_READ)
                {
                        CAN1_Rx(&rxFrame);

                        // Check for fuel node message
                        if(rxFrame.ID==1)
                        {
                                fuel=rxFrame.Data1;

                                // Clear previous display
                                Write_CMD_LCD(0x9F);

                                Write_str_LCD("        ");

                                // Display fuel bar
                                Write_CMD_LCD(0x9A);

                                FuelBar(fuel);

                                // Display fuel percentage
                                Write_CMD_LCD(0x9F);

                                Write_DAT_LCD('(');

                                Write_int_LCD(fuel);

                                Write_CMD_LCD(0xA3);

                                Write_str_LCD("%)");
                        }
                }

                /*else
                {
                        Write_CMD_LCD(0x9E);
                        Write_str_LCD(" - ");
                }*/


                /*--------------------------------------------
                Left Indicator Operation
                --------------------------------------------*/
                if(left_flag==1 && right_flag==0)
                {
                        // Send indicator status through CAN
                        txFrame.Data1=1;

                        CAN1_Tx(txFrame);

                        // Display right indicator symbol
                        Write_CMD_LCD(0xDF);

                        Write_DAT_LCD(5);

                        // Blink left indicator on LCD
                        Write_CMD_LCD(0xDE);

                        Write_DAT_LCD(4);

                        delay_ms(100);

                        Write_CMD_LCD(0xDE);

                        Write_DAT_LCD(' ');

                        delay_ms(100);
                }


                /*--------------------------------------------
                Right Indicator Operation
                --------------------------------------------*/
                else if(right_flag==1 && left_flag==0)
                {
                        // Send indicator status through CAN
                        txFrame.Data1=2;

                        CAN1_Tx(txFrame);

                        // Display left indicator symbol
                        Write_CMD_LCD(0xDE);

                        Write_DAT_LCD(4);

                        // Blink right indicator on LCD
                        Write_CMD_LCD(0xDF);

                        Write_DAT_LCD(5);

                        delay_ms(100);

                        Write_CMD_LCD(0xDF);

                        Write_DAT_LCD(' ');

                        delay_ms(100);
                }


                /*--------------------------------------------
                Both Indicators OFF
                --------------------------------------------*/
                else if(right_flag==0 && left_flag==0)
                {
                        // Send OFF status through CAN
                        txFrame.Data1=3;

                        CAN1_Tx(txFrame);

                        // Display left indicator
                        Write_CMD_LCD(0xDE);

                        Write_DAT_LCD(4);

                        // Display right indicator
                        Write_CMD_LCD(0xDF);

                        Write_DAT_LCD(5);
                }
        }
}


/*------------------------------------------------------------
Function : eint0_isr
Purpose  : ISR for Left Indicator External Interrupt
------------------------------------------------------------*/
void eint0_isr(void) __irq
{
        left_flag = !left_flag;  // Toggle left indicator state

        right_flag=0;            // Disable right indicator

        SSETBIT(EXTINT,0);       // Clear EINT0 interrupt flag

        VICVectAddr=0;           // Clear interrupt in VIC

        //delay_ms(30);          // Debounce delay
}


/*------------------------------------------------------------
Function : eint1_isr
Purpose  : ISR for Right Indicator External Interrupt
------------------------------------------------------------*/
void eint1_isr(void) __irq
{
        right_flag = !right_flag; // Toggle right indicator state

        left_flag=0;              // Disable left indicator

        SSETBIT(EXTINT,1);        // Clear EINT1 interrupt flag

        VICVectAddr=0;            // Clear interrupt in VIC

        //delay_ms(30);           // Debounce delay
}


/*------------------------------------------------------------
Function : Enable_EINT0
Purpose  : Configure and enable External Interrupt 0
------------------------------------------------------------*/
void Enable_EINT0(void)
{
        CFGPIN(PINSEL0,1,FUNC4); // Configure P0.1 as EINT0

        SSETBIT(VICIntEnable,14);// Enable EINT0 interrupt in VIC

        VICVectCntl0=0x20|14;    // Enable vectored interrupt slot

        VICVectAddr0=(unsigned)eint0_isr;

        SCLRBIT(EXTINT,0);       // Clear pending interrupt flag

        SETBIT(EXTMODE,0);       // Configure edge-triggered mode

        //SETBIT(EXTPOLAR,0);    // Falling edge trigger
}


/*------------------------------------------------------------
Function : Enable_EINT1
Purpose  : Configure and enable External Interrupt 1
------------------------------------------------------------*/
void Enable_EINT1(void)
{
        CFGPIN(PINSEL0,3,FUNC4); // Configure P0.3 as EINT1

        SSETBIT(VICIntEnable,15);// Enable EINT1 interrupt in VIC

        VICVectCntl1=0x20|15;    // Enable vectored interrupt slot

        VICVectAddr1=(unsigned)eint1_isr;

        SCLRBIT(EXTINT,1);       // Clear pending interrupt flag

        SETBIT(EXTMODE,1);       // Configure edge-triggered mode

        //SETBIT(EXTPOLAR,1);    // Falling edge trigger
}
