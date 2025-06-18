#include <avr/io.h>
#include <util/delay.h>
#include <emb.h>
#include <stdbool.h>
#include "seven_segment.h"


typedef struct Expander
{
    volatile uint8_t    *port;
    uint8_t             rclck; // 12
    uint8_t             srclk; // 11
    uint8_t             ser; // 14

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
    DDRC &= ~(0b01010101);
    DDRL &= ~(0b01010101);
    PORTA = 0;
    PORTC |= 0b01010101;
    PORTL |= 0b01010101;
    
}



int main()
{
    setup();
    uint8_t all = 0b11111111;
    uint8_t off = 0;
    uint8_t leds_on[4] = {all,all,all,all};
    uint8_t leds_off[4] = {off, off, off ,off};
    volatile uint8_t leds[4] = {off, off, off, off};
    volatile uint8_t    buttons_left[4] = {1,1,1,1};
    volatile uint8_t    buttons_right[4] = {1,1,1,1};
    shiftLane(&segments, leds_off, 4);
    uint8_t idx = 0;
    _delay_ms(2000);
    while(1)
    {
        buttons_left[0] = PINC & (1 << PC6);
        buttons_left[1] = PINC & (1 << PC4);
        buttons_left[2] = PINC & (1 << PC2);
        buttons_left[3] = PINC & (1 << PC0);
        
        buttons_right[0] = PINL & (1 << PL6);
        buttons_right[1] = PINL & (1 << PL4);
        buttons_right[2] = PINL & (1 << PL2);
        buttons_right[3] = PINL & (1 << PL0);

        leds[0] = buttons_left[0] == 0;
        leds[1] = buttons_left[1] == 0;
        leds[2] = buttons_left[2] == 0;
        leds[3] = buttons_left[3] == 0;

        leds[0] |= ((buttons_right[0] == 0) << 7);
        leds[1] |= ((buttons_right[1] == 0) << 7);
        leds[2] |= ((buttons_right[2] == 0) << 7);
        leds[3] |= ((buttons_right[3] == 0) << 7);

        shiftLane(&segments, leds, 4);
        _delay_ms(2000);
    }
}



    
// vert bleu noir
/*
0 : 0b11000000
1 : 0b11111001
6 : 0b10000010
5: 0b10010010
 */


// notes 1 + 1 1 0 0 1 1 1 0 0 0
// 1 1 0 0 1 1 1 0

//temps 0 -> 0 0 0 0 0 0 0 1^

// 0 0 0 0 0 0 1 1^