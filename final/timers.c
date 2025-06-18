/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chatou <chatou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:49:50 by fcoullou          #+#    #+#             */
/*   Updated: 2025/05/16 10:28:31 by chatou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"


// TIMER 0 8 bits //////////////////////////////////////////////////////////////////
void    tc0_clock(ui8 cs02, ui8 cs01, ui8 cs00)
{
    set_or_clear(&TCCR0B, cs02, CS02);
    set_or_clear(&TCCR0B, cs01, CS01);
    set_or_clear(&TCCR0B, cs00, CS00);
}

void    tc0_mode(ui8 wgm02, ui8 wgm01, ui8 wgm00)
{
    set_or_clear(&TCCR0A, wgm00, WGM00);
    set_or_clear(&TCCR0A, wgm01, WGM01);
    set_or_clear(&TCCR0B, wgm02, WGM02);
}

void    tc0_compare_match(ui8 com0A1, ui8 com0A0, ui8 com0B1, ui8 com0B0)
{
    set_or_clear(&TCCR0A, com0A1, COM0A1);
    set_or_clear(&TCCR0A, com0A0, COM0A0);
    set_or_clear(&TCCR0A, com0B1, COM0B1);
    set_or_clear(&TCCR0A, com0B0, COM0B0);
}

// TIMER 2 8 bits //////////////////////////////////////////////////////////////////
void    tc2_clock(ui8 cs22, ui8 cs21, ui8 cs20)
{
    set_or_clear(&TCCR2B, cs22, CS20);
    set_or_clear(&TCCR2B, cs21, CS21);
    set_or_clear(&TCCR2B, cs20, CS22);
}

void    tc2_mode(ui8 wgm22, ui8 wgm21, ui8 wgm20)
{
    set_or_clear(&TCCR2A, wgm20, WGM20);
    set_or_clear(&TCCR2A, wgm21, WGM21);
    set_or_clear(&TCCR2B, wgm22, WGM22);
}

void    tc2_compare_match(ui8 com2A1, ui8 com2A0, ui8 com2B1, ui8 com2B0)
{
    set_or_clear(&TCCR2A, com2A1, COM2A1);
    set_or_clear(&TCCR2A, com2A0, COM2A0);
    set_or_clear(&TCCR2A, com2B1, COM2B1);
    set_or_clear(&TCCR2A, com2B0, COM2B0);
}

// TIMER 1 16 bits //////////////////////////////////////////////////////////////////
void    tc1_clock(ui8 cs12, ui8 cs11, ui8 cs10)
{
    set_or_clear(&TCCR1B, cs12, CS12);
    set_or_clear(&TCCR1B, cs11, CS11);
    set_or_clear(&TCCR1B, cs10, CS10);
}

void    tc1_mode(ui8 wgm13, ui8 wgm12, ui8 wgm11, ui8 wgm10)
{
    set_or_clear(&TCCR1A, wgm10, WGM10);
    set_or_clear(&TCCR1A, wgm11, WGM11);
    set_or_clear(&TCCR1B, wgm12, WGM12);
    set_or_clear(&TCCR1B, wgm13, WGM13);
}

void    tc1_compare_match(ui8 com1A1, ui8 com1A0, ui8 com1B1, ui8 com1B0)
{
    set_or_clear(&TCCR1A, com1A1, COM1A1);
    set_or_clear(&TCCR1A, com1A0, COM1A0);
    set_or_clear(&TCCR1A, com1B1, COM1B1);
    set_or_clear(&TCCR1A, com1B0, COM1B0);
}

// TIMER 3 16 bits //////////////////////////////////////////////////////////////////
void    tc3_clock(ui8 cs32, ui8 cs31, ui8 cs30)
{
    set_or_clear(&TCCR3B, cs32, CS32);
    set_or_clear(&TCCR3B, cs31, CS31);
    set_or_clear(&TCCR3B, cs30, CS30);
}

void    tc3_mode(ui8 wgm33, ui8 wgm32, ui8 wgm31, ui8 wgm30)
{
    set_or_clear(&TCCR3A, wgm30, WGM30);
    set_or_clear(&TCCR3A, wgm31, WGM31);
    set_or_clear(&TCCR3B, wgm32, WGM32);
    set_or_clear(&TCCR3B, wgm33, WGM33);
}

void    tc3_compare_match(ui8 com3A1, ui8 com3A0, ui8 com3B1, ui8 com3B0)
{
    set_or_clear(&TCCR3A, com3A1, COM3A1);
    set_or_clear(&TCCR3A, com3A0, COM3A0);
    set_or_clear(&TCCR3A, com3B1, COM3B1);
    set_or_clear(&TCCR3A, com3B0, COM3B0);
}

// TIMER 4 16 bits //////////////////////////////////////////////////////////////////
void    tc4_clock(ui8 cs42, ui8 cs41, ui8 cs40)
{
    set_or_clear(&TCCR4B, cs42, CS42);
    set_or_clear(&TCCR4B, cs41, CS41);
    set_or_clear(&TCCR4B, cs40, CS40);
}

void    tc4_mode(ui8 wgm43, ui8 wgm42, ui8 wgm41, ui8 wgm40)
{
    set_or_clear(&TCCR4A, wgm40, WGM40);
    set_or_clear(&TCCR4A, wgm41, WGM41);
    set_or_clear(&TCCR4B, wgm42, WGM42);
    set_or_clear(&TCCR4B, wgm43, WGM43);
}

void    tc4_compare_match(ui8 com4A1, ui8 com4A0, ui8 com4B1, ui8 com4B0)
{
    set_or_clear(&TCCR4A, com4A1, COM4A1);
    set_or_clear(&TCCR4A, com4A0, COM4A0);
    set_or_clear(&TCCR4A, com4B1, COM4B1);
    set_or_clear(&TCCR4A, com4B0, COM4B0);
}

void    tc5_clock(ui8 cs52, ui8 cs51, ui8 cs50)
{
    set_or_clear(&TCCR5B, cs52, CS52);
    set_or_clear(&TCCR5B, cs51, CS51);
    set_or_clear(&TCCR5B, cs50, CS50);
}

// TIMER 5 16 bits //////////////////////////////////////////////////////////////////
void    tc5_mode(ui8 wgm53, ui8 wgm52, ui8 wgm51, ui8 wgm50)
{
    set_or_clear(&TCCR5A, wgm50, WGM50);
    set_or_clear(&TCCR5A, wgm51, WGM51);
    set_or_clear(&TCCR5B, wgm52, WGM52);
    set_or_clear(&TCCR5B, wgm53, WGM53);
}

void    tc5_compare_match(ui8 com5A1, ui8 com5A0, ui8 com5B1, ui8 com5B0)
{
    set_or_clear(&TCCR5A, com5A1, COM5A1);
    set_or_clear(&TCCR5A, com5A0, COM5A0);
    set_or_clear(&TCCR5A, com5B1, COM5B1);
    set_or_clear(&TCCR5A, com5B0, COM5B0);
}


// ==============================================================	TIMER 0  8 bits	============================================================== //
// //////////////////// TIMER0 REGISTERS ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TIMSK0 : 8 bits ----------------------------------------------
// | ---- | ---- | ---- | ---- | ---- | OCIE0B | OCIE0A | TOIE0 |
// |   7  |   6  |   5  |   4  |   3  |    2   |    1   |   0   |
//                                         |        |       +--> Activer l'interruption TIMER0_OVF
//                                         |        +----------> Activer l'interruption TIMER0_COMPA
//                                         +-------------------> Activer l'interruption TIMER0_COMPB
//
// TIFR0 : 8 bits --------------------------------------------
// | ---- | ---- | ---- | ---- | ---- | OCF0B | OCF0A | TOV0 |
// |   7  |   6  |   5  |   4  |   3  |   2   |   1   |   0  |
//                                        |       |       +---> Interruption TIMER0_OVF
//                                        |       +-----------> Interruption TIMER0_COMPA
//                                        +-------------------> Interruption TIMER0_COMPB 
//
// TCCR0A : 8 bits ---------------------------------------------------
// | COM0A1 | COM0A0 | COM0B1 | COM0B0 | ---- | ---- | WGM01 | WGM00 |
// |   7    |   6    |   5    |   4    |   3  |   2  |   1   |   0   |
//     |        |        |        |        |       |     + - - - +--> Modes de comparaison (WGM01 & WGM00)
//     + - - - -+ - - - -+ - - - -+---------------------------------> Modes de sortie de comparaison (COM0A1, COM0A0, COM0B1 & COM0B0)
//
// TCCR0B : 8 bits --------------------------------------------
// | FOC0A | FOC0B | ---- | ---- | WGM02 | CS02 | CS01 | CS00 |
// |   7   |   6   |   5  |   4  |   3   |  2   |  1   |  0   |
//     |       |              |       |     + - - -+ - - -+-------> Prescaler (CS02, CS01, CS00) -> (1, 8, 64, 256, 1024)
//     |       |              |       +---------------------------> Mode de comparaison (WGM02)
//     + - - - +--------------------------------------------------> FOC0A & FOC0B : Force Output Compare A & B
// 
// OCR0A : 8 bits -----------
// |   OCR0A   |          Définit la valeur de comparaison pour le TIMER0_COMPA
// |  xxxx xxxx |
//
// OCR0B : 8 bits -----------
// |   OCR0B   |          Définit la valeur de comparaison pour le TIMER0_COMPB
// |  xxxx xxxx |
//
// //////////////////// TIMER0 MODES ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// *** Sélection de la source d'horloge (CS02, CS01, CS00)
// --------------------------------------------------------------------------
// | CS02 | CS01 | CS00 | Description                                       |
// |------|------|------|---------------------------------------------------|
// |  0   |  0   |  0   | Pas de source d'horloge (Timer arrêté)            |
// |  0   |  0   |  1   | clkI/O (Sans prescaler)                           |
// |  0   |  1   |  0   | clkI/O / 8 (Depuis le prescaler)                  |
// |  0   |  1   |  1   | clkI/O / 64 (Depuis le prescaler)                 |
// |  1   |  0   |  0   | clkI/O / 256 (Depuis le prescaler)                |
// |  1   |  0   |  1   | clkI/O / 1024 (Depuis le prescaler)               |
// |  1   |  1   |  0   | Source d'horloge externe sur T0, front descendant |
// |  1   |  1   |  1   | Source d'horloge externe sur T0, front montant    |
// --------------------------------------------------------------------------
//
// ** Modes de comparaison (WGM02, WGM01, WGM00) **
// -------------------------------------------------------------------------------------
// | Mode | WGM02 | WGM01 | WGM00 | Type de fonctionnement  | TOP  | Maj OCRx | TOV sur|
// |------|-------|-------|-------|-------------------------|------|---------|---------|
// |  0   |   0   |   0   |   0   | Normal                  | 0xFF | Immédiat| MAX     |
// |  1   |   0   |   0   |   1   | PWM Phase Correct       | 0xFF |   TOP   | BOTTOM  | --> Valeur MAX (255)
// |  2   |   0   |   1   |   0   | CTC                     | OCRA | Immédiat| MAX     |
// |  3   |   0   |   1   |   1   | Fast PWM                | 0xFF | BOTTOM  | MAX     | --> Valeur MAX (255)
// |  4   |   1   |   0   |   0   | Réservé                 |  -   |    -    |    -    |
// |  5   |   1   |   0   |   1   | PWM Phase Correct       | OCRA |   TOP   | BOTTOM  | --> Valeur définie par OCR0A
// |  6   |   1   |   1   |   0   | Réservé                 |  -   |    -    |    -    |
// |  7   |   1   |   1   |   1   | Fast PWM                | OCRA | BOTTOM  |  TOP    |
// -------------------------------------------------------------------------------------
//
// //////////////////// TIMER0 COMPARE MATCH /////////////////////////////////////////////////////////////////////////////////////////////////////////
// *** CTC ***
// ----------------------------------------------------------------------------------
// | COM0A1/COM0B1 | COM0A0/COM0B0 | Description                                    |
// |---------------|---------------|------------------------------------------------|
// | 0             | 0             | Mode normal, OC0A/OC0B déconnecté              |
// | 0             | 1             | Toggle OC0A/OC0B sur Compare Match             |
// | 1             | 0             | Clear OC0A/OC0B sur Compare Match (niveau bas) |
// | 1             | 1             | Set OC0A/OC0B sur Compare Match (niveau haut)  |
// ----------------------------------------------------------------------------------
// *** Fast PWM ***
// ----------------------------------------------------------------------------------------------------------
// | COM0A1/COM0B1 | COM0A0/COM0B0 | Description                                                            |
// |---------------|---------------|------------------------------------------------------------------------|
// | 0             | 0             | Mode normal, OC0A/OC0B déconnecté                                      |
// | 0             | 1             | WGM02 = 1 : Toggle OC0A sur Compare Match, OC0B déconnecté             |
// |               |               | WGM02 = 0 : Mode normal, OC0A/OC0B déconnecté                          |
// | 1             | 0             | Clear OC0A/OC0B sur Compare Match, Set OC0A/OC0B à BOTTOM (non-inversé)|
// | 1             | 1             | Set OC0A/OC0B sur Compare Match, Clear OC0A/OC0B à BOTTOM (inversé)    |
// ----------------------------------------------------------------------------------------------------------
// *** PWM, Phase Correct ***
// ----------------------------------------------------------------------------------------------------------
// | COM0A1/COM0B1 | COM0A0/COM0B0 | Description                                                            |
// |---------------|---------------|------------------------------------------------------------------------|
// | 0             | 0             | Mode normal, OC0A/OC0B déconnecté                                      |
// | 0             | 1             | WGM02 = 1 : Toggle OC0A sur Compare Match, OC0B déconnecté             |
// |               |               | WGM02 = 0 : Mode normal, OC0A/OC0B déconnecté                          |
// | 1             | 0             | Clear OC0A/OC0B sur Compare Match en montée, Set en descente           |
// | 1             | 1             | Set OC0A/OC0B sur Compare Match en montée, Clear en descente           |
// ----------------------------------------------------------------------------------------------------------
// =============================================================================================================================================== //




// ==============================================================	TIMER 1  16 bits	========================================================== //
// //////////////////// TIMER1 REGISTERS ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TIMSK1 : 8 bits ----------------------------------------------
// | ---- | ---- | ---- | ---- | ---- | ICIE1 | OCIE1B | OCIE1A |
// |   7  |   6  |   5  |   4  |   3  |   2   |    1   |    0   |
//                                        |        |        +--> Activer l'interruption TIMER1_COMPA
//                                        |        +-----------> Activer l'interruption TIMER1_COMPB
//                                        +--------------------> Activer l'interruption TIMER1_CAPT
//
// TCCR1A : 8 bits -------------------------------------------------------
// | COM1A1 | COM1A0 | COM1B1 | COM1B0 | COM1C1 | COM1C0 | WGM11 | WGM10 |
// |   7    |   6    |   5    |   4    |   3    |   2    |   1   |   0   |
//     |        |        |        |        |        |        |       |
//     |        |        |        |        |        |        + - - - +--> Modes de comparaison (WGM11 & WGM10) : PWM Phase Correct
//     + - - - -+ - - - -+ - - - -+ - - - -+ - - - -+-------------------> Modes de sortie de comparaison (COM1A1, COM1A0, COM1B1, COM1B0, COM1C1 & COM1C0)
// 
// TCCR1B : 8 bits ---------------------------------------------
// | ICNC1 | ICES1 | ---- | WGM13 | WGM12 | CS12 | CS11 | CS10 |
// |   7   |   6   |   5  |   4   |   3   |  2   |  1   |  0   |
//     |       |              |       |      |      |      |
//     |       |              |       |      |      |      |
//     |       |              |       |      + - - -+ - - -+--> Prescaler (CS12, CS11, CS10)
//     |       |              |       |
//     |       |              +-------+-----------------------> Modes de comparaison (WGM13 & WGM12) : PWM Phase Correct & CTC
//     |       +----------------------------------------------> ICES1 : Capture Edge Select
//     +------------------------------------------------------> ICNC1 : Input Capture Noise Canceler
// 
// OCR1A : 16 bits -----------
// |   OCR1AH   |   OCR1AL   |          Définit la valeur de comparaison pour le TIMER1_COMPA
// |  xxxx xxxx |  xxxx xxxx |          
// 
// //////////////////// TIMER1 MODES ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// | Mode | WGM13 | WGM12 | WGM11 | WGM10 | Mode de fonctionnement                  | TOP    | OCR1x mis à jour à | TOV1 se déclenche à  |
// |------|-------|-------|-------|-------|-----------------------------------------|--------|--------------------|----------------------|
// | 0    | 0     | 0     | 0     | 0     | Normal                                  | 0xFFFF | Immédiat           | MAX                  |
// | 1    | 0     | 0     | 0     | 1     | PWM, Phase Correct, 8-bit               | 0x00FF | TOP                | BOTTOM               |
// | 2    | 0     | 0     | 1     | 0     | PWM, Phase Correct, 9-bit               | 0x01FF | TOP                | BOTTOM               |
// | 3    | 0     | 0     | 1     | 1     | PWM, Phase Correct, 10-bit              | 0x03FF | TOP                | BOTTOM               |
// | 4    | 0     | 1     | 0     | 0     | CTC (Clear Timer on Compare Match)      | OCR1A  | Immédiat           | MAX                  |
// | 5    | 0     | 1     | 0     | 1     | Fast PWM, 8-bit                         | 0x00FF | BOTTOM             | TOP                  |
// | 6    | 0     | 1     | 1     | 0     | Fast PWM, 9-bit                         | 0x01FF | BOTTOM             | TOP                  |
// | 7    | 0     | 1     | 1     | 1     | Fast PWM, 10-bit                        | 0x03FF | BOTTOM             | TOP                  |
// | 8    | 1     | 0     | 0     | 0     | PWM, Phase & Frequency Correct (ICR1)   | ICR1   | BOTTOM             | BOTTOM               |
// | 9    | 1     | 0     | 0     | 1     | PWM, Phase & Frequency Correct (OCR1A)  | OCR1A  | BOTTOM             | BOTTOM               |
// | 10   | 1     | 0     | 1     | 0     | PWM, Phase Correct (ICR1)               | ICR1   | TOP                | BOTTOM               |
// | 11   | 1     | 0     | 1     | 1     | PWM, Phase Correct (OCR1A)              | OCR1A  | TOP                | BOTTOM               |
// | 12   | 1     | 1     | 0     | 0     | CTC (ICR1)                              | ICR1   | Immédiat           | MAX                  |
// | 13   | 1     | 1     | 0     | 1     | (Réservé)                               | –      | –                  | –                    |
// | 14   | 1     | 1     | 1     | 0     | Fast PWM (ICR1)                         | ICR1   | BOTTOM             | TOP                  |
// | 15   | 1     | 1     | 1     | 1     | Fast PWM (OCR1A)                        | OCR1A  | BOTTOM             | TOP                  |
//
// //////////////////// TIMER1 COMPARE MATCH /////////////////////////////////////////////////////////////////////////////////////////////////////////
// *** CTC ***
// ----------------------------------------------------------------------------------
// | COM1A1/COM1B1 | COM1A0/COM1B0 | Description                                    |
// |---------------|---------------|------------------------------------------------|
// | 0             | 0             | Mode normal, OC1A/OC1B déconnecté              |
// | 0             | 1             | Toggle OC1A/OC1B sur Compare Match             |
// | 1             | 0             | Clear OC1A/OC1B sur Compare Match (niveau bas) |
// | 1             | 1             | Set OC1A/OC1B sur Compare Match (niveau haut)  |
// ----------------------------------------------------------------------------------
// *** Fast PWM ***
// ----------------------------------------------------------------------------------------------------------
// | COM1A1/COM1B1 | COM1A0/COM1B0 | Description                                                            |
// |---------------|---------------|------------------------------------------------------------------------|
// | 0             | 0             | Mode normal, OC1A/OC1B déconnecté                                      |
// | 0             | 1             | WGM13:0 = 14 ou 15 : Toggle OC1A sur Compare Match, OC1B déconnecté    |
// |               |               | Autres WGM1 : Mode normal, OC1A/OC1B déconnecté                        |
// | 1             | 0             | Clear OC1A/OC1B sur Compare Match, Set OC1A/OC1B à BOTTOM (non-inversé)|
// | 1             | 1             | Set OC1A/OC1B sur Compare Match, Clear OC1A/OC1B à BOTTOM (inversé)    |
// ----------------------------------------------------------------------------------------------------------
// *** PWM, Phase Correct & PWM, Phase & Frequency Correct ***
// ----------------------------------------------------------------------------------------------------------
// | COM1A1/COM1B1 | COM1A0/COM1B0 | Description                                                            |
// |---------------|---------------|------------------------------------------------------------------------|
// | 0             | 0             | Mode normal, OC1A/OC1B déconnecté                                      |
// | 0             | 1             | WGM13:0 = 9 ou 11 : Toggle OC1A sur Compare Match, OC1B déconnecté     |
// |               |               | Autres WGM1 : Mode normal, OC1A/OC1B déconnecté                        |
// | 1             | 0             | Clear OC1A/OC1B sur Compare Match en comptant UP, Set en comptant DOWN |
// | 1             | 1             | Set OC1A/OC1B sur Compare Match en comptant UP, Clear en comptant DOWN |
// ----------------------------------------------------------------------------------------------------------
// =============================================================================================================================================== //



// ==============================================================	TIMER 2  8 bits	============================================================== //
// //////////////////// TIMER2 REGISTERS ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TIMSK2 : 8 bits ----------------------------------------------
// | ---- | ---- | ---- | ---- | ---- | OCIE2B | OCIE2A | TOIE2 |
// |   7  |   6  |   5  |   4  |   3  |    2   |    1   |   0   |
//                                         |        |       +--> Activer l'interruption TIMER2_OVF
//                                         |        +----------> Activer l'interruption TIMER2_COMPA
//                                         +-------------------> Activer l'interruption TIMER2_COMPB
//
// TIFR2 : 8 bits --------------------------------------------
// | ---- | ---- | ---- | ---- | ---- | OCF2B | OCF2A | TOV2 |
// |   7  |   6  |   5  |   4  |   3  |   2   |   1   |   0  |
//                                         |        |       +--> Flag TIMER2_OVF
//                                         |        +----------> Flag TIMER2_COMPA
//                                         +-------------------> Flag TIMER2_COMPB
//
// TCCR2A : 8 bits ---------------------------------------------------
// | COM2A1 | COM2A0 | COM2B1 | COM2B0 | ---- | ---- | WGM21 | WGM20 |
// |   7    |   6    |   5    |   4    |   3  |   2  |   1   |   0   |
//     |        |        |        |        |       |     + - - - +----> Modes de comparaison (WGM21 & WGM20)
//     + - - - -+ - - - -+ - - - -+ - - - -+--------------------------> Modes de sortie de comparaison (COM2A1, COM2A0, COM2B1 & COM2B0)
// 
// //////////////////// TIMER2 MODES ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// | Mode | WGM22 | WGM21 | WGM20 | Mode de fonctionnement | TOP  | OCRx mis à jour à | TOV Flag sur |
// |------|-------|-------|-------|-----------------------|------|------------------|----------------|
// | 0    | 0     | 0     | 0     | Normal                | 0xFF | Immédiat         | MAX            |
// | 1    | 0     | 0     | 1     | PWM, Phase Correct    | 0xFF | TOP              | BOTTOM         |
// | 2    | 0     | 1     | 0     | CTC                   | OCRA | Immédiat         | MAX            |
// | 3    | 0     | 1     | 1     | Fast PWM              | 0xFF | BOTTOM           | MAX            |
// | 4    | 1     | 0     | 0     | Réservé               | -    | -                | -              |
// | 5    | 1     | 0     | 1     | PWM, Phase Correct    | OCRA | TOP              | BOTTOM         |
// | 6    | 1     | 1     | 0     | Réservé               | -    | -                | -              |
// | 7    | 1     | 1     | 1     | Fast PWM              | OCRA | BOTTOM           | TOP            |
//
// //////////////////// TIMER2 COMPARE MATCH /////////////////////////////////////////////////////////////////////////////////////////////////////////
// *** CTC ***
// ----------------------------------------------------------------------------------
// | COM2A1/COM2B1 | COM2A0/COM2B0 | Description                                    |
// |---------------|---------------|------------------------------------------------|
// | 0             | 0             | Mode normal, OC2A/OC2B déconnecté              |
// | 0             | 1             | Toggle OC2A/OC2B sur Compare Match             |
// | 1             | 0             | Clear OC2A/OC2B sur Compare Match (niveau bas) |
// | 1             | 1             | Set OC2A/OC2B sur Compare Match (niveau haut)  |
// ----------------------------------------------------------------------------------
// *** Fast PWM ***
// ----------------------------------------------------------------------------------------------------------
// | COM2A1/COM2B1 | COM2A0/COM2B0 | Description                                                            |
// |---------------|---------------|------------------------------------------------------------------------|
// | 0             | 0             | Mode normal, OC2A/OC2B déconnecté                                      |
// | 0             | 1             | WGM22 = 1 : Toggle OC2A sur Compare Match, OC2B déconnecté             |
// |               |               | WGM22 = 0 : Mode normal, OC2A/OC2B déconnecté                          |
// | 1             | 0             | Clear OC2A/OC2B sur Compare Match, Set OC2A/OC2B à BOTTOM (non-inversé)|
// | 1             | 1             | Set OC2A/OC2B sur Compare Match, Clear OC2A/OC2B à BOTTOM (inversé)    |
// ----------------------------------------------------------------------------------------------------------
// *** PWM, Phase Correct ***
// ----------------------------------------------------------------------------------------------------------
// | COM2A1/COM2B1 | COM2A0/COM2B0 | Description                                                            |
// |---------------|---------------|------------------------------------------------------------------------|
// | 0             | 0             | Mode normal, OC2A/OC2B déconnecté                                      |
// | 0             | 1             | WGM22 = 1 : Toggle OC2A sur Compare Match, OC2B déconnecté             |
// |               |               | WGM22 = 0 : Mode normal, OC2A/OC2B déconnecté                          |
// | 1             | 0             | Clear OC2A/OC2B sur Compare Match en montée, Set en descente           |
// | 1             | 1             | Set OC2A/OC2B sur Compare Match en montée, Clear en descente           |
// ----------------------------------------------------------------------------------------------------------
// =============================================================================================================================================== //