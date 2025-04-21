#include "emb.h"

void    spi_init()
{
    // enable MOSI and SCK and SS
    DDRB = (1 << DDB3) | (1 << DDB5) | (1 << DDB2);
    // enable SPI in MaSTeR mode and clock f_cpu/16 == 1 Mhz
    SPCR = (1 << SPE)  | (1 << MSTR) | (1 << SPR0);
    SPSR = 0;
}

void    spi_send(uint8_t data)
{
    SPDR = data;
    while(!(SPSR & (1 << SPIF)))
        ;
}


void    spi_send_led(uint8_t red, uint8_t green, uint8_t blue, uint8_t bright)
{
    spi_send(BRIGHT_MASK | bright);
    spi_send(blue);
    spi_send(green);
    spi_send(red);
}


void    spi_send_off()
{
    spi_send(BRIGHT_MASK | 0x00);
    spi_send(0x00);
    spi_send(0x00);
    spi_send(0x00);
}

void    spi_send_start_frame()
{
    for (uint8_t i = 0; i < 4; i++)
    {
        spi_send(0x00);
    }
}

void    spi_send_end_frame()
{
    for (uint8_t i = 0; i < 4; i++)
    {
        spi_send(0xff);
    }
}

void    spi_send_color(Color c)
{
    spi_send(BRIGHT_MASK | c[3]);
    spi_send(c[2]);
    spi_send(c[1]);
    spi_send(c[0]);
}
void    spi_set_all(Color first, Color second, Color third)
{
    spi_send_start_frame();
    spi_send_color(first);
    spi_send_color(second);
    spi_send_color(third);
    spi_send_end_frame();
}