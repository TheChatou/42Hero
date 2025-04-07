/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:47:16 by fcoullou          #+#    #+#             */
/*   Updated: 2025/04/07 15:50:23 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

#define SPEAKER_PIN PB1 // Pin D9 est PB1 sur l'Arduino Uno

// Correspondance entre noms de notes et fréquences
int get_frequency(const char* note)
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
    if (strcmp(note, "--") == 0) return N0; // Silence
    
    return 0;
}

void    print_t_part(t_part *p)
{
    for (int i = 0; i < TEMPS_MAX; i++)
    {
        uart_print_int(i + 1);
        uart_printstr(" - ");
        uart_print_ui16(p->notes[i].frequency);
        uart_printstr(" Hz, Durée: ");
        uart_print_ui16(p->notes[i].duration);
        uart_printstr(" ms\r\n");
    }
}

// Fonction pour parser les données de la partition depuis une chaîne
void parse_partition_from_string(const char** data, t_part *p)
{
    int i = 0;
        
    while (i < NOTES_MAX)
    {
        char note[3] = { data[i][0], data[i][1], '\0' };
        int freq = get_frequency(note);

        int j = 4;
        int t = 0;
        while (data[i][j] != '\0')
        {
            if (data[i][j] == '|')
            {
                j++;
                continue;
            }
            else if (data[i][j] == 'X')
            {
                p->notes[t].duration = T_1_4;
                p->notes[t].frequency = freq;
            }
            t++;
            j++;
        }
        i++;
    }
    // print_t_part(p);
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
        PORTB ^= (1 << SPEAKER_PIN);
        _delay_loop_2(period);
    }
}

int main(void)
{
    // Configure PB1 comme une sortie
    DDRB |= (1 << SPEAKER_PIN);

    uart_init();

// const char *tetris_data[] = {
//     "E5 |----|----|----|----|----|----|----|----|----|--X-|----|----|----|----|----|----|",
//     "f5 |----|----|----|----|----|----|----|----|---X|----|----|----|----|----|----|----|",
//     "D5 |----|----|----|----|----|----|----|----|----|----|X---|----|----|----|----|----|",
//     "C5 |----|----|----|----|----|----|----|----|----|----|--X-|----|----|----|----|----|",
//     "c5 |X---|----|----|X---|----|--X-|----|----|----|----|----|----|--X-|----|X---|----|",
//     "B4 |----|XX--|----|--X-|----|X---|----|----|-X--|----|----|----|X---|----|----|----|",
//     "A4 |---X|--X-|---X|---X|---X|----|X---|----|----|----|---X|---X|----|X---|----|----|",
//     "g4 |--X-|---X|----|----|X-X-|----|----|----|----|----|----|X-X-|----|----|X---|----|",
//     "f4 |----|----|X-X-|----|----|----|--X-|X---|----|----|----|----|----|--X-|X---|XXXX|" };
//     //   1    5    9    13   17   21   25   29   33   37   41   45   49   53   57   61   
    

const char *tetris_data[] = {
    "A5 |----|----|----|----|----|----|----|----|----|X---|----|----|----|----|----|----|----|",
    "G5 |----|----|----|----|----|----|----|----|----|--X-|----|----|----|----|----|----|----|",
    "F5 |----|----|----|----|----|----|----|----|---X|---X|----|----|----|----|----|----|----|",
    "E5 |X---|----|----|X---|----|--X-|----|----|----|----|X---|X---|----|--X-|----|----|----|",
    "D5 |----|X---|----|--X-|----|X---|----|----|-X--|----|----|--X-|----|X---|----|----|----|",
    "C5 |---X|--X-|---X|---X|---X|----|X---|----|----|----|---X|---X|---X|----|X---|----|----|",
    "B4 |--X-|---X|----|----|X---|----|----|----|----|----|----|----|X-X-|----|----|----|----|",
    "A4 |----|----|X-X-|----|----|----|--X-|X---|----|----|----|----|----|----|----|X---|X---|" };
    //   1    5    9    13   17   21   25   29   33   37   41   45   49   53   57   61   65

    t_part p = {0}; // Initialisation de la partition
    
    
    uart_printstr("Lecture de la partition...\r\n");
    // Partition lue depuis la chaîne de caractères
    uart_printstr("before parse\r\n");
    parse_partition_from_string(tetris_data, &p);

    uart_printstr("Partition lue:\r\n");
    while (1)
    {
        // Lecture et exécution de la partition
        for (int t = 0; t < TEMPS_MAX; t++)
        {            
            play_note(p.notes[t].frequency / 2, p.notes[t].duration * 2);
            // _delay_ms(50);
        }
        _delay_ms(1000);
    }

    return 0;
}
