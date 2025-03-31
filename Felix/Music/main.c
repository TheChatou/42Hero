/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:47:16 by fcoullou          #+#    #+#             */
/*   Updated: 2025/03/31 18:12:33 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

#define SPEAKER_PIN PB1 // Pin D9 est PB1 sur l'Arduino Uno

// Fréquences des notes
#define NOTE_C4  261
#define NOTE_D4  294
#define NOTE_E4  329
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  493
#define NOTE_C5  523
#define NOTE_D5  587

// Fonction pour jouer une note
void play_note(uint16_t frequency, uint16_t duration_ms)
{
    uint16_t period = 1000000 / frequency; // période en microsecondes
    uint16_t cycles = frequency * duration_ms / 1000; // nombre de cycles pour la durée donnée

    for (uint16_t i = 0; i < cycles; i++)
    {
        PORTB |= (1 << SPEAKER_PIN);  // Mise à HIGH pour activer le buzzer
        _delay_loop_2(period / 2);    // Moitié de la période
        PORTB &= ~(1 << SPEAKER_PIN); // Mise à LOW pour désactiver le buzzer
        _delay_loop_2(period / 2);    // L'autre moitié de la période
    }
}

int main(void)
{
    // Configure PB1 comme une sortie (D9)
    DDRB |= (1 << SPEAKER_PIN);

    ui16    notes[] = { NOTE_E4, NOTE_E4, NOTE_E4, NOTE_C4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_C4,
        NOTE_E4, NOTE_E4, NOTE_E4, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4 };

    ui16    dura[] = { 500, 200, 200, 200, 500, 200, 200, 200, 500, 200, 200, 200, 500, 200, 200, 200 };
            
    while (1)
    {
        for ( int i = 0; i < 16; i++)
        {
            play_note(notes[i], dura[i]);
            _delay_ms(100);
        }
        _delay_ms(1000);
    }

    return 0;
}