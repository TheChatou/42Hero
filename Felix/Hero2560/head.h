/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chatou <chatou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:56:12 by fcoullou          #+#    #+#             */
/*   Updated: 2025/06/18 16:52:09 by chatou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <avr/pgmspace.h>

typedef uint8_t             ui8;
typedef uint16_t            ui16;
typedef uint32_t            ui32;
typedef volatile uint8_t    vui8;
typedef volatile uint16_t   vui16;
typedef volatile uint32_t   vui32;

#define MASK_4BITS &0x0F


// RGB MODES //
#define MOD_R     (t_rgb_mod){255, 0, 0}
#define MOD_G     (t_rgb_mod){0, 255, 0}
#define MOD_B     (t_rgb_mod){0, 0, 255}
#define MOD_Y     (t_rgb_mod){125, 125, 0}
#define MOD_C     (t_rgb_mod){0, 125, 125}
#define MOD_M     (t_rgb_mod){125, 0, 125}
#define MOD_W     (t_rgb_mod){75, 75, 75}


#define NOTES_MAX 4
#define POLY_MAX 4
#define TEMPS_MAX 548
#define TEMPS_MAX_2 211
#define MAX_LENGTH 595

#define T_1_4   150
#define T_1_2   300
#define T_3_4   450
#define T_1_8   75
#define T_1_16  37
#define T_1_32  18
#define T_1     600

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

// ENUMS //
typedef enum e_onoff
{
    OFF = 0,
    ON = 1
}           e_onoff;

typedef struct
{
    ui16 note[2000];          // 1 piste = MAX_LENGTH notes
}           t_track;

typedef struct
{
    t_track tracks[4];       // 4 pistes max
    ui16 led[2000];           // LEDs à allumer pour chaque tick
    ui16 tempo;                     // Tempo de la musique
    ui16 length;                    // Nombre total de ticks
}           t_part;

// MY_LIB_EMBEDDED FUNCTIONS // libebdd.c
void	clear_n_set(vui8 *port, ui8 bit);
void	toogle_bit(vui8 *port, ui8 bit);
void	set_bit(vui8 *port, ui8 bit);
void	clear_bit(vui8 *port, ui8 bit);
void    set_or_clear(vui8 *port, ui8 val, ui8 bit);
ui8     is_bit_set(vui8 *port, ui8 bit);
void	reset_registre(vui8 *reg);

char	change_case(char c);
ui8		ishex(char c);
ui8     hex(ui8 c1, ui8 c2);
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
// TIMER 3 16 bits
void    tc3_clock(ui8 cs32, ui8 cs31, ui8 cs30);
void    tc3_mode(ui8 wgm33, ui8 wgm32, ui8 wgm31, ui8 wgm30);
void    tc3_compare_match(ui8 com3A1, ui8 com3A0, ui8 com3B1, ui8 com3B0);
// TIMER 4 16 bits
void    tc4_clock(ui8 cs42, ui8 cs41, ui8 cs40);
void    tc4_mode(ui8 wgm43, ui8 wgm42, ui8 wgm41, ui8 wgm40);
void    tc4_compare_match(ui8 com4A1, ui8 com4A0, ui8 com4B1, ui8 com4B0);
// TIMER 5 16 bits
void    tc5_clock(ui8 cs52, ui8 cs51, ui8 cs50);
void    tc5_mode(ui8 wgm53, ui8 wgm52, ui8 wgm51, ui8 wgm50);
void    tc5_compare_match(ui8 com5A1, ui8 com5A0, ui8 com5B1, ui8 com5B0);

// USART FUNCTIONS // usart.c
ui8     rounded(float f);
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
