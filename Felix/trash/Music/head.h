/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chatou <chatou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:56:12 by fcoullou          #+#    #+#             */
/*   Updated: 2025/04/21 23:47:27 by chatou           ###   ########.fr       */
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
#define TEMPS_MAX 548
#define TEMPS_MAX_2 211

// Fréquences des notes
#define N0  0
#define C3  131
#define c3  139
#define D3  147
#define d3  156
#define E3  165
#define F3  175
#define f3  185
#define G3  196
#define g3  208
#define A3  220
#define a3  233
#define B3  247
#define C4  261
#define c4  277
#define D4  294
#define d4  311
#define E4  329
#define F4  349
#define f4  370
#define G4  392
#define g4  415
#define A4  440
#define a4  466
#define B4  493
#define C5  523
#define c5  554
#define D5  587
#define d5  622
#define E5  659
#define F5  698
#define f5  740
#define G5  784
#define g5  831
#define A5  880
#define a5  932
#define B5  987
#define C6  1046

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

typedef struct s_notes
{
    int     freqs[NOTES_MAX];                          // Durée en millisecondes
    int     count;                           // Nombre de notes dans le temps
}           t_notes;

typedef struct s_part
{
    t_notes    notes[TEMPS_MAX]; // Tableau de notes sur une timeline
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
