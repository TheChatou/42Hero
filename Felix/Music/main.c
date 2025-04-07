/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chatou <chatou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:47:16 by fcoullou          #+#    #+#             */
/*   Updated: 2025/04/05 15:15:32 by chatou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"
#include "tetris.c"

#define SPEAKER_PIN PB1 // Pin D9 est PB1 sur l'Arduino Uno

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

#define T_1_8  125
#define T_1_16 62
#define T_1_4  250
#define T_1_2  500
#define T_3_4  750
#define T_1__  1000

// Correspondance entre noms de notes et fréquences
int get_frequency(char* note)
{
    if (strcmp(note, "C3") == 0) return C3;
    if (strcmp(note, "c3") == 0) return c3;
    if (strcmp(note, "D3") == 0) return D3;
    if (strcmp(note, "d3") == 0) return d3;
    if (strcmp(note, "E3") == 0) return E3;
    if (strcmp(note, "F3") == 0) return F3;
    if (strcmp(note, "f3") == 0) return f3;
    if (strcmp(note, "G3") == 0) return G3;
    if (strcmp(note, "g3") == 0) return g3;
    if (strcmp(note, "A3") == 0) return A3;
    if (strcmp(note, "a3") == 0) return a3;
    if (strcmp(note, "B3") == 0) return B3;
    if (strcmp(note, "C4") == 0) return C4;
    if (strcmp(note, "c4") == 0) return c4;
    if (strcmp(note, "D4") == 0) return D4;
    if (strcmp(note, "d4") == 0) return d4;
    if (strcmp(note, "E4") == 0) return E4;
    if (strcmp(note, "F4") == 0) return F4;
    if (strcmp(note, "f4") == 0) return f4;
    if (strcmp(note, "G4") == 0) return G4;
    if (strcmp(note, "g4") == 0) return g4;
    if (strcmp(note, "A4") == 0) return A4;
    if (strcmp(note, "a4") == 0) return a4;
    if (strcmp(note, "B4") == 0) return B4;
    if (strcmp(note, "C5") == 0) return C5;
    if (strcmp(note, "c5") == 0) return c5;
    if (strcmp(note, "D5") == 0) return D5;
    if (strcmp(note, "d5") == 0) return d5;
    if (strcmp(note, "E5") == 0) return E5;
    if (strcmp(note, "F5") == 0) return F5;
    if (strcmp(note, "f5") == 0) return f5;
    if (strcmp(note, "G5") == 0) return G5;
    if (strcmp(note, "g5") == 0) return g5;
    if (strcmp(note, "A5") == 0) return A5;
    if (strcmp(note, "a5") == 0) return a5;
    if (strcmp(note, "B5") == 0) return B5;
    if (strcmp(note, "C6") == 0) return C6;
    if (strcmp(note, "N0") == 0) return N0;
    
    return 0;
}


// Fonction pour parser les données de la partition depuis une chaîne
void parse_partition_from_string(const char* data, Partition* p)
{
    int i = 0;

    // Copie des données pour pouvoir les manipuler avec strtok
    char buffer[strlen(data) + 1];
    strcpy(buffer, data);

    // Récupère chaque ligne
    char* line_ptr = strtok(buffer, "\n");
    line_ptr = strtok(NULL, "\n"); // Ignore la première ligne (l'en-tête)

    while (line_ptr && i < NOTES_MAX)
    {
        char note[4];
        sscanf(line_ptr, "%3s |", note); // Récupère "E5", "f5", etc.
        int freq = get_frequency(note);

        uart_printstr("___Note: ");
        uart_printstr(note);
        uart_printstr("___\r\n");
        char* token = strtok(line_ptr + 4, "|"); // Saute "E5 |"
        int j = 0;

        while (token && j < TEMPS_MAX)
        {
            // Si un "X" est trouvé, la note est jouée à ce moment-là
            if (strchr(token, 'X') != NULL)
            {
                p->notes[i][j].frequency = freq;    // Assigne la fréquence de la note
                p->notes[i][j].duration = T_1_4;   // Durée de la note (1/4 de temps)
            }
            else
            {
                p->notes[i][j].frequency = 0;      // Pas de note jouée
                p->notes[i][j].duration = T_1_4;   // Durée par défaut
            }

            token = strtok(NULL, "|"); // Récupère le prochain "temps"
            j++;
        }
        line_ptr = strtok(NULL, "\n"); // Passe à la ligne suivante
        i++;
    }
}

// Fonction pour jouer une note
void play_note(uint16_t frequency, uint16_t duration_ms)
{
    if (frequency == 0)
    {
        PORTB &= ~(1 << SPEAKER_PIN); // S'assurer que le haut-parleur est éteint
        _delay_loop_2(duration_ms); // Pause si la note est 0
        return;
    }
    
    uint16_t period = (1000000 / frequency);
    uint16_t cycles = duration_ms;

    for (uint16_t i = 0; i < cycles; i++)
    {
        PORTB |= (1 << SPEAKER_PIN);
        _delay_loop_2(period);
        PORTB &= ~(1 << SPEAKER_PIN);
        _delay_loop_2(period);
    }
}

int main(void)
{
    // Configure PB1 comme une sortie
    DDRB |= (1 << SPEAKER_PIN);

    uart_init();

    uart_printstr("HELLO\r\n");
    uart_print_ui16(TEMPS_MAX);

    
    // Partition lue depuis la chaîne de caractères
    Partition p = {0};
    parse_partition_from_string(tetris_data, &p);

    uart_printstr("Partition lue:\r\n");
    // Lecture et exécution de la partition
    for (int i = 0; i < NOTES_MAX; i++)
    {
        for (int j = 0; j < TEMPS_MAX; j++)
        {
            // uart_print_ui16(i);
            // uart_printstr(" , ");
            // uart_print_ui16(j);
            // uart_printstr("\r\n Note: ");
            // uart_print_ui16(p.notes[i][j].frequency);
            if (p.notes[i][j].frequency != 0)
            {
                uart_printstr("Note: ");
                uart_print_ui16(p.notes[i][j].frequency);
                uart_printstr(" Hz, Durée: ");
                uart_print_ui16(p.notes[i][j].duration);
                uart_printstr(" ms\n");
                
                // Joue la note si la fréquence est différente de 0
                play_note(p.notes[i][j].frequency, p.notes[i][j].duration);
                _delay_ms(100);
            }
        }
    }

    return 0;
}
