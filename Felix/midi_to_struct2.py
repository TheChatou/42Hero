import mido

def simplify_led_mask(notes, num_ticks):
    """
    Simplifie les combinaisons de LED à partir d'événements MIDI.
    Règle :
        - Priorité aux LED simples : 1, 2, 4, 8
        - Ensuite autorise : 3, 5, 6, 9, 10, 12
        - Jamais 15 (toutes les LED en même temps)
        - Ajoute des 0 pour aérer s’il y a trop de polyphonie
    """
    tracks = [[0 for _ in range(num_ticks)] for _ in range(4)]
    leds = [0 for _ in range(num_ticks)]

    allowed_masks = [1, 2, 4, 8, 3, 5, 6, 9, 10, 12]

    for track_id, notes_track in enumerate(notes):
        for start_ms, end_ms, freq in notes_track:
            start_tick = start_ms // tick_ms
            end_tick = end_ms // tick_ms
            for tick in range(start_tick, min(end_tick, num_ticks)):
                tracks[track_id][tick] = freq
                leds[tick] |= (1 << track_id)

    # Nettoyage des LED selon les règles
    for tick in range(num_ticks):
        if leds[tick] == 15:
            leds[tick] = 0
            for i in range(4):
                tracks[i][tick] = 0
        elif leds[tick] not in allowed_masks:
            leds[tick] = 0
            for i in range(4):
                tracks[i][tick] = 0

    return tracks, leds

