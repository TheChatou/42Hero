#include "parts.h"
#include "expander.h"
#include "init.h"
#include "tetris.h"

volatile    uint16_t    tc0_counter = 0;
extern volatile Expander exp_leds;
volatile    uint8_t button_left[4] = {0,0,0,0};
volatile    uint8_t button_right[4] = {0,0,0,0};

volatile    uint8_t pushed_left[4] = {0,0,0,0};
volatile    uint8_t pushed_right[4] = {0,0,0,0};

volatile    uint16_t    tempo = 0;
volatile    uint8_t     state = PLAY;

uint8_t compare(volatile uint8_t *a, volatile uint8_t *b)
{
    for (uint8_t i =0; i<4; i++)
    {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}

inline void    reset(volatile uint8_t   *a)
{
    a[0] = 0;
    a[1] = 0;
    a[2] = 0;
    a[3] = 0;
}

void    timers_stop()
{
    TCCR1A = OCR1A = 0;
    TCCR3A = OCR3A = 0;
    TCCR4A = OCR4A = 0;
    TCCR5A = OCR5A = 0;
}



// Fonction pour jouer une note
void play_note_with_timer(uint16_t note, uint8_t track)
{
    uint16_t freq = note;
    
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

void    play_tracks(const t_part *music, uint16_t curr_note)
{
    tcs_init();

 
    play_note_with_timer(pgm_read_word(&music->tracks[0].note[curr_note]), 0);
    play_note_with_timer(pgm_read_word(&music->tracks[1].note[curr_note]), 1);
    play_note_with_timer(pgm_read_word(&music->tracks[2].note[curr_note]), 2);
    play_note_with_timer(pgm_read_word(&music->tracks[3].note[curr_note]), 3);
      
    tc0_counter = 0;
    TCNT2 = 0;
}

ISR(TIMER0_COMPA_vect)
{
    tc0_counter++;

    if (tc0_counter == tempo)
    {
        tc0_counter = 0;
        // uart_printstr("Tick - note : ");
        state = PLAY; // Indiquer que la note est terminée
    }
    else if (tc0_counter == (3*tempo / 4)){
        state = INPUT_AHEAD;
    }
    else if (tc0_counter == (tempo / 4)){
        state = UPDATE_SCORE;
    }
}


inline  void    measure_buttons()
{
    button_left[0] = !(PINC & (1 << PC6));
    button_left[1] = !(PINC & (1 << PC4));
    button_left[2] = !(PINC & (1 << PC2));
    button_left[3] = !(PINC & (1 << PC0));   
    button_right[0] = !(PINL & (1 << PL6));
    button_right[1] = !(PINL & (1 << PL4));
    button_right[2] = !(PINL & (1 << PL2));
    button_right[3] = !(PINL & (1 << PL0));

}

void    play_song( const t_part *p)
{
    const t_part    *music = p;
    const   uint16_t    length = pgm_read_word(&music->length);
    volatile uint16_t    time = 0;
    tempo = pgm_read_word(&music->tempo);

    volatile    uint16_t   left_score = 0;
    volatile    uint16_t    right_score = 0;

    volatile    uint8_t leds[4] = {ALL, ALL, ALL, ALL};
    volatile    uint8_t target[4] = {0,0,0,0};
    state = PLAY;
    while(time <= length)
    {
        measure_buttons();
        if (state == PLAY)
        {
            // save target notes for score
            target[0] = leds[0] & 1;
            target[1] = leds[1] & 1;
            target[2] = leds[2] & 1;
            target[3] = leds[3] & 1;
            //play note
            play_tracks(music, time);
            // update led
            uint8_t new_led = pgm_read_byte(&music->led[time]);
            for (uint8_t i = 0; i < 4; i++)
            {
                if (new_led & (1 << i))
                {
                    leds[i] = (leds[i] >> 1) | 0b10000000;
                }
                else{
                    leds[i] = leds[i] >> 1;
                }
            }
            shiftLane(&exp_leds, leds, 4);
            time++;
            state = INPUT_AFTER;
        }
        else if (state == UPDATE_SCORE)
        {
            // comapre to the target, reset the pushed vars and update score
            left_score += compare(target, pushed_left);
            right_score += compare(target, pushed_right);
            reset(pushed_left);
            reset(pushed_right);
            state = WAIT;
        }
        if (state > WAIT)
        {
            // we take into account a button pushed
            for (uint8_t i = 0; i < 4; i++)
            {
                pushed_left[i] |= button_left[i];
                pushed_right[i] |= button_right[i];
            }
            // set pushed vars
        }
    }



}

//52 PB1 PB0

int main(void)
{
    sei();
    init();
    turn_leds_off();
    turn_leds_on();
    while(1)
    {
        measure_buttons();
        if (button_left[0])
        {
            play_song(&tetris);
            turn_leds_off();
            turn_leds_on();
        }
        _delay_ms(400);
    }
}