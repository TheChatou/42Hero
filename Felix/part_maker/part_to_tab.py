import re

# Fréquences triées comme dans ta table
note_freqs = [
    31, 33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58,
    65, 69, 73, 78, 82, 87, 92, 98, 104, 110, 117, 123,
    131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247,
    261, 277, 294, 311, 329, 349, 370, 392, 415, 440, 466, 493,
    523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 987,
    1046, 1108, 1174, 1244, 1318, 1396, 1479, 1567, 1661, 1760, 1864, 1975
]

note_names = [
    "B1", "C1", "c1", "D1", "d1", "E1", "F1", "f1", "G1", "g1", "A1", "a1",
    "C2", "c2", "D2", "d2", "E2", "F2", "f2", "G2", "g2", "A2", "a2", "B2",
    "C3", "c3", "D3", "d3", "E3", "F3", "f3", "G3", "g3", "A3", "a3", "B3",
    "C4", "c4", "D4", "d4", "E4", "F4", "f4", "G4", "g4", "A4", "a4", "B4",
    "C5", "c5", "D5", "d5", "E5", "F5", "f5", "G5", "g5", "A5", "a5", "B5",
    "C6", "c6", "D6", "d6", "E6", "F6", "f6", "G6", "g6", "A6", "a6", "B6"
]

NOTE_NONE = 0

def note_to_value(note):
    try:
        index = note_names.index(note)
        value = note_freqs[index]  # Retourne la fréquence correspondante
        print(f"✅ Note trouvée : {note} -> Fréquence : {value}")
        return value
    except ValueError:
        print(f"❌ Note inconnue : {note}")
        return NOTE_NONE

def parse_txt_file(filename):
    with open(filename, "r") as f:
        lines = [line.strip() for line in f if line.strip().startswith("PISTE")]

    tracks = [[] for _ in range(4)]
    for i, line in enumerate(lines[:4]):
        _, data = line.split("|", 1)
        blocks = re.split(r"\|", data.strip())
        for block in blocks:
            if len(block) == 0:
                continue
            # Découper chaque bloc en notes individuelles (par exemple, "E2--C3--" -> ["E2", "--", "C3", "--"])
            notes = [block[j:j+2] for j in range(0, len(block), 2)]
            for note in notes:
                note = note.strip()
                if note == "--":  # Si c'est un silence
                    tracks[i].append(NOTE_NONE)
                else:
                    tracks[i].append(note_to_value(note))  # Insère la fréquence directement

    for i, track in enumerate(tracks):
        if all(note == NOTE_NONE for note in track):
            tracks[i] = [0] * len(track)

    return tracks

def format_array(array, items_per_line=4):
    formatted_array = ""
    for i, item in enumerate(array):
        if i % items_per_line == 0:
            formatted_array += "\n"
        formatted_array += f"{item}, "
    return formatted_array.strip(", ")

def generate_header(tracks, output_filename="partition.h"):
    with open(output_filename, "w") as f:
        f.write("#pragma once\n\n")
        f.write("#include \"head.h\"\n\n")

        f.write("const t_part tetris_song PROGMEM = {\n")
        f.write("    .tracks = {\n")

        for i, track in enumerate(tracks):
            if all(note == 0 for note in track):  # Si la piste contient uniquement des silences
                f.write("        {\n            .note = {0}\n        },\n")
            else:
                f.write("        {\n            .note = {\n")
                f.write(format_array(track, items_per_line=20))  # 20 fréquences par ligne
                f.write("\n            }\n        },\n")

        f.write("    },\n")
        f.write(f"    .length = {len(tracks[0])}\n")
        f.write("};\n")

    print(f"✅ Fichier 'partition.h' généré avec succès !")

if __name__ == "__main__":
    tracks = parse_txt_file("starwars.txt")
    generate_header(tracks)
