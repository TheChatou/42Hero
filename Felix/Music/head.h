/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:56:12 by fcoullou          #+#    #+#             */
/*   Updated: 2025/03/31 17:07:43 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>


typedef uint8_t             ui8;
typedef uint16_t            ui16;
typedef uint32_t            ui32;
typedef volatile uint8_t    vui8;
typedef volatile uint16_t   vui16;
typedef volatile uint32_t   vui32;

// PORTS & PINS //
#define _D5_R   PD5
#define _D5_G   PD6
#define _D5_B   PD3
#define _D1     PB0
#define _D2     PB1
#define _D3     PB2
#define _D4     PB4
#define _SW1    PD2
#define _SW2    PD3
#define _POT    PC0
#define _LDR    PC1
#define _TEMP   PC2

//  MASKS //
#define R       (1 << _D5_R)
#define G       (1 << _D5_G)
#define B       (1 << _D5_B)
#define D5_RGB  R | G | B
#define D1      (1 << _D1)
#define D2      (1 << _D2)
#define D3      (1 << _D3)
#define D4      (1 << _D4)
#define D1234   D1 | D2 | D3 | D4
#define SW1     (1 << _SW1)
#define SW2     (1 << _SW2)
#define POT     (1 << _POT)
#define LDR     (1 << _LDR)
#define TEMP    (1 << _TEMP)
#define MASK_4BITS &0x0F


// RGB MODES //
#define MOD_R     (t_rgb_mod){255, 0, 0}
#define MOD_G     (t_rgb_mod){0, 255, 0}
#define MOD_B     (t_rgb_mod){0, 0, 255}
#define MOD_Y     (t_rgb_mod){125, 125, 0}
#define MOD_C     (t_rgb_mod){0, 125, 125}
#define MOD_M     (t_rgb_mod){125, 0, 125}
#define MOD_W     (t_rgb_mod){75, 75, 75}

// ANSI ESCAPE CODES //
#define NEXT_LINE       "\033[1E"
#define CURSOR_LEFT     "\033[D"
#define CURSOR_RIGHT    "\033[C"
#define CURSOR_UP       "\033[A"
#define CURSOR_DOWN     "\033[B"
#define CLEAR_LINE      "\033[2K"
#define CLEAR_SCREEN    "\033[2J"
#define EC_RED             "\033[31m"
#define EC_GREEN           "\033[32m"
#define EC_YELLOW          "\033[33m"
#define EC_BLUE            "\033[34m"
#define EC_MAGENTA         "\033[35m"
#define EC_CYAN            "\033[36m"
#define EC_RESET           "\033[0m"
#define EC_BOLD            "\033[1m"
#define EC_UNDERLINE       "\033[4m"
#define EC_ITALIC          "\033[3m"

// ENUMS //
typedef enum e_onoff
{
    OFF = 0,
    ON = 1
}           e_onoff;

typedef enum e_updo
{
    DOWN = 0,
    UP = 1
}           e_updo;

typedef enum e_colors
{
    OFFF = 0,
    RED = 1,
    GREEN = 2,
    BLUE = 3,
    YELLOW = 4,
    CYAN = 5,
    MAGENTA = 6,
    WHITE = 7
}           e_colors;

// STRUCTS //
typedef struct LED_RGB
{
    vui8    *p;
    ui8     r;
    ui8     g;
    ui8     b;
}           t_LED_RGB;

typedef struct rgb_mod
{
    ui8     r;
    ui8     g;
    ui8     b;
}           t_rgb_mod;

// MY_LIB_EMBEDDED FUNCTIONS // libebdd.c
void	clear_n_set(vui8 *port, ui8 bit);
void	toogle_bit(vui8 *port, ui8 bit);
void	set_bit(vui8 *port, ui8 bit);
void	clear_bit(vui8 *port, ui8 bit);
void    set_or_clear(vui8 *port, ui8 val, ui8 bit);
ui8     is_bit_set(vui8 *port, ui8 bit);
void	reset_registre(vui8 *reg);

void	set_color(t_LED_RGB led, t_rgb_mod mode);
void	clear_led_rgb(t_LED_RGB led);


char	change_case(char c);
ui8		ishex(char c);
ui8     hex(ui8 c1, ui8 c2);
ui8     rounded(float f);
ui8	    ft_strlen(char *str);
void	init_led_D5();


/// TIMER FUNCTIONS // timers.c
// TIMER 0 8 bits
void    tc0_clock(ui8 cs02, ui8 cs01, ui8 cs00);
void    tc0_mode(ui8 wgm02, ui8 wgm01, ui8 wgm00);
void    tc0_compare_match(ui8 com0A1, ui8 com0A0, ui8 com0B1, ui8 com0B0);
// TIMER 2 8 bits
void    tc2_clock(ui8 cs22, ui8 cs21, ui8 cs20);
void    tc2_mode(ui8 wgm22, ui8 wgm21, ui8 wgm20);
void    tc2_compare_match(ui8 com2A1, ui8 com2A0, ui8 com2B1, ui8 com2B0);
// TIMER 1 16 bits
void    tc1_clock(ui8 cs12, ui8 cs11, ui8 cs10);
void    tc1_mode(ui8 wgm13, ui8 wgm12, ui8 wgm11, ui8 wgm10);
void    tc1_compare_match(ui8 com1A1, ui8 com1A0, ui8 com1B1, ui8 com1B0);

// USART FUNCTIONS // usart.c
void    uart_init();
char    uart_rx();
void    uart_tx(char c);
void    uart_printstr(const char *str);
void    uart_print_ui16(ui16 value);
void    uart_print_hex_ui8(ui8 n);
void    uart_print_hex_ui16(ui16 n);
void    uart_print_int(int n);

// ADC //
void    set_adc_Prescaler(ui8 adps2, ui8 adps1, ui8 adps0);
void    set_ADCSRA_reg(ui8 aden, ui8 adate, ui8 adif, ui8 adie);
void    set_adc_Chanel(ui8 mux3, ui8 mux2, ui8 mux1, ui8 mux0);
void    set_adc_Voltage(ui8 refs1, ui8 refs0);
ui8     adc_read();
ui16    adc_read_16();
void    adc_pot_init();
void    adc_temp_init();
void    adc_ldr_init();
void    adc_intemp_init();

//  LEDS //
void wheel(uint8_t pos);
void set_rgb(uint8_t r, uint8_t g, uint8_t b);
