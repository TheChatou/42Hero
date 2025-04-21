
#include "emb.h"

uint8_t round_ubrr()
{
    uint16_t ubrr = (10UL*F_CPU)/(16UL*UART_BAUDRATE) - 1;
    if (ubrr % 10 > 5)
        return (ubrr / 10 + 1);
    else
        return (ubrr / 10);
}

void uart_init(uint8_t r_int)
{
    uint8_t ubrr = round_ubrr();
    // define the rate of transmission
    UBRR0H = (unsigned char) (ubrr >> 8);
    UBRR0L = (unsigned char) (ubrr & 0xFF);

    // set uart as emitter and transmitter
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    //8 bits character size
    UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01); 
    // enable interrupt from reception
    if (r_int)
        UCSR0B |= 1 << RXCIE0;
}

void    uart_tx(char c)
{
    // make sure the last buffer has been sent
    while (!(UCSR0A & (1 << UDRE0)))
    {

    }
    // load the char into the send buffer
    UDR0 = c;
}

void    uart_printstr(const char *str)
{
    while(*str)
    {
        while (!(UCSR0A & (1 << UDRE0)));
        UDR0 = *str++;
    }
}

char    uart_rx(void)
{
    char received;
    // the receive flags is RXCn
    while(!(UCSR0A & (1 << RXC0)))
        ;
    received = UDR0;
    return (received);
}


void    put_nbr_base(uint16_t x, uint8_t base)
{
    if (x >= base)
        put_nbr_base(x / base, base);
    uart_tx(HEXA[x % base]);
}

void        uart_str_code(char *str, uint16_t x, uint8_t base)
{
    if (str){
        uart_printstr(str);
        uart_printstr(": ");
    }
    if (base == 16)
        uart_printstr("0x");
    put_nbr_base(x, base);
    uart_printstr("\r\n");
}

uint8_t uart_read_string(char *buffer, uint8_t  len)
{
    uint8_t i = 0;
    ft_memset(buffer, len, 0); 
    while(1)
    {
        char rec = uart_rx();
        if (rec == '\r' || rec == '\n')
        {
            if (i > len){
                return (1);
            }
            break;
        }
            
        else if (rec == 127 || rec == 8)
        {
            if (i > 0){
                uart_printstr("\b \b");
                i--;
            }
            if (i < len)
                buffer[i] = 0;
        }
        else if (i < len)
        {
            uart_tx(rec);
            buffer[i] = rec;
            i++;
        }
        else{
            uart_printstr("\033[31m");
            uart_tx(rec);
            uart_printstr("\033[0m");
            i++;
        }
    }
    return (0);
}