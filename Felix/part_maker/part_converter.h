/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part_converter.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chatou <chatou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:02:51 by chatou            #+#    #+#             */
/*   Updated: 2025/04/21 21:58:27 by chatou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <math.h>



#define NOTES_MAX 4
#define TEMPS_MAX 548

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

typedef struct s_notes
{
    int     freqs[NOTES_MAX];                          // Durée en millisecondes
    int     count;                           // Nombre de notes dans le temps
}           t_notes;

typedef struct s_part
{
    t_notes    notes[TEMPS_MAX]; // Tableau de notes sur une timeline
}           t_part;

// Convertir une note MIDI en fréquence
int midi_note_to_frequency(int midi_note);

// Convertir une partition MIDI en tableau C
void convert_partition_to_c(const char *input_filename, const char *output_filename, int notes_max);
