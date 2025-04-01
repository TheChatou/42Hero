/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:47:16 by fcoullou          #+#    #+#             */
/*   Updated: 2025/04/01 13:48:17 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

#define SPEAKER_PIN PB1 // Pin D9 est PB1 sur l'Arduino Uno

// Fréquences des notes
#define NOTE_C4  261
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  329
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  493
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  987
#define NOTE_C6  1046

// Fonction pour jouer une note
void play_note(uint16_t frequency, uint16_t duration_ms)
{
    if (frequency == 0)
    {
        _delay_loop_2(duration_ms / 2); // Pause si la note est 0
        return;
    }
    
    uint16_t period = (1000000 / frequency) * 5;
    uint16_t cycles = duration_ms;

    for (uint16_t i = 0; i < cycles; i++)
    {
        PORTB |= (1 << SPEAKER_PIN);
        _delay_loop_2(period / 2);
        PORTB &= ~(1 << SPEAKER_PIN);
        _delay_loop_2(period / 2);
    }
}

int main(void)
{
    // Configure PB1 comme une sortie
    DDRB |= (1 << SPEAKER_PIN);
    
    // uint16_t notes[] = { 
    //     NOTE_E5, NOTE_E5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_D5, NOTE_C5, NOTE_B4, 
    //     NOTE_A4, NOTE_A4, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_A4,
    //     NOTE_D5, NOTE_F5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_B4
    // };

    // uint16_t notes[] = { 
    //     NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, 
    //     NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, 
    //     NOTE_C6
    // };
    
    // uint16_t notes[] = { 
    //     NOTE_E5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_A4, 
    //     NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_A4,
    //     NOTE_D5, NOTE_F5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_B4
    // };

    // uint16_t durations[] = { 
    //     2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 
    //     2000, 2000, 2000, 2000, 2000, 2000, 2000 
    // };

// // Super Mario
//     uint16_t notes[] = {
//         NOTE_E5, NOTE_E5, 0, NOTE_E5, 0, NOTE_C5, NOTE_E5, 0,
//         NOTE_G5, 0, 0, 0, NOTE_G4, 0, 0, 0,
//         NOTE_C5, 0, 0, NOTE_G4, 0, 0, NOTE_E4, 0,
//         0, NOTE_A4, 0, NOTE_B4, 0, NOTE_B4, NOTE_A4, 0,
//         NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, 0, NOTE_F5, NOTE_G5, 0,
//         NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4, 0, 0, NOTE_C5, 0,
//         0, NOTE_G4, 0, NOTE_E4, 0, NOTE_A4, 0, NOTE_B4,
//         0, NOTE_A4, NOTE_G4, 0, NOTE_E5, 0, NOTE_G5, NOTE_A5,
//         0, NOTE_F5, NOTE_G5, 0, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4
//     };

//     uint16_t durations[] = {
//         150, 150, 150, 150, 150, 150, 150, 150,
//         150, 300, 150, 300, 150, 300, 150, 300,
//         150, 300, 150, 150, 150, 150, 150, 150,
//         150, 150, 150, 150, 150, 150, 150, 150,
//         150, 150, 150, 150, 150, 150, 150, 150,
//         150, 150, 150, 150, 150, 300, 150, 300,
//         150, 300, 150, 150, 150, 150, 150, 150,
//         150, 150, 150, 150, 150, 150, 150, 150,
//         150, 150, 150, 150, 150, 150, 150, 150
//     };

// Tetris
    uint16_t notes[] = {
        NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4,
        NOTE_A4, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5,
        NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_A4,
        NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A5, NOTE_A5, NOTE_A5,
        NOTE_G5, NOTE_F5, NOTE_E5, NOTE_C5, NOTE_E5, NOTE_D5,
        NOTE_C5, NOTE_B4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5,
        NOTE_C5, NOTE_A4, NOTE_A4, NOTE_A4
    };

    uint16_t durations[] = {
        300, 150, 300, 150, 300, 300,
        300, 150, 300, 300, 150, 300,
        300, 150, 300, 300, 300, 300,
        300, 150, 300, 300, 150, 300,
        300, 150, 300, 300, 150, 300,
        300, 150, 300, 300, 150, 300,
        300, 150, 300, 300
    };
    
    while (1)
    {
        for (size_t i = 0; i < sizeof(notes) / sizeof(notes[0]); i++)
        {
            play_note(notes[i], durations[i] / 2);
            _delay_ms(50);
        }
        _delay_ms(200);
    }

    return 0;
}
