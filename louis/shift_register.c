#include "shift_register.h"

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