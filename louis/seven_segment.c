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

const volatile Expander segments = {&PORTA, PA0, PA2, PA4};

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
    DDRL = 0b00001111;
    PORTL = 0;
}



int main()
{
    setup();
    uint8_t digit[4] = {0b01000000, 0b00010000, 0b00000100, 0b00000001};
    uint8_t nums[4] = {0b00000001, 0b00000011, 0b00001100, 0b00001001};
    uint8_t idx = 0;
    while(1)
    {
        PORTA = digit[idx];
        PORTL = nums[idx];
        idx = (idx+1) % 4;
        _delay_ms(500);
    }
    
}