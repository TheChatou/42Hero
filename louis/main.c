#include <avr/io.h>
#include <util/delay.h>
#include <emb.h>
#include <stdbool.h>

#define SER 0 //pin14 of exp && 8 on UNO
#define RCLCK 1 //pin12 of exp && 9 on UNO
#define SRCLK 2 //pin11 of exp && 10 on UNO 

#define _BUTTON1 PD2
#define _BUTTON2 PD3

#define BPM 500

volatile uint16_t timer1_count = 0;
volatile uint16_t timer1_max = 20;
volatile uint8_t stop = 1;

// const uint8_t sheet[] = {0,0,1,0 ,0,0,0,1, 0,0,0,0, 0,0,0,1, 0,0,0,1, 0,0,0,0, 1,0,0,0, 0,0,0,0, 0,1,0,0, 0,0,0,1, 0,0,0,1, 0,0,0,1, 0,0,0,0, 1,0,1,1, 0,1,1,1};
const uint8_t sheet1[] = {1,0,0,0,1,1,0,0};
const uint8_t sheet2[] = {0,0,1,0,0,0,1,0};
const uint8_t sheet_size = 8;      
const   uint8_t start_up = 0xff;
const   uint8_t clean = 0;  

void led_set_up()
{
    DDRB |= (1 << SER) | (1 << RCLCK) | (1 << SRCLK);
    PORTB = 0;
}

void timer_set_up()
{
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM13) | (1 << WGM12) |(1 << CS11)| (1 << CS10);

    ICR1 = 6249;
    TIMSK1 |= 1 << TOIE1;
    stop = 0;
    sei();
}




void    shiftLane(uint8_t *lane, uint8_t size)
{
    PORTB &= ~(1 << RCLCK);
    for (uint8_t idx = 0; idx < size; idx++)
    {
        uint8_t data = lane[idx];
        for (uint8_t bit = 0; bit < 8; bit++)
        {
            PORTB &= ~(1 << SRCLK);
            if ((data >> bit) & 1)
            PORTB |= 1 << SER;
            else
                PORTB &= ~(1 << SER);
            PORTB |= (1 << SRCLK);
            __asm__ __volatile__ ("nop");
        }
    }
    PORTB |= (1 << RCLCK);
}

void    update_leds(uint8_t sheet_idx,  bool *target)
{
    static uint8_t notes[2] = {0, 0};
    notes[0] <<= 1;
    notes[1] <<= 1;
    if (sheet_idx < sheet_size)
    {
        notes[0] |= sheet1[sheet_idx];
        notes[1] |= sheet2[sheet_idx];
    }
    uart_str_code("notes 1  are",notes[0], 10);
    uart_str_code("notes 2 are", notes[1], 10);
    shiftLane(&notes, 2);
    if (sheet_idx >= sheet_size && notes[1] == 0 && notes[0] == 0)
    {
        stop = 1;
    }
    target[0] = notes[0] & (1 << 7);
    target[1] = notes[1] & (1 << 7);
}

ISR(TIMER1_OVF_vect)
{
    static uint8_t sheet_idx = 0;
    static bool is_pressed[2] = {0, 0};
    static bool target[2] = {true, true};

    if (timer1_count <= 12 || timer1_count >= 18)
    {
        if(PIND & (1 << _BUTTON1))
            is_pressed[0] = true; // check if button is pressed
        if (PIND & (1 <<_BUTTON2))
            is_pressed[1] = true;
        if (timer1_count == 0)
        {
           update_leds(sheet_idx, target);
            // play music
            uart_str_code("target 1 is: ", target[0], 10);
            uart_str_code("target 2 is: ", target[1], 10);
            sheet_idx++;
        }
        if (timer1_count == 12)
        {
            uart_str_code("pressed1? ", is_pressed[0], 10);
            uart_str_code("pressed2?", is_pressed[1],10);
            if (target[0] == is_pressed[0] && target[1] == is_pressed[1])
                uart_str_code("Success*2", sheet_idx-1, 10);
            else if (target[0] == is_pressed[0])
                uart_str_code("SuccessFail", sheet_idx - 1, 10);
            else if (target[1] == is_pressed[1])
                uart_str_code("FailSuccess",sheet_idx - 1, 10);
            else
                uart_str_code("FailFail", sheet_idx-1, 10);
            uart_printstr("\r\n");
            is_pressed[0] = false;
            is_pressed[1] = false;
        }
    }
    // blink led to make jumps more noticableis it better ?
    // if (timer1_count == 19)
    // {
    //     shiftLane(&clean, 1);
    // }
    timer1_count = (timer1_count + 1) % timer1_max;
    if (stop)
    {
        TIMSK1 &= ~(1 << TOIE1);
        TCCR1B &=~((1 << CS11)| (1 << CS10));
    }   
}

int main()
{
    uart_init(0);
    uint8_t lanes[2] = {clean, clean};
    uart_printstr("uart is ready\n");
    led_set_up();
    shiftLane(lanes, 2);
    _delay_ms(1000);
    lanes[0]= start_up;
    lanes[1] = start_up;
    shiftLane(lanes, 2);
    _delay_ms(2000);
    timer_set_up();
    while(1)
    {
    }

}
