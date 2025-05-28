#include <avr/io.h>
#include <util/delay.h>
#include <emb.h>
#include <stdbool.h>


typedef struct Expander
{
    volatile uint8_t    *port;
    uint8_t             rclck;
    uint8_t             srclk;
    uint8_t             ser;

} Expander;

volatile Expander segments = {&PORTA, PA0, PA2, PA4};

void    shiftLane(Expander *exp, uint8_t *lane, uint8_t size)
{
    *exp->port &= ~(1 << exp->rclck);
    for (uint8_t idx = 0; idx < size; ++idx)
    {
        uint8_t data = lane[idx];
        for (uint8_t bit = 0; bit < 8; ++bit)
        {
            *exp->port &= ~(1 << exp->srclk);
            if ((data >> bit) & 1)
 
 
 
                *exp->port |= 1 << exp->ser;
            else
                *exp->port &= ~(1 << exp->ser);
            *exp->port |= 1 << exp->srclk;
            __asm__ __volatile__ ("nop");
        }
    }
    *exp->port |= 1 << exp->rclck;
}


void    setup()
{
    DDRA |= (1 << PA4) | (1 << PA0) | (1 << PA2) | (1 << PA6);
    PORTA = 0;
    
}



int main()
{
    setup();
    uint8_t zero[2] = {0b00010000, 0b11000000};
    uint8_t one[2] = {0b00100000, 0b11111001};
    uint8_t six[2] = {0b01000000, 0b10000010};
    uint8_t five[2] = {0b10000000, 0b10010010};
    uint8_t reset[2] = {0b00000000, 0b11111111};
    while(1)
    {
        shiftLane(&segments, zero, 2);
        // shiftLane(&segments, reset, 2);
        shiftLane(&segments, one, 2);
        // shiftLane(&segments, reset, 2);
        shiftLane(&segments, six, 2);
        // shiftLane(&segments, reset, 2);
        shiftLane(&segments, five, 2);
        // shiftLane(&segments, reset, 2);
    }
    
}

/*
0 : 0b11000000
1 : 0b11111001
6 : 0b10000010
5: 0b10010010
 */