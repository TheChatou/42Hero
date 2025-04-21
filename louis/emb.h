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
uint8_t     uart_read_string(char *buffer, uint8_t  len);


#define RED_PRINT "\033[31m"
#define BLACK_PRINT "\033[0m"
#define BLUE_PRINT "\033[34m"

//eeprom

#ifndef EEPROM_MAX
#define EEPROM_MAX 0x3ff
#endif

#ifndef EEPROM_SIZE
#define EEPROM_SIZE 1024
#endif

#ifndef EEPROM_MIN
#define EEPROM_MIN 0x00
#endif

#define MEMO_BCK 0x7f
#define FREE_BCK 0x8f
#define HEADER_SIZE 0x03
#define MEMO_START 0x04
#define LAST_BLOCK 0x3fb

#define EMPTY "<empty>"
#define ALREADY_EXIST 1
#define NO_SPACE_LEFT 2
#define FOUND 0
#define NOT_FOUND 1
#define INST_READ 0
#define INST_WRITE 1
#define INST_FORGET 2
#define INST_PRINT 3


uint8_t     eeprom_read(uint16_t adress, uint8_t *byte);
uint8_t     eeprom_write(uint16_t adress, uint8_t byte);
uint8_t     eeprom_write_vector(uint16_t adress, uint8_t *v, uint8_t len);
uint8_t     eeprom_read_vector(uint16_t adress, uint8_t *v, uint8_t len);
void        eeprom_hexdump(uint8_t c);
void        eeprom_hexdump_highlight(uint16_t highlight);
uint8_t     eeprom_get(char *key, uint16_t *cursor);
uint16_t    eeprom_insert(char *key, char *value);
uint8_t     eeprom_delete(char *key);
void        eeprom_mem_init(uint8_t force);
void        eeprom_defrag(uint16_t idx, uint16_t size);

//utils
void        ft_memset(uint8_t *s, uint16_t len, uint8_t byte);
uint8_t     ft_strcmp(char *a, char *b);
uint16_t    ft_strlen(char *s);
uint8_t     ft_memcmp(uint8_t *a, uint8_t *b, uint16_t len);
void        ft_memcpy(uint8_t *dest, uint8_t *src, uint16_t len);


/* 
{7f==occupied} keySize valueSize        key value header size = 3
{8f == free}   BlockSize BlockSize
Biggest occupied block 1 + 1 + 1 + 64 = 67
Min occupied block 1+1+1+1+1 = 5
{e1 == initialised}
*/

//SPI

#define BRIGHT_MASK 0b11100000

typedef uint8_t Color[4];

#define APA_DARK {0x00, 0x00, 0x00, 0x00}

void    spi_init();
void    spi_send(uint8_t data);
void    spi_send_led(uint8_t red, uint8_t green, uint8_t blue, uint8_t bright);
void    spi_send_off();
void    spi_send_start_frame();
void    spi_send_end_frame();
void    spi_send_color(Color c);
void    spi_set_all(Color first, Color second, Color third);


// EXPANDER

#ifndef EXPANDER_ADRESS
#define EXPANDER_ADRESS 0b00100000
#endif

#ifndef EXPANDER_ADRESS_LOW
#define EXPANDER_ADRESS_LOW 0b00000111
#endif

#define EXPANDER_IP0 0
#define EXPANDER_IP1 1
#define EXPANDER_OP0 2
#define EXPANDER_OP1 3
#define EXPANDER_PP0 4
#define EXPANDER_PP1 5
#define EXPANDER_CP0 6
#define EXPANDER_CP1 7

uint16_t    exp_read_ports();
uint8_t     exp_read_port(uint8_t p);

void    exp_conf_port(uint8_t p, uint8_t conf);
void    exp_conf_ports(uint8_t p0, uint8_t p1);

void    exp_set_output(uint8_t port, uint8_t output);
void    exp_set_both_output(uint8_t p0, uint8_t p1);