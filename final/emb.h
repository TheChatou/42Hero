#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef UART_BAUDRATE
#define UART_BAUDRATE 115200
#endif

#ifndef HEXA
#define HEXA "0123456789abcdef"
#endif

// UART
uint8_t     round_ubrr();
void        uart_init(uint8_t r_int);
void        uart_tx(char c);
void        uart_printstr(const char *str);
char        uart_rx(void);
void        uart_str_code(char *str, uint16_t x, uint8_t base);
void        put_nbr_base(uint16_t x, uint8_t base);





