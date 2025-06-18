#ifndef EXPANDER_H
#define EXPANDER_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

typedef struct Expander
{
    volatile uint8_t    *port;
    uint8_t             rclck;
    uint8_t             srclk;
    uint8_t             ser;

} Expander;

void    shiftLane(Expander *exp, uint8_t *lane, uint8_t size);

#endif