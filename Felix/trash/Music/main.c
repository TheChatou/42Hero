/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chatou <chatou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:42:22 by chatou            #+#    #+#             */
/*   Updated: 2025/04/21 23:54:06 by chatou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"
#include "tetris.h"
#include "mario.h"

#define SPEAKER_PIN PB1 // Pin D9 est PB1 sur l'Arduino Uno

vui8 end_note = 0;
vui16 tc2_counter = 0; // Compteur de débordements pour TIMER2
vui8 curr_note = 0; // Note actuelle à jouer
volatile t_notes current; 

void    timers_stop()
{
    // Arrêter le TIMER1
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
    ICR1 = 0;                            // Initialiser ICR1 à 0
    OCR1A = 0;                           // Initialiser OCR1A à 0
    
}

void    tc2_init()
{
    // Configuration de TIMER2 pour la durée des notes
    tc2_clock(0, 0, 1);                     // Prescaler 64
    tc2_mode(0, 1, 0);                      // Mode CTC
    tc2_compare_match(0, 0, 0, 0);          // Déconnecter OC2A et OC2B

    TIMSK2 |= (1 << OCIE2A);                // Activer l'interruption de comparaison
    OCR2A = 249;                            // Valeur de comparaison pour 1 ms
}

// Fonction pour jouer une note
void play_note_with_timer(uint8_t note_index)
{
    tc1_init();
    tc2_init();
    
    // memcpy_P((t_notes *)&current, &tetris.notes[note_index], sizeof(t_notes));

    memcpy_P((t_notes *)&current, &mario.notes[note_index], sizeof(t_notes));

    if (current.count == 0)
    {
        timers_stop(); // Silence
        return;
    }

    static vui8 current_alt_note = 0;

    // uart_print_int(note_index);
    // uart_printstr(" - ");
    // uart_print_int(current.freqs[current_alt_note]);
    // uart_printstr(" - Note ");
    // uart_print_int(current.count);
    // uart_printstr(" - Count\r\n");

    // Calculer ICR1 pour générer la bonne fréquence (Fast PWM avec ICR1 comme TOP)
    ui16 frequency = current.freqs[current_alt_note];
    ui16 top = ((F_CPU / (8 * frequency)) - 1) % 65535; // Prescaler 8
    ICR1 = top;

    uart_printstr("TOP : ");
    uart_print_ui16(top);
    uart_printstr("\r\n");
    
    OCR1A = top / 2; // 50% duty cycle

    // Redémarrer le compteur de Timer2
    tc2_counter = 0;
    TCNT2 = 0;
}

ISR(TIMER2_COMPA_vect)
{
    tc2_counter++;
    
    // uart_print_ui16(current.count);
    if (current.count > 1)
    {
        // Alterner entre les fréquences si plusieurs notes sont présentes
        static vui8 current_alt_note = 0;
        current_alt_note = (current_alt_note + 1) % current.count;

        // Calculer ICR1 pour générer la bonne fréquence (Fast PWM avec ICR1 comme TOP)
        ui16 frequency = current.freqs[current_alt_note];
        ui16 top = ((F_CPU / (16 * frequency)) - 1) % 65535; // Prescaler 8
        ICR1 = top;

        // uart_printstr("TOP : ");
        // uart_print_ui16(top);
        // uart_printstr("\r\n");
        
        OCR1A = top / 2; // 50% duty cycle
    }

    if (tc2_counter >= 250)
    {
        tc2_counter = 0;
        end_note = 1; // Indiquer que la note est terminée
    }
}

int main(void)
{
    // Configure PB1 comme une sortie
    DDRB |= (1 << SPEAKER_PIN);

    uart_init();
    tc1_init();
    tc2_init();
    sei(); // Activer les interruptions globales       

    
    int curr_note = 0; // Quart de temps actuel
    while (1)
    {
        if (end_note)
        {
            play_note_with_timer(curr_note);
            curr_note = (curr_note + 1) % TEMPS_MAX_2;

            // uart_print_int(curr_note);
            // uart_printstr(" - Note \r\n");
            
            end_note = 0;
        }
    }

    return 0;
}
