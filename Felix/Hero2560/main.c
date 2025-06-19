/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chatou <chatou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:42:22 by chatou            #+#    #+#             */
/*   Updated: 2025/06/18 19:00:05 by chatou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"
#include "tetris.h"
// #include "tetris_3pistes.h"
#include "mario.h"
#include "sonic.h"
// #include "mario2.h"
// #include "simpsons.h"
// #include "starwars.h"
// #include "test_partition.h"

vui8 end_note = 0;
vui16 tc0_counter = 0;

void    timers_stop()
{
    TCCR1A = OCR1A = 0;
    TCCR3A = OCR3A = 0;
    TCCR4A = OCR4A = 0;
    TCCR5A = OCR5A = 0;
}

void    tc0_init()
{
    // Configuration de TIMER0 pour la duree des notes
    tc0_clock(0, 1, 1);                     // Prescaler 64
    tc0_mode(0, 1, 0);                      // Mode CTC
    TIMSK0 |= (1 << OCIE0A);                // Activer l'interruption de comparaison
    OCR0A = 100;                            // Valeur de comparaison pour 1 ms
}

void    tc1_init()
{
    // Configuration de TIMER1 pour le PWM (fréquence de la note)
    tc1_clock(0, 1, 0);                     // Prescaler 8
    tc1_mode(1, 1, 1, 0);                   // PWM Fast PWM (ICR1)
    tc1_compare_match(1, 0, 0, 0);          // Clear OC1A sur Compare Match (niveau bas)
    DDRB |= (1 << PB5);                     // OC1A (PB5) en sortie
    ICR1 = 0;                               // Initialiser ICR1 à 0
    OCR1A = 0;                              // Initialiser OCR1A à 0
    
}

void    tc3_init()
{
    // Configuration de TIMER3 pour le PWM (fréquence de la note)
    tc3_clock(0, 1, 0);                     // Prescaler 8
    tc3_mode(1, 1, 1, 0);                   // PWM Fast PWM (ICR3)
    tc3_compare_match(1, 0, 0, 0);          // Clear OC3A sur Compare Match
    DDRE |= (1 << PE3);                     // OC3A (PE3) = D5 en sortie
    ICR3 = 0;
    OCR3A = 0;
}

void    tc4_init()
{
    // Configuration de TIMER4 pour le PWM (fréquence de la note)
    tc4_clock(0, 1, 0);                     // Prescaler 8
    tc4_mode(1, 1, 1, 0);                   // PWM Fast PWM (ICR4)
    tc4_compare_match(1, 0, 0, 0);          // Clear OC4A sur Compare Match (niveau bas)
    DDRH |= (1 << PH3);                     // OC4A (PH3) en sortie
    ICR4 = 0;                               // Initialiser ICR4 à 0
    OCR4A = 0;                              // Initialiser OCR4A à 0
}

void    tc5_init()
{
    // Configuration de TIMER5 pour le PWM (fréquence de la note)
    tc5_clock(0, 1, 0);                     // Prescaler 8
    tc5_mode(1, 1, 1, 0);                   // PWM Fast PWM (ICR5)
    tc5_compare_match(1, 0, 0, 0);          // Clear OC5A sur Compare Match
    DDRL |= (1 << PL3);                     // OC5A (PL3) = D44 en sortie
    ICR5 = 0;
    OCR5A = 0;
}

void    tcs_init()
{
    tc1_init();                         //  TC0 pour la durée des notes
    tc3_init();                         //  TC1 pour la piste 1
    tc4_init();                         //  TC4 pour la piste 2 et 3
    tc5_init();                         //  TC5 pour la piste 4
}

// Fonction pour jouer une note
void play_note_with_timer(ui16 note, ui8 track)
{
    ui16 freq = note;
    
    if (freq == 0)
    {
        // Arrêter le timer correspondant
        if (track == 0) { OCR1A = 0; }
        else if (track == 1) { OCR3A = 0; }
        else if (track == 2) { OCR4A = 0; }
        else if (track == 3) { OCR5A = 0; }
        return;
    }

    uint16_t top = (F_CPU / (16 * freq)) - 1;

    // Configurer le timer correspondant
    if (track == 0)
    {
        ICR1 = top;
        OCR1A = top / 2;
    }
    else if (track == 1)
    {
        ICR3 = top;
        OCR3A = top / 2;
    }
    else if (track == 2)
    {
        ICR4 = top;
        OCR4A = top / 2;
    }
    else if (track == 3)
    {
        ICR5 = top;
        OCR5A = top / 2;
    }


}

void    play_tracks(const t_part *music, ui16 curr_note)
{
    tcs_init();

    ui16 note0 = pgm_read_word(&music->tracks[0].note[curr_note]);
    ui16 note1 = pgm_read_word(&music->tracks[1].note[curr_note]);
    ui16 note2 = pgm_read_word(&music->tracks[2].note[curr_note]);
    ui16 note3 = pgm_read_word(&music->tracks[3].note[curr_note]);
    uart_print_int(curr_note);
    uart_printstr(" \n\r");

    play_note_with_timer(note0, 0);
    uart_printstr("T1: "); uart_print_int(note0); uart_printstr("\n\r");
    play_note_with_timer(note1, 1);
    uart_printstr("T3: "); uart_print_int(note1); uart_printstr("\n\r");
    play_note_with_timer(note2, 2);
    uart_printstr("T4: "); uart_print_int(note2); uart_printstr("\n\r");
    play_note_with_timer(note3, 3);
    uart_printstr("T5: "); uart_print_int(note3); uart_printstr("\n\r");
      
    tc0_counter = 0;
    TCNT2 = 0;
}

ISR(TIMER0_COMPA_vect)
{
    tc0_counter++;

    if (tc0_counter == 300)
    {
        tc0_counter = 0;
        uart_printstr("Tick - note : ");
        end_note = 1; // Indiquer que la note est terminée
    }
}

int main(void)
{
    // Configure les pins comme sorties
    DDRB |= (1 << PB1); // TIMER0
    DDRB |= (1 << PB5); // TIMER1 ---------- D11 ------- OK
    DDRE |= (1 << PE3); // TIMER3 ---------- D5 ------- OK
    DDRH |= (1 << PH3); // TIMER4 ---------- D6 ------- OK
    DDRL |= (1 << PL3); // TIMER5 ---------- D46 ------ OK
    
    uart_init();
    tc0_init();                         //  TC0 pour la durée des notes
    tcs_init();                         //  TC1, TC3, TC4, TC5 pour les pistes
    sei();                              // Activer les interruptions globales       

    const t_part *music = &mario;
    // const t_part *music = &sonic;
    // const t_part *music = &tetris;
    // const t_part *music = &tetris_song;
    // const t_part *music = &starwars;
    // const t_part *music = &simpsons;
    
    // const t_part *music = &test;
    
    ui16 length = pgm_read_word(&music->length);
    ui16 current_time = 0;
    while (1)
    {
        if (end_note)
        {
            play_tracks(music, current_time);
                
            current_time++;
            
            end_note = 0;

            if (current_time >= length)
            {
                current_time = 0; // Réinitialiser le temps actuel
                timers_stop(); // Arrêter les timers
            }
        }
    }

    return 0;
}
