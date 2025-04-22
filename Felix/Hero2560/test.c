#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL
#define BAUD_RATE 115200

void uart_init()
{
    uint16_t ubrr = 8;
    UBRR0H = (ubrr >> 8);
    UBRR0L = ubrr;
    UCSR0B = (1 << TXEN0); // Activer la transmission
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 bits, 1 stop bit
}

void uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0))); // Attendre que le registre soit prêt
    UDR0 = c;
}

void uart_printstr(const char *str)
{
    while (*str)
        uart_tx(*str++);
}

int main(void)
{
    uart_init();

    // Configure PB1 comme une sortie
    DDRB |= (1 << PB7);

    while (1)
    {
        uart_printstr("Hello, UART!\n");
        _delay_ms(1000);
        // Allumer la LED (mettre PB7 à HIGH)
        PORTB |= (1 << PB7);
        uart_printstr("LED ON\n");
        _delay_ms(1000);

        // Éteindre la LED (mettre PB7 à LOW)
        PORTB &= ~(1 << PB7);
        uart_printstr("LED OFF\n");
        _delay_ms(1000);
    }
    return 0;
}