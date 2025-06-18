/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libebdd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:00:46 by fcoullou          #+#    #+#             */
/*   Updated: 2025/06/18 18:55:07 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parts.h"

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





