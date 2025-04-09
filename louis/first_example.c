#include <avr/io.h>
#include <util/delay.h>

#define SER 0 //pin14 of exp && 8 on UNO
#define RCLCK 1 //pin12 of exp && 9 on UNO
#define SRCLK 2 //pin11 of exp && 10 on UNO 



const char *sheet[] = 
        {"|--X-|---X|----|---X|---X|----|X---|----|-X--|---X|---X|---X|---X|----|X---|----|----",
        "|----|----|X-X-|----|X---|----|--X-|X---|----|----|X---|----|X-X-|----|----|X---|X---"};

#define TIME_0 0xaa55
#define TIME_1 0x55aa
#define _SHEET_SIZE = 24;



void set_up()
{
    DDRB |= (1 << SER) | (1 << RCLCK) | (1 << SRCLK);
    PORTB = 0;
}

void shiftOut(uint8_t data)
{
    PORTB &= ~(1 << RCLCK);
    for (uint8_t bit = 0; bit < 8; bit++)
    {
        PORTB &= ~(1 << SRCLK);
        if ((data >> bit) & 1)
            PORTB |= 1 << SER;
        else
            PORTB &= ~(1 << SER);
        PORTB |= (1 << SRCLK);
        _delay_us(10);
    }
    PORTB |= (1 << RCLCK);
}

void    shiftLane(uint16_t data)
{
    PORTB &= ~(1 << RCLCK);
    for (uint8_t bit = 0; bit < 16; bit++)
    {
        PORTB &= ~(1 << SRCLK);
        if ((data >> bit) & 1)
            PORTB |= 1 << SER;
        else
            PORTB &= ~(1 << SER);
        PORTB |= (1 << SRCLK);
        _delay_us(10);
    }
    PORTB |= (1 << RCLCK);
}

void    load_notes(uint16_t *notes)
{
    static uint8_t idx = 0;
    if (idx % 5 == 0)
        idx = (idx+1) % 86;
    uint8_t instr1 = (*notes & 0xff00) >> 8;
    uint8_t instr2 = (*notes & 0x00ff);
    instr1 <<= 1;
    instr2 <<= 1;
    if (sheet[0][idx] == 'X')
        instr1 |= 1;
    if (sheet[1][idx] == 'X')
        instr2 |=  1;
    *notes = (instr1 << 8) | instr2;
    idx = (idx + 1) % 86;
}

int main()
{
    set_up();
    shiftLane(0xffff);
    _delay_ms(2000);
    shiftLane(0);
    uint16_t notes = 0;
    while(1)
    {
        load_notes(&notes);
        shiftLane(notes);
        _delay_ms(200);
    }

}