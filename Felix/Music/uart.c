/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uart.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chatou <chatou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:22:04 by fcoullou          #+#    #+#             */
/*   Updated: 2025/04/05 14:58:08 by chatou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

ui8	rounded(float f)
{
    if (f - (int)f >= 0.5)
        return (ui8)f + 1;
    return (ui8)f;
}

void    uart_init()
{
    float ubrr_f = (float)F_CPU / (16 * BAUD_RATE) - 1;
    ui8 ubrr = (ui8)rounded(ubrr_f);
    
    UBRR0H = ubrr >> 8;
    UBRR0L = ubrr & 255;
    
    UCSR0B = (1 << TXEN0);
    
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);     // 8 bits, 1 stop bit, pas de parité (8N1)
}

void    uart_tx(const char c)
{
    while (!(UCSR0A & (1 << UDRE0)));           // Attendre que le registre soit prêt
    UDR0 = c;                                   // Envoyer le caractère 
}

char    uart_rx()
{
    while (!(UCSR0A & (1 << RXC0)));            // Attendre qu'une donnée soit reçue
    return UDR0;                                // Retourner la donnée reçue
}

void    uart_printstr(const char *str)
{
    while (*str)
        uart_tx(*str++);
}

void uart_print_ui16(ui16 value)
{
    if (value == 0)
    {
        uart_tx('0');
        return;
    }

    char buffer[5];  
    int i = 0;

    while (value > 0)
    {
        buffer[i++] = '0' + (value % 10); 
        value /= 10;
    }

    for (int j = i - 1; j >= 0; j--)
        uart_tx(buffer[j]);
}

void    uart_print_hex_ui8(ui8 n)
{
    char hex[16] = "0123456789ABCDEF";

    uart_tx(hex[(n >> 4) MASK_4BITS]);
    uart_tx(hex[n MASK_4BITS]);
}

void    uart_print_int(int n)
{
    if (n < 0)
    {
        uart_tx('-');
        n = -n;
    }

    uart_print_ui16(n);
}

void    uart_print_hex_ui16(ui16 n)
{
    uart_print_hex_ui8(n >> 8);
    uart_print_hex_ui8(n);
}
