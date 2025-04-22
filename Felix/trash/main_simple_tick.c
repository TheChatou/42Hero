/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:47:16 by fcoullou          #+#    #+#             */
/*   Updated: 2025/03/31 17:45:01 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

#define SPEAKER_PIN PB1 // Pin D9 est PB1 sur l'Arduino Uno

int main(void)
{
    // Configure PB1 comme une sortie (D9)
    DDRB |= (1 << SPEAKER_PIN);

    while (1)
    {
        // Génère un son (mettre PB1 à HIGH)
        PORTB |= (1 << SPEAKER_PIN);
        _delay_ms(500); // Attente de 500ms (durée du son)

        // Arrête le son (mettre PB1 à LOW)
        PORTB &= ~(1 << SPEAKER_PIN);
        _delay_ms(500); // Attente de 500ms (silence)
    }

    return 0;
}