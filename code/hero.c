#include "hero.h"


/// @brief helper function to compare buttons input against partition
/// @param a the partition
/// @param b the button state
/// @return return 0 if the player made an error, if correct returns: 1 if no button
/// were to be pushed, else 2. It was decided a no input success would not yield points
uint8_t compare(volatile uint8_t *a, volatile uint8_t *b)
{
    uint8_t light = 0;
    for (uint8_t i =0; i<4; i++)
    {
        if (a[i] != b[i])
            return 0;
        if (a[i] > 0)
            light = 1;

    }
    return (1 + light);
}

/// @brief reset a 4 byte vector to 0
/// @param a the vector (SIZE==4 assumed)
inline void    reset(volatile uint8_t   *a)
{
    a[0] = 0;
    a[1] = 0;
    a[2] = 0;
    a[3] = 0;
}

/// @brief set the top and compare match of note timers to 0
void    timers_stop()
{
    TCCR1A = OCR1A = 0;
    TCCR3A = OCR3A = 0;
    TCCR4A = OCR4A = 0;
    TCCR5A = OCR5A = 0;
}

/// @brief select the timer corresponding to track and sets its top and compare value to play the desired frequency(note)
/// @param note the desired frequency
/// @param track the timer to set
void play_note_with_timer(uint16_t note, uint8_t track)
{
    uint16_t freq = note;
    
    if (freq == 0)
    {
        // disable the timer if the frequency is 0
        if (track == 0) { OCR1A = 0; }
        else if (track == 1) { OCR3A = 0; }
        else if (track == 2) { OCR4A = 0; }
        else if (track == 3) { OCR5A = 0; }
        return;
    }

    // freq = F_timer / 2 (1+TOP)
    // => TOP = F_timer / (2*freq) - 1
    // F_timer = FCPU/8
    uint16_t top = (F_CPU / (16 * freq)) - 1;

    // select the corresponding timer and set the top and compare value
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

/// @brief helper function to display score as the guage
/// @param pct 
/// @return 
uint8_t gauge(uint16_t pct)
{
    uint8_t i = pct / 10;
    uint8_t g = 0;
    for (uint8_t j = 0; j < i; j++)
    {
        g = (g << 1) + 1;
    }
    return g;
}

