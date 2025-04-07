#include <avr/io.h>
#include <util/delay.h>

#define SER 0 //pin14 of exp && 8 on UNO
#define RCLCK 1 //pin12 of exp && 9 on UNO
#define SRCLK 2 //pin11 of exp && 10 on UNO 



volatile uint8_t sheet[] = {0,1,1,1,0,1,0,1,0,1,1,1,0,0,0,1,1,1,1,1,0,1,0,0};
#define _SHEET_SIZE = 24;

void set_up()
{
    DDRB |= (1 << SER) | (1 << RCLCK) | (1 << SRCLK);
    PORTB = 0;
}


//set the values of the 8 ports
void shiftOut(uint8_t data)
{
    // unlock latch
    PORTB &= ~(1 << RCLCK);
    for (uint8_t bit = 0; bit < 8; bit++)
    {
        // clock low
        PORTB &= ~(1 << SRCLK);
        // load bit to send
        if ((data >> bit) & 1)
            PORTB |= 1 << SER;
        else
            PORTB &= ~(1 << SER);
        //clock high => shit registered shifted and value loaded
        PORTB |= (1 << SRCLK);
        _delay_us(10);
    }
    // lock latch shift register copied into data register
    PORTB |= (1 << RCLCK);
}

int main()
{
    set_up();
    shiftOut(0b11111111);
    _delay_ms(1000);
    shiftOut(0b00000000);
    _delay_ms(1000);
    uint8_t leds = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        leds |= sheet[i] << i;
    }
    shiftOut(leds);
  
    while(1)
    {
       
        _delay_ms(1000);
        uint8_t idx = 8;
        while(idx < 24)
        {
            leds = (leds >> 1) | (sheet[idx] << 7);
            shiftOut(leds);
            _delay_ms(1000);
            idx++;
        }
       
    }
}