import pretty_midi
import sys

NOTE_NAMES = ['C', 'c', 'D', 'd', 'E', 'F',
              'f', 'G', 'g', 'A', 'a', 'B']

def note_name(midi_note):
    octave = midi_note // 12 - 1
    name = NOTE_NAMES[midi_note % 12]
    return f"{name}{octave}"

def make_empty_grid(length):
    return ["--"] * length

def parse_midi_fixed_tracks(filename, resolution=0.125, max_tracks=4):
    midi = pretty_midi.PrettyMIDI(filename)
    total_time = midi.get_end_time()
    steps = int(total_time / resolution) + 1

    # Crée 4 pistes vides
    tracks = [make_empty_grid(steps) for _ in range(max_tracks)]

    # Trie toutes les notes de tous les instruments
    all_notes = []
    for instrument in midi.instruments:
        for note in instrument.notes:
            all_notes.append((note.start, note))  # tri par temps
    all_notes.sort(key=lambda x: x[0])

    for start_time, note in all_notes:
        t = int(start_time / resolution)
        pitch = note_name(note.pitch)

        placed = False
        for track in tracks:
            if track[t] == "--":
                track[t] = pitch
                placed = True
                break

        # if not placed:
        #     print(f"❌ Trop de notes simultanées à t={t * resolution:.3f}s — impossible de caser plus de 4 voix !")
        #     sys.exit(1)

    return steps, tracks

def format_output(steps, tracks):
    output_lines = []
    for i, line in enumerate(tracks):
        formatted = f"PISTE{i+1} |"
        for j in range(steps):
            formatted += line[j]
            if (j + 1) % 4 == 0:
                formatted += "|"
        output_lines.append(formatted)
    return output_lines

def save_output_to_file(output_lines, output_filename):
    with open(output_filename, 'w') as f:
        for line in output_lines:
            f.write(line + "\n")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 midi_to_txt_4pistes.py <input_midi_file> [resolution]")
        sys.exit(1)

    input_filename = sys.argv[1]
    resolution = float(sys.argv[2]) if len(sys.argv) > 2 else 0.125  # par défaut : 1/8e de temps
    output_filename = "tetris_output.txt"

    steps, tracks = parse_midi_fixed_tracks(input_filename, resolution=resolution)
    output_lines = format_output(steps, tracks)
    save_output_to_file(output_lines, output_filename)

    print(f"✅ Fichier généré avec résolution {resolution} : {output_filename}")
