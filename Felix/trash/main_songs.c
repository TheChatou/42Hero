/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chatou <chatou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:47:16 by fcoullou          #+#    #+#             */
/*   Updated: 2025/04/02 13:48:55 by chatou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

#define SPEAKER_PIN PB1 // Pin D9 est PB1 sur l'Arduino Uno

// Fréquences des notes
#define N_00  0
#define N_C3  131
#define N_c3  139
#define N_D3  147
#define N_d3  156
#define N_E3  165
#define N_F3  175
#define N_f3  185
#define N_G3  196
#define N_g3  208
#define N_A3  220
#define N_a3  233
#define N_B3  247
#define N_C4  261
#define N_c4  277
#define N_D4  294
#define N_d4  311
#define N_E4  329
#define N_F4  349
#define N_f4  370
#define N_G4  392
#define N_g4  415
#define N_A4  440
#define N_a4  466
#define N_B4  493
#define N_C5  523
#define N_c5  554
#define N_D5  587
#define N_d5  622
#define N_E5  659
#define N_F5  698
#define N_f5  740
#define N_G5  784
#define N_g5  831
#define N_A5  880
#define N_a5  932
#define N_B5  987
#define N_C6  1046

#define T_1_8  125
#define T_1_16 62
#define T_1_4  250
#define T_1_2  500
#define T_3_4  750
#define T_1__  1000

// Fonction pour jouer une note
void play_note(uint16_t frequency, uint16_t duration_ms)
{
    if (frequency == 0)
    {
        PORTB &= ~(1 << SPEAKER_PIN); // S'assurer que le haut-parleur est éteint
        _delay_loop_2(duration_ms); // Pause si la note est 0
        return;
    }
    
    uint16_t period = (1000000 / frequency);
    uint16_t cycles = duration_ms;

    for (uint16_t i = 0; i < cycles; i++)
    {
        PORTB |= (1 << SPEAKER_PIN);
        _delay_loop_2(period);
        PORTB &= ~(1 << SPEAKER_PIN);
        _delay_loop_2(period);
    }
}

int main(void)
{
    // Configure PB1 comme une sortie
    DDRB |= (1 << SPEAKER_PIN);
    
// // Super Mario Bros Theme - Ajusté avec un tempo plus précis
//     uint16_t notes[] = {
//         N_E5, N_E5, N_00, N_E5, N_00, N_C5, N_E5, N_00,
//         N_G5, N_00, N_00, N_00, N_G4, N_00, N_00, N_00,
//         N_C5, N_00, N_00, N_G4, N_00, N_00, N_E4, N_00,
//         N_00, N_A4, N_00, N_B4, N_00, N_B4, N_A4, N_00,
//         N_G4, N_E5, N_G5, N_A5, N_00, N_F5, N_G5, N_00,
//         N_E5, N_C5, N_D5, N_B4, N_00, N_00, N_C5, N_00,
//         N_00, N_G4, N_00, N_E4, N_00, N_A4, N_00, N_B4,
//         N_00, N_A4, N_G4, N_00, N_E5, N_00, N_G5, N_A5,
//         N_00, N_F5, N_G5, N_00, N_E5, N_C5, N_D5, N_B4,
//         // Suite
//         N_00, N_G5, N_F5, N_E5, N_D5, N_C5, N_00, N_E4, N_G4,
//         N_A4, N_F4, N_G4, N_00, N_E4, N_C4, N_D4, N_B3, N_G3,
//         N_00, N_E5, N_G5, N_A5, N_F5, N_G5, N_00, N_E5, N_C5, N_D5,
//         N_B4, N_G4, N_00, N_E4, N_C4, N_D4, N_B3, N_A3, N_G3,
//         N_G4, N_A4, N_G4, N_00, N_E4, N_G4, N_A4, N_F4, N_G4,
//         N_00, N_E4, N_C4, N_D4, N_B3, N_G3, N_E3, N_C3, N_A3
//     };
    
//     uint16_t durations[] = {
//         T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8,
//         T_1_8, T_1_4, T_1_8, T_1_4, T_1_8, T_1_4, T_1_8, T_1_4,
//         T_1_8, T_1_4, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8,
//         T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8,
//         T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8,
//         T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_4, T_1_8, T_1_4,
//         T_1_8, T_1_4, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8,
//         T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8,
//         T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8,
//         // Suite
//         T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_4, T_1_8, T_1_8,
//         T_1_8, T_1_8, T_1_8, T_1_4, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8,
//         T_1_4, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_4, T_1_8, T_1_8, T_1_8,
//         T_1_8, T_1_8, T_1_4, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8,
//         T_1_8, T_1_8, T_1_4, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8,
//         T_1_4, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8, T_1_8
//     };

    // Tetris Theme - Réarrangé pour refléter la mélodie originale
    uint16_t notes[] = {
        N_E5, N_B4, N_C5, N_D5, N_C5, N_B4, N_A4, N_A4,
        N_C5, N_E5, N_D5, N_C5, N_B4, N_C5, N_D5, N_E5,
        N_C5, N_A4, N_A4, N_A4, N_B4, N_C5, N_D5, N_F5,
        N_A5, N_G5, N_F5, N_E5, N_C5, N_E5, N_D5, N_C5,
        N_B4, N_B4, N_C5, N_D5, N_E5, N_C5, N_A4, N_A4
    };

    uint16_t durations[] = {
        T_1_4, T_1_8, T_1_8, T_1_4, T_1_8, T_1_8, T_1_4, T_1_8,
        T_1_8, T_1_4, T_1_8, T_1_8, T_1_4, T_1_8, T_1_8, T_1_4,
        T_1_4, T_1_4, T_1_8, T_1_8, T_1_8, T_1_8, T_1_4, T_1_8,
        T_1_8, T_1_4, T_1_8, T_1_8, T_1_4, T_1_8, T_1_8, T_1_4,
        T_1_4, T_1_8, T_1_8, T_1_4, T_1_4, T_1_4, T_1_4, T_1_4
    };

    
    while (1)
    {
        for (size_t i = 0; i < sizeof(notes) / sizeof(notes[0]); i++)
        {
            play_note(notes[i], durations[i]);
            _delay_ms(100);
        }
        _delay_ms(2000);
    }

    return 0;
}
