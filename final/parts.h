#ifndef PARTS_H
#define PARTS_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <avr/pgmspace.h>

#define MUSIC_MAX_LEN 1000
#define ALL 0b11111111
typedef uint8_t             ui8;
typedef uint16_t            ui16;
typedef uint32_t            ui32;
typedef volatile uint8_t    vui8;
typedef volatile uint16_t   vui16;
typedef volatile uint32_t   vui32;

typedef struct t_track
{
    uint16_t    note[MUSIC_MAX_LEN];
}   t_track;

typedef struct
{
    t_track tracks[4];       // 4 pistes max
    uint8_t led[MUSIC_MAX_LEN];           // LEDs à allumer pour chaque tick
    uint16_t tempo;                     // Tempo de la musique
    uint16_t length;                    // Nombre total de ticks
    uint16_t diff[2];                      // difficulte
}   t_part;

typedef enum {
    UPDATE_SCORE,
    WAIT,
    INPUT_AHEAD,
    PLAY,
    INPUT_AFTER,
    IDLE
} STATE;

/// TIMER FUNCTIONS // timers.c
// TIMER 0 8 bits
void    tc0_clock(uint8_t cs02, uint8_t cs01, uint8_t cs00);
void    tc0_mode(uint8_t wgm02, uint8_t wgm01, uint8_t wgm00);
void    tc0_compare_match(uint8_t com0A1, uint8_t com0A0, uint8_t com0B1, uint8_t com0B0);
// TIMER 2 8 bits
void    tc2_clock(uint8_t cs22, uint8_t cs21, uint8_t cs20);
void    tc2_mode(uint8_t wgm22, uint8_t wgm21, uint8_t wgm20);
void    tc2_compare_match(uint8_t com2A1, uint8_t com2A0, uint8_t com2B1, uint8_t com2B0);
// TIMER 1 16 bits
void    tc1_clock(uint8_t cs12, uint8_t cs11, uint8_t cs10);
void    tc1_mode(uint8_t wgm13, uint8_t wgm12, uint8_t wgm11, uint8_t wgm10);
void    tc1_compare_match(uint8_t com1A1, uint8_t com1A0, uint8_t com1B1, uint8_t com1B0);
// TIMER 3 16 bits
void    tc3_clock(uint8_t cs32, uint8_t cs31, uint8_t cs30);
void    tc3_mode(uint8_t wgm33, uint8_t wgm32, uint8_t wgm31, uint8_t wgm30);
void    tc3_compare_match(uint8_t com3A1, uint8_t com3A0, uint8_t com3B1, uint8_t com3B0);
// TIMER 4 16 bits
void    tc4_clock(uint8_t cs42, uint8_t cs41, uint8_t cs40);
void    tc4_mode(uint8_t wgm43, uint8_t wgm42, uint8_t wgm41, uint8_t wgm40);
void    tc4_compare_match(uint8_t com4A1, uint8_t com4A0, uint8_t com4B1, uint8_t com4B0);
// TIMER 5 16 bits
void    tc5_clock(uint8_t cs52, uint8_t cs51, uint8_t cs50);
void    tc5_mode(uint8_t wgm53, uint8_t wgm52, uint8_t wgm51, uint8_t wgm50);
void    tc5_compare_match(uint8_t com5A1, uint8_t com5A0, uint8_t com5B1, uint8_t com5B0);

// MY_LIB_EMBEDDED FUNCTIONS // libebdd.c
void	clear_n_set(vui8 *port, ui8 bit);
void	toogle_bit(vui8 *port, ui8 bit);
void	set_bit(vui8 *port, ui8 bit);
void	clear_bit(vui8 *port, ui8 bit);
void    set_or_clear(vui8 *port, ui8 val, ui8 bit);
ui8     is_bit_set(vui8 *port, ui8 bit);
void	reset_registre(vui8 *reg);

#endif