#ifndef INIT_H
#define INIT_H

#include <avr/io.h>
#include <util/delay.h>

#define VALID_LEFT PB3
#define VALID_RIGHT PB2

void    init();
void    notes_timers_init();

#endif