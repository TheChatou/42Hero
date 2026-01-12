#include "hero.h"
#include "text_to_led.h"
#include "parts.h"
#include "zelda.h"
#include "mario.h"
#include "tetris.h"
#include "sonic.h"

// counter incremented by master timer to update state machine
volatile uint16_t   tc0_counter;

extern volatile Expander exp_leds;

//vectors to store button measures
volatile    uint8_t button_left[4] = {0,0,0,0};
volatile    uint8_t button_right[4] = {0,0,0,0};

//vectors to store player input from button measures
volatile    uint8_t pushed_left[4] = {0,0,0,0};
volatile    uint8_t pushed_right[4] = {0,0,0,0};

volatile    uint16_t    tempo = 0;
volatile    uint8_t     state = PLAY;

volatile    uint8_t led_logo[4] = {0, 0, 0, 0};

/// @brief play next time from the part
/// @param music the partition
/// @param curr_note index of the current time in the arrays
void    play_tracks(const t_part *music, uint16_t curr_note)
{
    notes_timers_init();

 
    play_note_with_timer(pgm_read_word(&music->tracks[0].note[curr_note]), 0);
    play_note_with_timer(pgm_read_word(&music->tracks[1].note[curr_note]), 1);
    play_note_with_timer(pgm_read_word(&music->tracks[2].note[curr_note]), 2);
    play_note_with_timer(pgm_read_word(&music->tracks[3].note[curr_note]), 3);
      
    tc0_counter = 0; // reset counter to 0
    TCNT2 = 0;
}

//master timer:
// play the notes, update the state-engine status to trigger input measuremen/comparison
// right now each event is base on a proportion of the music's tempo which is not that great
ISR(TIMER0_COMPA_vect)
{
    if (state == IDLE)
        return;
    tc0_counter++; // increase counter
    if (tc0_counter == tempo) // one cycle completed
    {
        tc0_counter = 0;
        state = PLAY; // time to play next note
    }
    else if (tc0_counter == (3*tempo / 4)){ //starting to accept inout for next note
        state = INPUT_AHEAD;
    }
    else if (tc0_counter == (tempo / 4)){ // end of input-window => match input/part and score
        state = UPDATE_SCORE;
    }
    else if (tc0_counter == (tempo / 2)) // turn off success leds
    {
        PORTB &= ~( (1 << VALID_LEFT) | (1 << VALID_RIGHT));
    }
}

/// @brief store the state of buttons in the vectors
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

