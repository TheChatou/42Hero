from mido import MidiFile, MidiTrack

input_file = "green-hill-zone-8-.mid"
output_file = "sonic.mid"

# Indices des pistes à supprimer
pistes_a_supprimer = [3, 4, 5, 7, 8]  # Tu mets ici toutes les pistes que tu veux virer

mid = MidiFile(input_file)
new_mid = MidiFile(ticks_per_beat=mid.ticks_per_beat)

for i, track in enumerate(mid.tracks):
    if i not in pistes_a_supprimer:
        new_mid.tracks.append(track)

new_mid.save(output_file)
print(f"✔ Pistes supprimées : {pistes_a_supprimer}")
