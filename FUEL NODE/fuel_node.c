//fuel_node.c
#include "headers.h"
#include "can_defines.h"
#include "can.h"
#include "delay.h"

struct CAN_Frame txFrame;
int main()
{
    f32 fuel,voltage;
    f32 empty_tank,full_tank;
    //f32 empty_tank=0.264,full_tank=2.380;
    Init_ADC();
    Init_CAN1();
    while(1)
    {
        voltage = Read_ADC(CH0);

        empty_tank=((0.238/3.3)*1023);
        full_tank=((2.364/3.3)*1023);

        fuel=(((voltage-empty_tank)/(full_tank-empty_tank))*100);

        txFrame.ID=1;
        txFrame.vbf.RTR=0;
        txFrame.vbf.DLC=1;
        txFrame.Data1=(u8)fuel;
        while(!(C1GSR & TCS1_BIT_READ)); //wait

        CAN1_Tx(txFrame);
        delay_ms(500);
    }
}
