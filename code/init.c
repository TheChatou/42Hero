#include "init.h"

void    master_timer_init()
{
    TCCR0B |= (1 << CS01) | (1 << CS00); //prescaler == 64
    TCCR0A = (1 << WGM01); // mode == CTC
    TIMSK0 |= 1 << OCIE0A; //interrupt on compare match
    OCR0A = 100;
}

/// @brief notes are played using 4 timers (4 notes polyphony)
/// timers comapare is set according the the desired frequency and will output a square note
void    notes_timers_init()
{
    TCCR1B |= 1 << CS11; // prescaler == 8
    
    //timer mode fast PWM with top = ICR
    TCCR1B |= (1 << WGM12)  | (1 << WGM13);
    TCCR1A |= (1 << WGM11);

    TCCR1A |= (1 << COM1A1); //clear OC1A on compare match, set it at bottom
    DDRB |= (1 << PB5); //OC1A == PB5 as output
    ICR1 = 0;
    OCR1A = 0;

    //timer 3
    TCCR3B |= 1 << CS31;
    TCCR3B |= (1 << WGM32) | (1 << WGM33);
    TCCR3A |= (1 << WGM31);
    TCCR3A |= (1 << COM3A1);
    DDRE |= (1 << PE3);
    ICR3 = 0;
    OCR3A = 0;

    //timer 4
    TCCR4B |= 1 << CS41;
    TCCR4B |= (1 << WGM42) | (1 << WGM43);
    TCCR4A |= (1 << WGM41);
    TCCR4A |= (1 << COM4A1);
    DDRH |= (1 << PH3);
    ICR4 = 0;
    OCR4A = 0;

    //timer 5
    TCCR5B |= 1 << CS51;
    TCCR5B |= (1 << WGM52) | (1 << WGM53);
    TCCR5A |= (1 << WGM51);
    TCCR5A |= (1 << COM5A1);
    DDRL |= (1 << PL3);
    ICR5 = 0;
    OCR5A = 0;
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

    DDRB |= 1 << PB2; //left
    DDRB |= 1 << PB3; //right

    master_timer_init();
    notes_timers_init();

}