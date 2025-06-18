#ifndef SEVEN_H
#define SEVEN_H

#include <avr/io.h>
#include <util/delay.h>
#include <emb.h>
#include <stdbool.h>

uint8_t seven_digit[] = {
    0xC0,
    0xF9,
    0xA4,
    0xB0,
    0x99,
    0x92,
    0x82,
    0xf8,
    0x80,
    0x90
};

#define SEG_FIRST_D 0b10001000
#define SEG_SECOND_D 0b01000100
#define SEG_THIRD_D 0b00100010
#define SEG_FOURTH_D 0b00010001



#endif