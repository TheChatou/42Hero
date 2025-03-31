/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:09:02 by fcoullou          #+#    #+#             */
/*   Updated: 2025/03/15 20:14:39 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void wheel(uint8_t pos)
{
    pos = 255 - pos;
    if (pos < 85)
    {
        set_rgb(255 - pos * 3, 0, pos * 3);
    }
    else if (pos < 170)
    {
        pos = pos - 85;
        set_rgb(0, pos * 3, 255 - pos * 3);
    }
    else
    {
        pos = pos - 170;
        set_rgb(pos * 3, 255 - pos * 3, 0);
    }
}

void    init_rgb()
{
    DDRD |= R | G | B;
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    OCR0A = r;
    OCR0B = g;
    OCR2B = b;
}
