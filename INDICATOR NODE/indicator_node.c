//indicator_node.c
#include "headers.h"
#include "can_defines.h"
#include "can.h"
#include "delay.h"

#define LEDS (0xFF<<0) //P0.0-P0.7 ACTIVE LOW LEDS

struct CAN_Frame rxFrame;
u8 indicator_state = 0;

// Left Indicator (Right -> Left)
// Right Indicator (Left -> Right)

int main()
{
    int i,j;
    // Configure LEDs as output
    IODIR0 |= LEDS;
    IOSET0 = LEDS;//Initially LEDS OFF
    // Initialize CAN
    Init_CAN1();

    while(1)
    {
        // Receive command from Main Node
        if(C1GSR & RBS_BIT_READ)
        {
           CAN1_Rx(&rxFrame);
           if(rxFrame.ID == 2)
           {
              indicator_state = rxFrame.Data1;
           }
        }
        // Execute indicator
        if(indicator_state == 1)
        {
           //Left_Indicator();
           for(i=7;i>=0;i--)
           {
              if(C1GSR & RBS_BIT_READ)
              {
                 CAN1_Rx(&rxFrame);
                 if(rxFrame.ID == 2)
                 {
                    indicator_state = rxFrame.Data1;
                 }
               }

               if(indicator_state!=1)
                       break;
               IOCLR0=(1<<i);
               delay_ms(120);
               IOSET0=(1<<i);

               /*else{
                  IOCLR0 = (1<<i);
                  delay_ms(120);
                  IOSET0 = (1<<i);
               }*/
            }
        }
        else if(indicator_state == 2)
        {
            //Right_Indicator();
            for(j=0;j<=7;j++)
            {
                if(C1GSR & RBS_BIT_READ)
                {
                    CAN1_Rx(&rxFrame);
                    if(rxFrame.ID == 2)
                    {
                        indicator_state = rxFrame.Data1;
                    }
                }

                if(indicator_state!=2)
                        break;
                IOCLR0=(1<<j);
                delay_ms(120);
                IOSET0=(1<<j);

                /*else{
                    IOCLR0 = (1<<j);
                    delay_ms(120);
                    IOSET0 = (1<<j);
                }*/
            }
        }
        else//indicator_state=3
        {
            IOSET0 = LEDS;
        }
    }
}
