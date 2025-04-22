/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:42:22 by chatou            #+#    #+#             */
/*   Updated: 2025/04/22 16:56:47 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"
#include "tetris1.h"
#include "mario.h"
#include "Notes_tab.h"

#define SPEAKER_PIN PB1 // Pin D9 est PB1 sur l'Arduino Uno

vui8 end_note = 0;
vui16 tc2_counter = 0; // Compteur de débordements pour TIMER2
vui8 curr_note = 0; // Note actuelle à jouer
volatile t_notes current; 
volatile unsigned char char_index = 0;

void    timers_stop()
{
    TCCR1A = 0;
    OCR1A = 0;
}

void    tc1_init()
{
    // Configuration de TIMER1 pour le PWM (fréquence de la note)
    tc1_clock(0, 1, 0);                     // Prescaler 8
    tc1_mode(1, 1, 1, 0);                   // PWM Fast PWM (ICR1)
    tc1_compare_match(1, 0, 0, 0);          // Set OC1A on Compare Match, Clear OC1A at BOTTOM    DDRB |= (1 << SPEAKER_PIN); // OC1A (PB1) en sortie
    DDRB |= (1 << SPEAKER_PIN);             // OC1A (PB1) en sortie
    ICR1 = 0;                               // Initialiser ICR1 à 0
    OCR1A = 0;                              // Initialiser OCR1A à 0
    
}

void    tc2_init()
{
    // Configuration de TIMER2 pour la durée des notes
    tc2_clock(1, 1, 0);                     // Prescaler 64
    tc2_mode(0, 1, 0);                      // Mode CTC
    tc2_compare_match(0, 0, 0, 0);          // Déconnecter OC2A et OC2B

    TIMSK2 |= (1 << OCIE2A);                // Activer l'interruption de comparaison
    OCR2A = 100;                            // Valeur de comparaison pour 1 ms
}

ui16    polyphony(const int *freqs, int count)
{
    int i;
    int sum = 0;
    if (count == 0)
        return 0; // Eviter la division par zéro

    if (count == 1)
        return freqs[0]; // Si une seule note, retourner sa fréquence
        
    for (i = 0; i < count; i++)
    {
        sum += freqs[i];
    }
    return sum / count; // Retourne la fréquence moyenne
}

// Fonction pour jouer une note
void play_note_with_timer(const t_part *music, uint8_t note_index)
{
    memcpy_P((t_notes *)&current, &music->notes[note_index], sizeof(t_notes));

    if (current.count == 0)
    {
        timers_stop();                      // Silence
        return;
    }

    tc1_init();
    tc2_init();
    
    static vui8 current_alt_note = 0;

    // Calculer ICR1 pour générer la bonne fréquence (Fast PWM avec ICR1 comme TOP)
    ui16 frequency = current.freqs[current_alt_note];
    // ui16 frequency = polyphony((const int *)current.freqs, (int)current.count);
    ui16 top = ((F_CPU / (16 * frequency)) - 1);
    ICR1 = top;
    OCR1A = top / 2;                                // 50% duty cycle

    // Redémarrer le compteur de Timer2
    tc2_counter = 0;
    TCNT2 = 0;
}

ISR(TIMER2_COMPA_vect)
{
    tc2_counter++;
    
    if (current.count > 1 && tc2_counter % 50 == 0)
    {
        // Alterner entre les fréquences si plusieurs notes sont présentes
        static vui8 current_alt_note = 0;
        current_alt_note = (current_alt_note + 1) % current.count;

        // Calculer ICR1 pour générer la bonne fréquence (Fast PWM avec ICR1 comme TOP)
        ui16 frequency = current.freqs[current_alt_note];
        ui16 top = ((F_CPU / (16 * frequency)) - 1);
        ICR1 = top;
        
        OCR1A = top / 2;
    }

    if (tc2_counter == 250)
    {
        tc2_counter = 0;
        end_note = 1;                       // Indiquer que la note est terminée
    }
}

// int main(void)
// {
//     // Configure PB1 comme une sortie
//     DDRB |= (1 << SPEAKER_PIN);

//     uart_init();
  
//     uart_tx('T');
    
//     tc1_init();
//     tc2_init();
//     sei();                              // Activer les interruptions globales       

//     // const t_part *music = &mario;    // Pointer vers la musique à jouer
//     const t_part *music = &tetris1;     // Pointer vers la musique à jouer
    

//     int curr_note = 0;                  // Quart de temps actuel
//     while (1)
//     {
//         if (end_note)
//         {
//             play_note_with_timer(music, curr_note);
//             curr_note = (curr_note + 1) % TEMPS_MAX_2;
            
//             end_note = 0;
//         }
//     }

//     return 0;
// }

int main(void)
{
    // Configure PB1 comme une sortie
    // DDRB |= (1 << SPEAKER_PIN);

    uart_init();
  
    // uart_tx('T');
    while (1)
    {
        uart_tx('A');
        _delay_ms(1000);
    }

    return 0;
}
