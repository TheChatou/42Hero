#include "init.h"
#include "parts.h"



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


void    init()
{
    DDRB |= (1 << PB1); // TIMER0
    DDRB |= (1 << PB5); // TIMER1 ---------- D11 ------- OK
    DDRE |= (1 << PE3); // TIMER3 ---------- D5 ------- OK
    DDRH |= (1 << PH3); // TIMER4 ---------- D6 ------- OK
    DDRL |= (1 << PL3); // TIMER5 ---------- D46 ------ OK

    DDRA |= (1 << PA4) | (1 << PA0) | (1 << PA2) | (1 << PA6); //leds_exp
    DDRC &= ~(0b01010101); //buttons
    DDRL &= ~(0b01010101); //buttons
    PORTA = 0;
    PORTC |= 0b01010101; //buttons
    PORTL |= 0b01010101; // buttons

    tc0_init();
    tc1_init();
    tc3_init();
    tc4_init();
    tc5_init();

}