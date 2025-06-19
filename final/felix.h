/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   felix.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 23:17:45 by chatou            #+#    #+#             */
/*   Updated: 2025/06/19 14:52:00 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Letters with led matrix

#ifndef FELIX_H
#define FELIX_H

#include <avr/pgmspace.h>

const uint8_t alphabet[][4] PROGMEM = {
    // Espace
    {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    }
    // Logo '4'
    ,{
        0b00001100,
        0b00111100,
        0b11101111,
        0b10001111
    }
    // Logo '2'
    ,{
        0b11001111,
        0b10011111,
        0b11110001,
        0b11100011
    }
    // Logo 'H'
    ,{
        0b11111111,
        0b00011000,
        0b00011000,
        0b11111111
    }
    // Logo 'E'
    ,{
        0b11111111,
        0b11011011,
        0b11011011,
        0b11000011
    }
    // Logo 'R'
    ,{
        0b11111111,
        0b11011100,
        0b11010110,
        0b01100011
    }
    // Logo 'O'
    ,{
        0b01111110,
        0b11000011,
        0b11000011,
        0b01111110
    }
    // Espace
    ,{
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    }
};

// Nombre total de caractères définis (utile pour un modulo)
# define ALPHABET_SIZE (sizeof(alphabet) / sizeof(alphabet[0]))


#endif