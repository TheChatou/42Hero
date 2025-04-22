/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libebdd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:00:46 by fcoullou          #+#    #+#             */
/*   Updated: 2025/04/07 16:52:57 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	clear_n_set(vui8 *port, ui8 bit)
{
	*port = (1 << bit);
}

void	toogle_bit(vui8 *port, ui8 bit)
{
	*port ^= (1 << bit);
}

void	set_bit(vui8 *port, ui8 bit)
{
	*port |= (1 << bit);
}

void	clear_bit(vui8 *port, ui8 bit)
{
	*port &= ~(1 << bit);
}

void	set_or_clear(vui8 *port, ui8 val, ui8 bit)
{
	if (val)
		set_bit(port, bit);
	else
		clear_bit(port, bit);
}

ui8 is_bit_set(vui8 *port, ui8 bit)
{
	return (*port & (1 << bit) & 1);
}

void	reset_registre(vui8 *reg)
{
	*reg = 0;
}

void	set_color(t_LED_RGB led, t_rgb_mod mode)
{
	if (mode.r)
		set_bit(led.p, led.r);
	if (mode.g)
		set_bit(led.p, led.g);
	if (mode.b)
		set_bit(led.p, led.b);
}

void	clear_led_rgb(t_LED_RGB led)
{
	*led.p &= ~(1 << led.r);
	*led.p &= ~(1 << led.g);
	*led.p &= ~(1 << led.b);
}

char	change_case(char c)
{
	if ((c >= 'a') && (c <= 'z'))
		return (c - 32);
	else if ((c >= 'A') && (c <= 'Z'))
		return (c + 32);
    else
		return (c);
}

ui8		ishex(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'))
		return (1);
	return (0);
}

ui8	hex(ui8 c1, ui8 c2)
{
	ui8 res = 0;
	
	if (c1 >= '0' && c1 <= '9')
		res = c1 - '0';
	else if (c1 >= 'a' && c1 <= 'f')
		res = c1 - 'a' + 10;
	res = res << 4;
	if (c2 >= '0' && c2 <= '9')
		res += c2 - '0';
	else if (c2 >= 'a' && c2 <= 'f')
		res += c2 - 'a' + 10;
	return (res);
}

ui8	rounded(float f)
{
    if (f - (int)f >= 0.5)
        return (ui8)f + 1;
    return (ui8)f;
}

ui8	ft_strlen(char *str)
{
	ui8 i = 0;
	
	while (str[i])
		i++;
	return (i);
}

void	init_led_D5()
{
	t_LED_RGB led = {&DDRD, PD5, PD6, PD7};
	
	set_bit(led.p, led.r);
	set_bit(led.p, led.g);
	set_bit(led.p, led.b);
}
