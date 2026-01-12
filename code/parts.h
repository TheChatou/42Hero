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

//struct describing a track (one per timer), contains the series of frequencies to be played
typedef struct t_track
{
    uint16_t    note[MUSIC_MAX_LEN];
}   t_track;

/// @brief struct describing a song contains :
//4 t_track, one per note timer
//4 corresponding led pattern to be displayed and check against button inputs
// the tempo == number of ticks of the master timer before switching to next note
typedef struct
{
    t_track tracks[4];       
    uint8_t led[MUSIC_MAX_LEN];           
    uint16_t tempo;                     
    uint16_t length;                    
    uint16_t diff[2];                      
}   t_part;



#endif