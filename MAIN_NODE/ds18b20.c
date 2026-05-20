#include "headers.h"

/*------------------------------------------------------------
Macro Definitions
------------------------------------------------------------*/

// DS18B20 1-Wire data line connected to P0.16
#define D 1<<16

// Read current state of P0.16
#define R (IOPIN0&(1<<16))


/*------------------------------------------------------------
Function : ResetDS18b20
Purpose  : Send reset pulse and detect DS18B20 presence
------------------------------------------------------------*/
unsigned char ResetDS18b20(void)
{
        unsigned int presence;

        IODIR0 |= D;              // Configure data line as output
        IOPIN0 |= D;              // Pull data line HIGH

        delay_us(1);              // Delay ˜ 1µs

        IOPIN0 &= ~(D);           // Pull data line LOW (reset pulse)

        delay_us(478);            // Hold LOW for ˜ 480µs

        IOPIN0 |= D;              // Release data line

        delay_us(54);             // Wait for presence response

        presence = IOPIN0;        // Read presence pulse

        delay_us(423);            // Recovery delay

        // Check if device responded
        if(presence & R)
                return 1;
        else
                return 0;
}


/*------------------------------------------------------------
Function : ReadBit
Purpose  : Read single bit from DS18B20 using 1-Wire protocol
------------------------------------------------------------*/
unsigned char ReadBit(void)
{
        unsigned int B;

        IOPIN0 &= ~(D);           // Pull line LOW to initiate read slot

        delay_us(1);              // Delay ˜ 1µs

        IOPIN0 |= D;              // Release line

        IODIR0 &= ~(D);           // Configure pin as input

        delay_us(10);             // Wait before sampling bit

        B = IOPIN0;               // Read data line state

        IODIR0 |= D;              // Reconfigure pin as output

        // Return received bit
        if(B & R)
                return 1;
        else
                return 0;
}


/*------------------------------------------------------------
Function : WriteBit
Purpose  : Write single bit to DS18B20 using 1-Wire protocol
------------------------------------------------------------*/
void WriteBit(unsigned char Dbit)
{
        IOPIN0 &= ~(D);           // Pull line LOW to start write slot

        delay_us(1);              // Delay ˜ 1µs

        if(Dbit)
                IOPIN0 |= D;      // Release line for logic HIGH

        delay_us(58);             // Hold timing slot

        IOPIN0 |= D;              // Release line

        delay_us(1);              // Recovery delay
}


/*------------------------------------------------------------
Function : ReadByte
Purpose  : Read one byte from DS18B20
------------------------------------------------------------*/
unsigned char ReadByte(void)
{
        unsigned char i;
        unsigned char Din = 0;

        for (i=0;i<8;i++)
        {
                // Read bits one by one (LSB first)
                Din |= ReadBit() ? 0x01<<i : Din;

                delay_us(45);     // Delay between bit reads
        }

        return(Din);
}


/*------------------------------------------------------------
Function : WriteByte
Purpose  : Write one byte to DS18B20
------------------------------------------------------------*/
void WriteByte(unsigned char Dout)
{
        unsigned char i;

        for (i=0; i<8; i++)
        {
                WriteBit((Dout & 0x1));   // Send LSB first

                Dout = Dout >> 1;         // Shift next bit

                delay_us(1);              // Small delay
        }

        delay_us(98);                     // Recovery delay
}


/*------------------------------------------------------------
Function : ReadTemp
Purpose  : Read temperature value from DS18B20 sensor
------------------------------------------------------------*/
int ReadTemp(void)
{
        unsigned char n,buff[2];
        int temp;

        ResetDS18b20();       // Reset DS18B20

        WriteByte(0xcc);      // Skip ROM command

        WriteByte(0x44);      // Start temperature conversion

        // Wait until conversion is complete
        while (ReadByte()==0xff);

        ResetDS18b20();       // Reset again

        WriteByte(0xcc);      // Skip ROM command

        WriteByte(0xbe);      // Read Scratchpad command

        // Read first 2 bytes of temperature data
        for (n=0; n<2; n++)
        {
                buff[n] = ReadByte();
        }

        // Combine MSB and LSB into 16-bit temperature value
        temp = buff[1];

        temp = temp << 8;

        temp = temp | buff[0];

        return(temp);         // Return raw temperature data
}
