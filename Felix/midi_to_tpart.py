
import mido
import sys
from collections import defaultdict

MAX_LENGTH = 595
POLY_MAX = 4

def midi_to_freq(note):
    return int(round(440.0 * (2.0 ** ((note - 69) / 12.0))))

def parse_midi(filename):
    mid = mido.MidiFile(filename)
    ticks_per_beat = mid.ticks_per_beat
    tracks_notes = [[] for _ in range(POLY_MAX)]
    event_times = set()

    for track_id, track in enumerate(mid.tracks[:POLY_MAX]):
        current_time = 0
        notes_on = {}

        for msg in track:
            current_time += msg.time
            if msg.type == 'note_on' and msg.velocity > 0:
                notes_on.setdefault(msg.note, []).append(current_time)
            elif (msg.type == 'note_off') or (msg.type == 'note_on' and msg.velocity == 0):
                if msg.note in notes_on and notes_on[msg.note]:
                    start = notes_on[msg.note].pop(0)
                    duration = current_time - start
                    start_ms = mido.tick2second(start, ticks_per_beat, 500000) * 1000
                    end_ms = mido.tick2second(current_time, ticks_per_beat, 500000) * 1000
                    freq = midi_to_freq(msg.note)
                    tracks_notes[track_id].append((int(start_ms), int(end_ms - start_ms), freq))
                    event_times.add(int(start_ms))
                    event_times.add(int(end_ms))

    min_duration = min((d for tr in tracks_notes for (_, d, _) in tr if d > 0), default=125)
    tick_ms = min_duration
    length = int((max(event_times) // tick_ms) + 1)
    track_arrays = [[0] * length for _ in range(POLY_MAX)]
    led_array = [0] * length

    for track_id in range(POLY_MAX):
        for start_ms, duration_ms, freq in tracks_notes[track_id]:
            start_tick = start_ms // tick_ms
            end_tick = (start_ms + duration_ms) // tick_ms
            for tick in range(start_tick, min(end_tick, length)):
                track_arrays[track_id][tick] = freq
                led_array[tick] |= (1 << track_id)

    return track_arrays, led_array, tick_ms, length

def write_header(track_arrays, led_array, tick_ms, length, output_path):
    with open(output_path, "w") as f:
        f.write("const t_part generated PROGMEM = {\n")
        f.write("    .tracks = {\n")
        for t in track_arrays:
            notes_str = ', '.join(str(n) for n in t[:MAX_LENGTH])
            f.write(f"        {{ .note = {{ {notes_str} }} }},\n")
        f.write("    },\n")
        led_str = ', '.join(str(n) for n in led_array[:MAX_LENGTH])
        f.write(f"    .led = {{ {led_str} }},\n")
        f.write(f"    .tempo = {tick_ms},\n")
        f.write(f"    .length = {length}\n")
        f.write("};\n")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 midi_to_tpart.py <fichier.mid>")
        sys.exit(1)

    midi_file = sys.argv[1]
    output_file = "generated_part.h"
    track_arrays, led_array, tick_ms, length = parse_midi(midi_file)
    write_header(track_arrays, led_array, tick_ms, length, output_file)
    print(f"✅ Fichier généré : {output_file}")
