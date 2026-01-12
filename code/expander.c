#include "expander.h"

// expander corresponding to the leds
volatile Expander exp_leds = {&PORTA, PA0, PA2, PA4}; 

/// @brief set the values of a linear sequence of shift registers
/// @param exp the starting shift register (the one connect to the board)
/// @param lane a vector of uint representing the values of the ports to set
/// @param size the size of the vector (should a priori correspond the the number of expanders)
void    shiftLane(volatile Expander *exp,volatile uint8_t *lane, uint8_t size)
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

/// @brief set all leds to off
void    turn_leds_off()
{
    uint8_t l[4] = {0,0,0,0};
    shiftLane(&exp_leds, l, 4);
}

/// @brief set all leds to on
void    turn_leds_on()
{
    uint8_t l[4] = {0b11111111, 0b11111111, 0b11111111, 0b11111111};
    shiftLane(&exp_leds, l, 4);
}