/// @brief main game loop: state driven see comments inside
/// @param p the music to play
void    play_song( const t_part *p)
{
    const t_part    *music = p;
    const   uint16_t    length = pgm_read_word(&music->length);
    volatile uint16_t    time = 0; // partition idx counter
    tempo = pgm_read_word(&music->tempo);

    volatile    uint16_t   left_score = 0;
    volatile    uint16_t    right_score = 0;

    volatile    uint8_t leds[4] = {0, 0, 0, 0};
    volatile    uint8_t target[4] = {0,0,0,0};

    volatile uint16_t   best = 0; // compute the perfect score to display score as a gauge

    state = PLAY;
    turn_leds_off();
    _delay_ms(1000);
    while(time <= length)
    {
        measure_buttons();
        if (state == PLAY) //time to play note
        {

            play_tracks(music, time);
            // update led
            uint8_t new_led = pgm_read_byte(&music->led[time]);
            uint16_t diff[2];
            diff[0] = pgm_read_word(&music->diff[0]);
            diff[1] = pgm_read_word(&music->diff[1]);
            // to ease the game only a fraction of note can be taken as leds and button input
            // eg : one note out of four has to be played by the player for tetris
            if ((time % diff[0]) != diff[1])
                new_led = 0;
            // set the led according to the part
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
            // register the target for the player input
            target[0] = leds[0] & 1;
            target[1] = leds[1] & 1;
            target[2] = leds[2] & 1;
            target[3] = leds[3] & 1;
            time++; // increase idx counter
            state = INPUT_AFTER; // state update : accept player inputs 
        }
        else if (state == UPDATE_SCORE) // compare players input against the target
        {
            uint8_t left_delta = compare(target, pushed_left);
            uint8_t right_delta = compare(target, pushed_right);
            if (left_delta == 2) // if player is correct and button were to be pushed => score
            {
                PORTB |= 1 << VALID_LEFT;
                left_score += 1;
            }
            if (right_delta == 2)
            {
                PORTB |= 1 << VALID_RIGHT;
                right_score += 1;
            }
            if (target[0] | target[1] | target[2] | target[3]) // compute perfect score
                best += 1;
            state = WAIT; //update state : just wait while the notes play
            reset(pushed_left);
            reset(pushed_right);
        }
        if (state > WAIT) // in all state above WAIT the player input are taken into account
        {
            // we take into account a button pushed
            for (uint8_t i = 0; i < 4; i++)
            {
                pushed_left[i] |= button_left[i];
                pushed_right[i] |= button_right[i];
            }
            // set pushed vars
        }
        // condition to stop te song by pushing all buttons, disable in release mode!
        if (button_left[3] && button_right[3] && 
            button_left[2] && button_right[2] &&
            button_left[1] && button_right[1] &&
            button_left[0] && button_right[0])
        {
            timers_stop();
            return;
        }
    }
    // end of song time to compute score
    timers_stop();
    state = IDLE;
    PORTB &= ~((1 << VALID_LEFT) | (1 << VALID_RIGHT));

    //score as percentage of perfect score
    uint8_t final_left = gauge((left_score * 100) / (best));
    uint8_t final_right = gauge((right_score*100) / (best));
    uint8_t score_display[4] = {final_left, 0, 0, final_right};
    
    //display winner side
    if (left_score > right_score)
        PORTB |= 1 << VALID_LEFT;
    else
        PORTB |= 1 << VALID_RIGHT;
    shiftLane(&exp_leds, score_display, 4);

    _delay_ms(5000);
    turn_leds_off();
    //score in binary
    uint8_t as_bit_left = (left_score*255)/best;
    uint8_t as_bit_right = (right_score*255)/best;
    score_display[0] = as_bit_left;
    score_display[3] = as_bit_right;
    shiftLane(&exp_leds, score_display, 4);
    _delay_ms(10000);
    PORTB &= ~((1 << VALID_LEFT) | (1 << VALID_RIGHT));
}

/// @brief waiting screen displaying 42 hero on the leds, interrupt when correct button input pressed
/// @return 
int playing_logo()
{
    static uint8_t current_char = 0;
    static uint32_t timer = 0;
    
    measure_buttons();

    // go back to track selection if a button was pressed
    for (uint8_t i = 0; i < 4; i++)
        if (button_left[i] && button_right[i])
            return 0;

    if (++timer >= 40000)
    {
        timer = 0;

        for (uint8_t row = 0; row < 4; row++)
        {
            led_logo[row] = pgm_read_byte(&logo_hero[current_char][row]);
            // led_logo[row] = pgm_read_byte(&alphabet[0][row]);
        }

        shiftLane(&exp_leds, led_logo, 4);
        current_char = (current_char + 1) % LOGO_SIZE;
    }

    return 1;
}

int main(void)
{
    sei();
    init();
    turn_leds_off();
    turn_leds_on();
    while(1)
    {
        measure_buttons();
        while (playing_logo());
        // song is chosen by each player pushing the same button
        if (button_left[3] && button_right[3])
        {
            play_song(&tetris_test);
            turn_leds_off();
            turn_leds_on();
        }
        else if (button_left[0] && button_right[0])
        {
            play_song(&mario_test);
            turn_leds_off();
            turn_leds_on();
        }
        else if (button_left[1] && button_right[1])
        {
            play_song(&sonic);
            turn_leds_off();
            turn_leds_on();
        }
        else if (button_left[2] && button_right[2])
        {
            play_song(&zelda);
            turn_leds_off();
            turn_leds_on();
        }
        
        _delay_ms(300);
    }
}