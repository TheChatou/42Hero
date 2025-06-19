
import mido
import sys

def midi_to_freq(note):
    return int(round(440.0 * (2.0 ** ((note - 69) / 12.0))))

def extract_tracks(filename, num_tracks=4):
    mid = mido.MidiFile(filename)
    ticks_per_beat = mid.ticks_per_beat
    tempo = 500000  # default: 120 BPM

    # Récupération tempo depuis la track 0 si dispo
    for msg in mid.tracks[0]:
        if msg.type == 'set_tempo':
            tempo = msg.tempo
            break

    events = [[] for _ in range(num_tracks)]
    all_times_ms = set()

    # Prendre les 4 premières pistes musicales (avec note_on velocity > 0)
    musical_tracks = []
    for track in mid.tracks:
        if any(msg.type == 'note_on' and msg.velocity > 0 for msg in track):
            musical_tracks.append(track)
        if len(musical_tracks) >= num_tracks:
            break

    for i in range(num_tracks):
        track = musical_tracks[i]
        current_time = 0
        active_notes = {}

        for msg in track:
            current_time += msg.time
            if msg.type == 'set_tempo':
                tempo = msg.tempo
            elif msg.type == 'note_on' and msg.velocity > 0:
                active_notes[msg.note] = current_time
            elif msg.type in ('note_off', 'note_on') and msg.note in active_notes:
                start = active_notes.pop(msg.note)
                start_ms = mido.tick2second(start, ticks_per_beat, tempo) * 1000
                end_ms = mido.tick2second(current_time, ticks_per_beat, tempo) * 1000
                freq = midi_to_freq(msg.note)
                duration = int(end_ms - start_ms)
                events[i].append((int(start_ms), int(end_ms), freq))
                all_times_ms.update([int(start_ms), int(end_ms)])

    return events, tempo, sorted(all_times_ms)

def build_structure(events, all_times_ms, tempo_us, output_filename):
    all_times_ms = sorted(set(all_times_ms))
    tick_durations = [t2 - t1 for t1, t2 in zip(all_times_ms, all_times_ms[1:]) if t2 - t1 > 0]
    tick_ms = max(min(tick_durations), 125) if tick_durations else 125
    num_ticks = (all_times_ms[-1] // tick_ms) + 1

    tracks = [[0 for _ in range(num_ticks)] for _ in range(4)]
    leds = [0 for _ in range(num_ticks)]

    for track_id, notes in enumerate(events):
        for start_ms, end_ms, freq in notes:
            start_tick = start_ms // tick_ms
            end_tick = end_ms // tick_ms
            for tick in range(start_tick, min(end_tick, num_ticks)):
                tracks[track_id][tick] = freq
                leds[tick] |= (1 << track_id)

    with open(output_filename, "w") as f:
        f.write("const t_part generated PROGMEM = {\n")
        f.write("    .tracks = {\n")
        for tr in tracks:
            f.write("        { .note = { ")
            f.write(", ".join(str(n) for n in tr))
            f.write(" } },\n")
        f.write("    },\n")
        f.write("    .led = { ")
        f.write(", ".join(str(b) for b in leds))
        f.write(" },\n")
        f.write(f"    .tempo = {tick_ms},\n")
        f.write(f"    .length = {num_ticks}\n")
        f.write("};\n")

    print(f"✅ Généré : {output_filename} | tempo: {tick_ms} ms/tick | ticks: {num_ticks}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage : python3 midi_to_struct.py fichier.mid [output.h]")
        sys.exit(1)

    mid_file = sys.argv[1]
    out_file = sys.argv[2] if len(sys.argv) > 2 else "generated_part.h"

    events, tempo_us, time_marks = extract_tracks(mid_file)
    build_structure(events, time_marks, tempo_us, out_file)
