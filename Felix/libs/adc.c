/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:37:48 by fcoullou          #+#    #+#             */
/*   Updated: 2025/03/15 20:17:13 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void    set_adc_Prescaler(ui8 adps2, ui8 adps1, ui8 adps0)
{
    set_or_clear(&ADCSRA, adps2, ADPS2);
    set_or_clear(&ADCSRA, adps1, ADPS1);
    set_or_clear(&ADCSRA, adps0, ADPS0);
}

void    set_ADCSRA_reg(ui8 aden, ui8 adate, ui8 adif, ui8 adie)
{
    set_or_clear(&ADCSRA, aden, ADEN);
    set_or_clear(&ADCSRA, adate, ADATE);
    set_or_clear(&ADCSRA, adif, ADIF);
    set_or_clear(&ADCSRA, adie, ADIE);
}

void    set_adc_Chanel(ui8 mux3, ui8 mux2, ui8 mux1, ui8 mux0)
{
    set_or_clear(&ADMUX, mux3, MUX3);
    set_or_clear(&ADMUX, mux2, MUX2);
    set_or_clear(&ADMUX, mux1, MUX1);
    set_or_clear(&ADMUX, mux0, MUX0);
}

void    set_adc_Voltage(ui8 refs1, ui8 refs0)
{
    set_or_clear(&ADMUX, refs1, REFS1);
    set_or_clear(&ADMUX, refs0, REFS0);
}

ui8 adc_read()
{
    set_bit(&ADCSRA, ADSC);             // Démarrer une nouvelle conversion
    
    while (is_bit_set(&ADCSRA, ADSC));  // Attendre la fin de la conversion
    
    return ADCH;                        // Retourner la valeur 8 bits (car ADLAR = 1)
}

ui16 adc_read_16()
{
    set_bit(&ADCSRA, ADSC);                 // Démarrer une nouvelle conversion
    
    while (is_bit_set(&ADCSRA, ADSC));      // Attendre la fin de la conversion
    
    return ADC;                             // Retourner la valeur 10 bits (car ADLAR = 0)
}

void    adc_pot_init()
{
    clear_bit(&DDRC, _POT);             // Configuration du potentiometre en entrée
    
    set_bit(&ADMUX, ADLAR);           // Configuré pour lire 10 bits sur ADCH & ADCL
    set_adc_Chanel(0, 0, 0, 0);         // 0000 : "ADC0 (PC0)"
    set_adc_Voltage(0, 1);              // 01 : "AVCC with external capacitor at AREF pin"
    set_ADCSRA_reg(1, 1, 0, 0);         // Activation de l'ADC et de l'interruption
    set_adc_Prescaler(0, 1, 1);
}

void    adc_ldr_init()
{
    clear_bit(&DDRC, _LDR);             // Configuration du potentiometre en entrée
    
    clear_bit(&ADMUX, ADLAR);           // Configuré pour lire 10 bits sur ADCH & ADCL
    set_adc_Chanel(0, 0, 0, 1);         // 0001 : "ADC1 (PC1)"
    set_adc_Voltage(0, 1);              // 01 : "AVCC with external capacitor at AREF pin"
    set_ADCSRA_reg(1, 1, 0, 0);
    set_adc_Prescaler(0, 1, 1);
}

void    adc_temp_init()
{
    clear_bit(&DDRC, _TEMP);             // Configuration du potentiometre en entrée
    
    clear_bit(&ADMUX, ADLAR);           // Configuré pour lire 10 bits sur ADCH & ADCL
    set_adc_Chanel(0, 0, 1, 0);         // 0010 : "ADC2 (PC2)"
    set_adc_Voltage(0, 1);              // 01 : "AVCC with external capacitor at AREF pin"
    set_ADCSRA_reg(1, 1, 0, 0);
    set_adc_Prescaler(0, 1, 1);
}

void    adc_intemp_init()
{
    clear_bit(&ADMUX, ADLAR);           // Configuré pour lire 10 bits sur ADCH & ADCL
    set_adc_Chanel(1, 0, 0, 0);         // 1000 : "ADC8 (int temp)"
    set_adc_Voltage(1, 1);              // 11 : "Internal 1.1V Voltage Reference with external capacitor at AREF pin"
    set_ADCSRA_reg(1, 0, 0, 0);
    set_adc_Prescaler(1, 1, 1);         // F_CPU / 128 
}


// ============================================================== ADC (Convertisseur Analogique-Numérique) ============================================================= //
// //////////////////// ADC REGISTERS ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ADMUX : 8 bits ----------------------------------------------
// | REFS1 | REFS0 | ADLAR | ---- | MUX3 | MUX2 | MUX1 | MUX0 |
// |   7   |   6   |   5   |  4   |   3  |   2  |   1  |   0  |
//     |       |       |              +- - - +- - - +- - - +----> Sélection du canal d'entrée ADC (MUX3:0)
//     |       |       +----------------> Justification du résultat (0 = Droite, 1 = Gauche)
//     + - - - +------------------------> Référence de tension (00 = AREF, 01 = AVcc, 11 = 1.1V interne)
// 
// ADCSRA : 8 bits --------------------------------------------
// | ADEN | ADSC | ADATE | ADIF | ADIE | ADPS2 | ADPS1 | ADPS0 |
// |   7  |   6  |   5   |   4  |   3  |   2   |   1   |   0   |
//     |      |      |       |      |      +- - - -+ - - - +----> Division du prescaler ADC (ADPS2:0)
//     |      |      |       |      +-------------------> Activation interruption ADC
//     |      |      |       +--------------------------> Drapeau d'interruption ADC (1 = Conversion terminée)
//     |      |      +----------------------------------> Auto-Trigger (1 = Activé)
//     |      +-----------------------------------------> Lancer conversion ADC (1 = Start)
//     +------------------------------------------------> Activer ADC (1 = Activé)
// 
// ADCSRB : 8 bits --------------------------------------------
// | ---- | ---- | ---- | ---- | ---- | ACME | ---- | ADTS |
// |   7  |   6  |   5  |   4  |   3  |   2  |   1  |  0-2 |
//                                 |      + - - - - - - +----> Source du déclenchement automatique (ADTS2:0)
//                                 +-------------------------> Comparator Analogique Multiplexé (1 = Activé)
// 
// ADCH & ADCL : 16 bits --------------------------------------
// | ADCH (8 bits) | ADCL (8 bits) |
// |  15 - 8       |  7 - 0        |
//         Résultat de la conversion ADC (10 bits significatifs, selon ADLAR)
//  Qu'est-ce que ADLAR ?
// ADLAR est un bit de configuration du registre ADMUX qui permet de choisir la justification du résultat de la conversion ADC.
// Comment lire la valeur de la conversion ADC ?
// - Si ADLAR = 0, la valeur de la conversion est stockée dans les bits ADCH (8 bits) et ADCL (2 bits de poids faible)
// - Si ADLAR = 1, la valeur de la conversion est stockée dans les bits ADCH (2 bits de poids fort) et ADCL (8 bits)
//  EN GROS :   ADLAR = 0 (lecture 10 bits sur ADCL & ADCH)
//              ADLAR = 1 (lecture 8 bits sur ADCH)
//
// ADLAR 0 //
// | ADCH (2 bits) | ADCL (8 bits) |            -- ui16 result = (ADCH << 8) | ADCL;
// |   ------98    |   76543210    |            -- ui8 result = (ADCH << 2) | (ADCL >> 6);
//
// ADLAR 1 //
// | ADCH (8 bits) | ADCL (2 bits) |            -- ui16 result = (ADCH << 2) | (ADCL >> 6);
// |   98765432    |   10------    |            -- ui8 result = ADCH; (8 bits significatifs)
// 
// //////////////////// ADC MODES ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// *** Sélection de la source d'horloge (ADPS2, ADPS1, ADPS0)
// ----------------------------------------------------------
// | ADPS2 | ADPS1 | ADPS0 | Division F_CPU                 |
// |------|------|------|-----------------------------------|
// |  0   |  0   |  0   | Pas de conversion (ADC désactivé) |
// |  0   |  0   |  1   | F_CPU / 2                         |
// |  0   |  1   |  0   | F_CPU / 4                         |
// |  0   |  1   |  1   | F_CPU / 8                         |
// |  1   |  0   |  0   | F_CPU / 16                        |
// |  1   |  0   |  1   | F_CPU / 32                        |
// |  1   |  1   |  0   | F_CPU / 64                        |
// |  1   |  1   |  1   | F_CPU / 128                       |
// ----------------------------------------------------------
// 0667855716
// *** Sélection du canal d'entrée ADC (MUX3, MUX2, MUX1, MUX0)
// ---------------------------------------------------
// | MUX3 | MUX2 | MUX1 | MUX0 | Canal sélectionné   |
// |------|------|------|------|---------------------|
// |  0   |  0   |  0   |  0   | ADC0 (PC0)          |
// |  0   |  0   |  0   |  1   | ADC1 (PC1)          |
// |  0   |  0   |  1   |  0   | ADC2 (PC2)          |
// |  0   |  0   |  1   |  1   | ADC3 (PC3)          |
// |  0   |  1   |  0   |  0   | ADC4 (PC4)          |
// |  0   |  1   |  0   |  1   | ADC5 (PC5)          |
// |  0   |  1   |  1   |  0   | ADC6 (PC6)          |
// |  0   |  1   |  1   |  1   | ADC7 (PC7)          |
// |  1   |  0   |  0   |  0   | Température interne |
// |  1   |  0   |  0   |  1   | 1.1V interne        |
// |  1   |  0   |  1   |  0   | GND                 |
// ---------------------------------------------------
// =============================================================================================================================================== //
