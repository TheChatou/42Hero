/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:47:16 by fcoullou          #+#    #+#             */
/*   Updated: 2025/03/31 17:12:56 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

#define SPEAKER_PIN PB1  // Broche pour le haut-parleur
#define F_CPU 16000000UL // Fréquence de l'horloge (16 MHz)

void _delay_ms_custom(uint16_t ms)
{
    while (ms--)
        _delay_loop_2(4000); // 4000 itérations = environ 1ms à 16 MHz
}

// Convertit une note MIDI en fréquence
int midiToFrequency(int midiNote)
{
    return (int)(pow(2, (midiNote - 69) / 12.0) * 440);
}

// Joue une note avec une certaine durée
void play_note(int note, int duration)
{
    if (note > 0)
    {
        int frequency = midiToFrequency(note);
        int period = 1000000 / frequency; // Période en µs
        int cycles = (duration * 1000) / (2 * period); // Nombre de cycles de la note

        for (int i = 0; i < cycles; i++)
        {
            PORTB ^= (1 << SPEAKER_PIN); // Inverse le signal sur PB1 (haut-parleur)
            _delay_ms_custom(period / 1000); // Temps pour chaque demi-cycle
        }
    }
    _delay_ms_custom(duration * 1.3); // Petit silence entre les notes
}

// Joue un morceau en suivant un tableau de notes et de durées
void playSong(const uint8_t *song, int length)
{
    for (int i = 0; i < length; i += 2)
    {
        play_note(song[i], song[i + 1] * 50); // Note + durée
    }
}

void setup()
{
    DDRB |= (1 << SPEAKER_PIN); // Configure la pin comme sortie
}

void loop()
{
    static const uint8_t part1[] = {76, 12, 76, 12, 20, 12, 76, 12, 20, 12, 72, 12, 76, 12, 20, 12, 79, 12, 20, 36, 67, 12, 20, 36};

    // Joue la musique en enchaînant les parties
    playSong(part1, sizeof(part1)); 
    _delay_ms_custom(5000); // Pause avant de recommencer
}

int main()
{
    setup(); // Initialisation
    while (1)
    {
        loop(); // Exécution du loop
    }
    return 0;
}