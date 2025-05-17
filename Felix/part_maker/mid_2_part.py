import pretty_midi
import numpy as np

NOTE_NAMES = ['C', 'c', 'D', 'd', 'E', 'F', 'f', 'G', 'g', 'A', 'a', 'B']

def midi_to_freq(note):
    return int(round(440.0 * (2 ** ((note - 69) / 12.0))))

def find_min_resolution(midi):
    durations = []
    for inst in midi.instruments:
        for note in inst.notes:
            durations.append(note.end - note.start)
    min_dur = min([d for d in durations if d > 0])
    return round(min_dur, 3)

def parse_midi_to_tracks(filename, max_tracks=4):
    midi = pretty_midi.PrettyMIDI(filename)
    resolution = find_min_resolution(midi)
    print(f"🕒 Résolution détectée : {resolution}s")

    total_time = midi.get_end_time()
    steps = int(total_time / resolution) + 1
    tracks = [[0] * steps for _ in range(max_tracks)]

    all_notes = []
    for instrument in midi.instruments:
        for note in instrument.notes:
            all_notes.append((note.start, note.pitch))

    all_notes.sort(key=lambda x: x[0])

    for start_time, pitch in all_notes:
        t = int(start_time / resolution)
        freq = midi_to_freq(pitch)
        for track in tracks:
            if track[t] == 0:
                track[t] = freq
                break  # Place sur la première piste dispo

    return tracks, steps

def write_header(tracks, length, output_file="test_partition.h"):
    with open(output_file, "w") as f:
        f.write("#pragma once\n\n#include \"head.h\"\n\n")
        f.write("const t_part test PROGMEM = {\n")
        f.write("    .tracks = {\n")
        for track in tracks:
            f.write("        {\n            .note = {\n                ")
            f.write(', '.join(str(x) for x in track))
            f.write("\n            }\n        },\n")
        f.write("    },\n")
        f.write(f"    .length = {length}\n")
        f.write("};\n")

    print(f"✅ Fichier généré : {output_file}")

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print("Utilisation : python3 midi_to_header.py fichier.mid")
        sys.exit(1)
    midi_file = sys.argv[1]
    tracks, steps = parse_midi_to_tracks(midi_file)
    write_header(tracks, steps)
