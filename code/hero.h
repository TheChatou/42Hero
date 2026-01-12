#ifndef HERO_H
#define HERO_H

#include "parts.h"
#include "init.h"
#include "expander.h"

/// @brief enum to describe the master timer state machine
typedef enum {
    UPDATE_SCORE,
    WAIT,
    INPUT_AHEAD,
    PLAY,
    INPUT_AFTER,
    IDLE
} STATE;

uint8_t compare(volatile uint8_t *a, volatile uint8_t *b);
void    reset(volatile uint8_t   *a);
void    timers_stop();
void    play_note_with_timer(uint16_t note, uint8_t track);
uint8_t gauge(uint16_t pct);

#endif