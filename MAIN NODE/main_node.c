//main_node.c
#include "headers.h"
#include "can_defines.h"
#include "can.h"
#include "delay.h"

struct CAN_Frame txFrame;
struct CAN_Frame rxFrame;

volatile u8 left_flag=0,right_flag=0;
u8 fuel;

int main()
{
  int temp;
  unsigned char tp,tpd;

  Enable_EINT0();
  Enable_EINT1();

  Init_CAN1();//CAN initialization
  LCD_Init();//LCD initialization
  FuelBar_();

  Write_CMD_LCD(0x80);//selecting starting line and staring pos
  Write_str_LCD("---Project Menu---");
  delay_ms(1000);

  //temp
  Write_CMD_LCD(0xC0);
  Write_str_LCD("Engine Temp: ");

  Write_CMD_LCD(0x40+24);
  Degree();
  Write_CMD_LCD(0xD2);
  Write_DAT_LCD(3);
  Write_CMD_LCD(0xD3);
  Write_str_LCD("C");

  //fuel
  Write_CMD_LCD(0x94);
  Write_str_LCD("Fuel: ");

  //indicator
  Write_CMD_LCD(0xD4);
  Write_str_LCD("INDICATOR: ");

        Write_CMD_LCD(0x40+32);
  LI();
        Write_CMD_LCD(0x40+40);
  RI();

  txFrame.ID=2;
  txFrame.vbf.RTR=0;
  txFrame.vbf.DLC=1;

  while(1)
  {
        if(ResetDS18b20()==0)
        {
            temp=ReadTemp();  //READING TEMPERATURE FROM DS18B20 USING 1-WIRE PROTOCOL
            tp  = temp>>4;    //GETTING INTEGER PART
            tpd=temp&0x08?0x35:0x30;//GETTING FRACTIONAL PART

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

        if(C1GSR &RBS_BIT_READ)
        {
            CAN1_Rx(&rxFrame);
            if(rxFrame.ID==1)
            {
                fuel=rxFrame.Data1;
                Write_CMD_LCD(0x9F);
                Write_str_LCD("        ");

                Write_CMD_LCD(0x9A);
                FuelBar(fuel);
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

        if(left_flag==1 &&right_flag==0)
        {
           //indicator on leds
           txFrame.Data1=1;
           CAN1_Tx(txFrame);

           //Write_CMD_LCD(0x40+40);
           //RI();
           Write_CMD_LCD(0xDF);
           Write_DAT_LCD(5);

           //indicator blink on lcd
           Write_CMD_LCD(0xDE);
           Write_DAT_LCD(4);
           delay_ms(100);

           Write_CMD_LCD(0xDE);
           Write_DAT_LCD(' ');
           delay_ms(100);
        }

        else if(right_flag==1 && left_flag==0)
        {
           //indicator on leds left to right
           txFrame.Data1=2;
           CAN1_Tx(txFrame);

           //Write_CMD_LCD(0x40+32);
           //LI();
           Write_CMD_LCD(0xDE);
           Write_DAT_LCD(4);

           //indicator blink on lcd
           Write_CMD_LCD(0xDF);
           Write_DAT_LCD(5);
           delay_ms(100);

           Write_CMD_LCD(0xDF);
           Write_DAT_LCD(' ');
           delay_ms(100);

        }
        else if(right_flag==0 && left_flag==0)
        {
           //indicator on leds left to right
           txFrame.Data1=3;
           CAN1_Tx(txFrame);

           //indicator status on lcd
           //Write_CMD_LCD(0x40+32);
           //LI();
           Write_CMD_LCD(0xDE);
           Write_DAT_LCD(4);

           //Write_CMD_LCD(0x40+40);
           //RI();
           Write_CMD_LCD(0xDF);
           Write_DAT_LCD(5);
        }
  }
}

void eint0_isr(void) __irq
{
  left_flag = !left_flag;
  right_flag=0;
  SSETBIT(EXTINT,0);//clear EINT0 flag
  VICVectAddr=0;//dummy write to clear
                //interrupt flag in VIC^M
  //delay_ms(30);//debounce
}
void eint1_isr(void) __irq
{
  right_flag = !right_flag;
  left_flag=0;
  SSETBIT(EXTINT,1);//clear EINT1 flag
  VICVectAddr=0;//dummy write;^M
  //delay_ms(30);//debounce
}

void Enable_EINT0(void)
{
  CFGPIN(PINSEL0,1,FUNC4);
  SSETBIT(VICIntEnable,14);
  VICVectCntl0=0x20|14;
  VICVectAddr0=(unsigned)eint0_isr;
  SCLRBIT(EXTINT,0);
  SETBIT(EXTMODE,0);
  //SETBIT(EXTPOLAR,0);
}

void Enable_EINT1(void)
{
  CFGPIN(PINSEL0,3,FUNC4);
  SSETBIT(VICIntEnable,15);
  VICVectCntl1=0x20|15;
  VICVectAddr1=(unsigned)eint1_isr;
  SCLRBIT(EXTINT,1);
  SETBIT(EXTMODE,1);
  //SETBIT(EXTPOLAR,1);
}
