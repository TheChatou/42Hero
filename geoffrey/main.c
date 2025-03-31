/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:14:31 by gburtin           #+#    #+#             */
/*   Updated: 2025/03/31 17:50:57 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// Pin definitions for the Arduino Uno (assuming we're using Arduino pins)
// Modify these if you're using a different microcontroller or pins
#define DATA_PIN PB0  // Pin 8 on Arduino (Data Pin)
#define LATCH_PIN PB2 // Pin 10 on Arduino (Latch Pin)
#define CLOCK_PIN PB4 // Pin 12 on Arduino (Clock Pin)

void	shiftOut(uint8_t data)
{
	for (int i = 7; i >= 0; i--)
	{
		// Shift out the data, bit by bit
		if (data & (1 << i))
		{
			PORTB |= (1 << DATA_PIN); // Set data pin high
		}
		else
		{
			PORTB &= ~(1 << DATA_PIN); // Set data pin low
		}
		// Pulse the clock pin to shift the data bit
		PORTB |= (1 << CLOCK_PIN);  // Set clock pin high
		PORTB &= ~(1 << CLOCK_PIN); // Set clock pin low
	}
}

void	latch(void)
{
	// Latch the data into the shift register
	PORTB |= (1 << LATCH_PIN);  // Set latch pin high
	PORTB &= ~(1 << LATCH_PIN); // Set latch pin low
}

int	main(void)
{
	// Set DATA_PIN, LATCH_PIN, and CLOCK_PIN as output
	DDRB |= (1 << DATA_PIN) | (1 << LATCH_PIN) | (1 << CLOCK_PIN);

	while (1)
	{
		// Turn on all LEDs (binary 11111111)
		shiftOut(0b01111000); // Send 0xFF (all high) to the shift register
		latch();              // Latch the data to the outputs
		_delay_ms(1000);      // Wait for 1 second

		// Turn off all LEDs (binary 00000000)
		shiftOut(0x00);  // Send 0x00 (all low) to the shift register
		latch();         // Latch the data to the outputs
		_delay_ms(1000); // Wait for 1 second
	}

	return (0);
}