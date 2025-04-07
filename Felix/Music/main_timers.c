/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:47:16 by fcoullou          #+#    #+#             */
/*   Updated: 2025/04/07 17:25:05 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

#define SPEAKER_PIN PB1 // Pin D9 est PB1 sur l'Arduino Uno

vui8 play_note = 0;
vui8 end_note = 0;
vui16 timer2_overflow_count = 0; // Compteur de débordements pour TIMER2

// Correspondance entre noms de notes et fréquences
int get_frequency(const char* note)
{
    if (strcmp(note, "C3") == 0) return C3;
    if (strcmp(note, "c3") == 0) return c3;
    if (strcmp(note, "D3") == 0) return D3;
    if (strcmp(note, "d3") == 0) return d3;
    if (strcmp(note, "E3") == 0) return E3;
    if (strcmp(note, "F3") == 0) return F3;
    if (strcmp(note, "f3") == 0) return f3;
    if (strcmp(note, "G3") == 0) return G3;
    if (strcmp(note, "g3") == 0) return g3;
    if (strcmp(note, "A3") == 0) return A3;
    if (strcmp(note, "a3") == 0) return a3;
    if (strcmp(note, "B3") == 0) return B3;
    if (strcmp(note, "C4") == 0) return C4;
    if (strcmp(note, "c4") == 0) return c4;
    if (strcmp(note, "D4") == 0) return D4;
    if (strcmp(note, "d4") == 0) return d4;
    if (strcmp(note, "E4") == 0) return E4;
    if (strcmp(note, "F4") == 0) return F4;
    if (strcmp(note, "f4") == 0) return f4;
    if (strcmp(note, "G4") == 0) return G4;
    if (strcmp(note, "g4") == 0) return g4;
    if (strcmp(note, "A4") == 0) return A4;
    if (strcmp(note, "a4") == 0) return a4;
    if (strcmp(note, "B4") == 0) return B4;
    if (strcmp(note, "C5") == 0) return C5;
    if (strcmp(note, "c5") == 0) return c5;
    if (strcmp(note, "D5") == 0) return D5;
    if (strcmp(note, "d5") == 0) return d5;
    if (strcmp(note, "E5") == 0) return E5;
    if (strcmp(note, "F5") == 0) return F5;
    if (strcmp(note, "f5") == 0) return f5;
    if (strcmp(note, "G5") == 0) return G5;
    if (strcmp(note, "g5") == 0) return g5;
    if (strcmp(note, "A5") == 0) return A5;
    if (strcmp(note, "a5") == 0) return a5;
    if (strcmp(note, "B5") == 0) return B5;
    if (strcmp(note, "C6") == 0) return C6;
    if (strcmp(note, "N0") == 0) return N0;
    if (strcmp(note, "--") == 0) return N0; // Silence
    
    return 0;
}

void    print_t_part(t_part *p)
{
    for (int i = 0; i < TEMPS_MAX; i++)
    {
        uart_print_int(i + 1);
        uart_printstr(" - ");
        uart_print_ui16(p->notes[i].frequency);
        uart_printstr(" Hz, Durée: ");
        uart_print_ui16(p->notes[i].duration);
        uart_printstr(" ms\r\n");
    }
}

// Fonction pour parser les données de la partition depuis une chaîne
void parse_partition_from_string(const char** data, t_part *p)
{
    int i = 0;
        
    while (i < NOTES_MAX)
    {
        char note[3] = { data[i][0], data[i][1], '\0' };
        int freq = get_frequency(note);

        int j = 4;
        int t = 0;
        while (data[i][j] != '\0')
        {
            if (data[i][j] == '|')
            {
                j++;
                continue;
            }
            else if (data[i][j] == 'X')
            {
                p->notes[t].duration = T_1_4;
                p->notes[t].frequency = freq;
            }
            t++;
            j++;
        }
        i++;
    }
    // print_t_part(p);
}

// // Fonction pour jouer une note
// void play_note(uint16_t frequency, uint16_t duration_ms)
// {
//     if (frequency == 0)
//     {
//         PORTB &= ~(1 << SPEAKER_PIN); // S'assurer que le haut-parleur est éteint
//         _delay_loop_2(duration_ms); // Pause si la note est 0
//         return;
//     }
    
//     uint16_t period = (1000000 / frequency);
//     uint16_t cycles = duration_ms;

//     for (uint16_t i = 0; i < cycles; i++)
//     {
//         PORTB ^= (1 << SPEAKER_PIN);
//         _delay_loop_2(period);
//     }
// }

void    timers_stop()
{
    // Arrêter le TIMER1
    TCCR1A = 0;
    OCR1A = 0;
}

void    timers_init()
{
    // Configuration de TIMER1 pour le PWM (fréquence de la note)
    tc1_clock(0, 0, 1);                     // Prescaler 8
    tc1_mode(1, 0, 1, 1);                   // PWM Phase Correct (OCR1A)
    tc1_compare_match(1, 0, 1, 0);          // Set OC1A on Compare Match, Clear OC1A at BOTTOM

    // Configuration de TIMER2 pour la durée des notes
    TCCR2A = 0;                             // Mode normal
    TCCR2B = (1 << CS22) | (1 << CS21);     // Prescaler 256
    TIMSK2 = (1 << TOIE2);                  // Activer l'interruption d'overflow
}

// Fonction pour jouer une note
void play_note_with_timer(ui16 frequency, ui16 duration_ms)
{
    if (frequency == 0)
    {
        timers_stop();
    }
    else
    {        
        // Calcul de la période pour TIMER1 (PWM)
        ui16 period = (F_CPU / 8 / frequency);
        OCR1A = period;
    }
    
    // Configurer TIMER2 pour la durée
    timer2_overflow_count = 0; // Réinitialiser le compteur d'overflow
    ui16 total_ovflow = (F_CPU / 256) * duration_ms / 1000; // Ticks pour la durée
    TCNT2 = 0; // Compteur initial
    end_note = total_ovflow; // Réinitialiser l'indicateur
 
}

ISR(TIMER2_OVF_vect)
{
    timer2_overflow_count++;

    // Vérifier si la durée de la note est écoulée
    if (timer2_overflow_count >= end_note)
    {
        timers_stop(); // Arrêter le timer
        play_note = 1; // Indiquer que la note est terminée
    }
}

int main(void)
{
    // Configure PB1 comme une sortie
    DDRB |= (1 << SPEAKER_PIN);

    uart_init();
    timers_init();
    sei(); // Activer les interruptions globales

    const char *tetris_data[] = {
    "A5 |----|----|----|----|----|----|----|----|----|X---|----|----|----|----|----|----|----|",
    "G5 |----|----|----|----|----|----|----|----|----|--X-|----|----|----|----|----|----|----|",
    "F5 |----|----|----|----|----|----|----|----|---X|---X|----|----|----|----|----|----|----|",
    "E5 |Xx--|----|----|X---|----|--X-|----|----|----|----|X---|X---|----|--X-|----|----|----|",
    "D5 |----|X---|----|--X-|----|X---|----|----|-X--|----|----|--X-|----|X---|----|----|----|",
    "C5 |---X|--X-|---X|---X|---X|----|X---|----|----|----|---X|---X|---X|----|X---|----|----|",
    "B4 |--X-|---X|----|----|X---|----|----|----|----|----|----|----|X-X-|----|----|----|----|",
    "A4 |----|----|X-X-|----|----|----|--X-|X---|----|----|----|----|----|----|----|XXXX|X---|" };
    //   1    5    9    13   17   21   25   29   33   37   41   45   49   53   57   61   65

    t_part p = {0}; // Initialisation de la partition
    
    
    // Partition lue depuis la chaîne de caractères
    parse_partition_from_string(tetris_data, &p);

    while (1)
    {
        if (play_note)
        {
            // Passer à la note suivante
            play_note_with_timer(p.notes[play_note].frequency / 2, p.notes[play_note].duration * 2);
            play_note++;

            // Réinitialiser l'indicateur
            end_note = 0;

            // Revenir au début si toutes les notes ont été jouées
            if (play_note >= TEMPS_MAX)
            {
                play_note = 0;
            }
        }
    }

    return 0;
}
