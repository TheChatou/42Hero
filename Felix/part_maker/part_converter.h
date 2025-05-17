/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part_converter.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chatou <chatou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:02:51 by chatou            #+#    #+#             */
/*   Updated: 2025/04/23 15:38:22 by chatou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <math.h>
#include <avr/pgmspace.h>

#define TEMPS_MAX 68
#define TRACK_LENGTH 128
#define POLY_MAX 4

typedef struct {
    uint8_t note_index;  // Index vers notes_freqs[]
} t_note;

typedef struct {
    t_note steps[TRACK_LENGTH];  // 1 piste = TRACK_LENGTH steps
} t_track;

typedef struct {
    t_track tracks[POLY_MAX];    // 4 pistes max
    uint8_t length;              // Nombre total de steps
} t_part;

extern const t_part tetris_song;