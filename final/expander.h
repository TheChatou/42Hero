#ifndef EXPANDER_H
#define EXPANDER_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>


typedef struct Expander
{
    volatile uint8_t    *port;
    uint8_t             rclck; // 12
    uint8_t             srclk; // 11
    uint8_t             ser; // 14

} Expander;

void    shiftLane(volatile Expander *exp, volatile uint8_t *lane, uint8_t size);
void    turn_leds_off();
void    turn_leds_on();


#endif