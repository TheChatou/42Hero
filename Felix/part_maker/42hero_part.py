import pretty_midi

NOTE_NAMES = ['C', 'c', 'D', 'd', 'E', 'F',
              'f', 'G', 'g', 'A', 'a', 'B']

def note_name(midi_note):
    octave = midi_note // 12 - 1
    name = NOTE_NAMES[midi_note % 12]
    return f"{name}{octave}"

def parse_midi_to_tetris_data(filename, resolution=0.25):
    midi = pretty_midi.PrettyMIDI(filename)
    instrument = midi.instruments[0]  # Prend la première piste
    note_grid = {}

    # Calcule la durée totale en secondes
    total_time = midi.get_end_time()
    steps = int(total_time // resolution) + 1

    # Prépare une grille vide
    for n in range(21, 109):  # Plage de notes MIDI normales (piano)
        note_grid[n] = ['----'] * steps

    # Remplir la grille avec précision au quart de temps
    for note in instrument.notes:
        start = note.start / resolution  # Position de début en quarts de temps
        end = note.end / resolution      # Position de fin en quarts de temps
        start_step = int(start)          # Temps de début (entier)
        end_step = int(end)              # Temps de fin (entier)

        for t in range(start_step, min(end_step + 1, steps)):
            # Détermine les quarts de temps à activer pour cette note
            for quarter in range(4):
                quarter_time = t + quarter * 0.25
                if start <= quarter_time < end:
                    # Active le quart de temps correspondant
                    note_grid[note.pitch][t] = (
                        note_grid[note.pitch][t][:quarter] + 'X' +
                        note_grid[note.pitch][t][quarter + 1:]
                    )

    # Génère les lignes pour tetris_data
    tetris_data = []
    for midi_note in sorted(note_grid.keys()):
        note_name_str = note_name(midi_note)
        ascii_line = f"{note_name_str} |" + "|".join(note_grid[midi_note]) + "|"
        # Ajouter uniquement les lignes contenant 'X'
        if 'X' in ascii_line:
            tetris_data.append(f"\"{ascii_line}\"")

    # Ajouter la ligne de numérotation
    time_line = "    //" + "".join(f"{i:>5}" for i in range(1, steps + 1, 4))
    tetris_data.append(time_line)

    return tetris_data

def save_tetris_data_to_file(tetris_data, output_filename):
    with open(output_filename, 'w') as f:
        f.write("const char *tetris_data[] = {\n")
        f.write(",\n".join(tetris_data))
        f.write("\n};\n")

if __name__ == "__main__":
    import sys

    if len(sys.argv) < 2:
        print("Usage: python3 42hero_part.py <input_midi_file>")
        sys.exit(1)

    input_filename = sys.argv[1]
    output_filename = "tetris_data.c"  # Nom du fichier de sortie

    # Convertir le fichier MIDI en données tetris_data
    tetris_data = parse_midi_to_tetris_data(input_filename)

    # Sauvegarder dans un fichier
    save_tetris_data_to_file(tetris_data, output_filename)

    print(f"Transcription sauvegardée dans {output_filename}")
