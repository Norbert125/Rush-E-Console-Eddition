#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// This script requires the 'sox' utility on Linux/Unix.
// Compile with: gcc rush_e_stable.c -o rush_e_stable

// --- Frequency Definitions (Hz) ---
#define C3 131
#define D3 147
#define E3 165
#define F3 175
#define G3 196
#define A3 220
#define B3 247

#define C4 262
#define D4 294
#define E4 330
#define F4 349
#define G4 392
#define A4 440
#define B4 494

#define C5 523
#define D5 587
#define E5 659
#define F5 698
#define G5 784
#define A5 880
#define B5 988

#define C6 1047
#define D6 1175
#define D_SHARP_6 1245
#define E6 1319
#define F6 1397
#define G6 1568
#define A6 1760

#define REST 0

// Plays a note using the SoX 'play' command.
void linux_play_note(int frequency_hz, int duration_ms) {
    if (frequency_hz == REST || duration_ms == 0) {
        // If it's a rest, just pause the execution thread.
        usleep(duration_ms * 1000);
        return;
    }

    double duration_s = (double)duration_ms / 1000.0;
    char command[128];

    // Using 'sawtooth' for aggressive synth timbre
    // '-n -6' applies a -6dB gain to prevent clipping on sawtooth
    snprintf(command, sizeof(command),
             "play -q -n synth %f sawtooth %d gain -n -6 fade 0 0 %f",
             duration_s, frequency_hz, duration_s / 2.0);

    // This command blocks until the sound finishes playing
    system(command);
}

void playRushEBeat(int iterations) {
    // This array contains the primary melody line from the polyphonic version.
    int frequencies[] = {
        // 1. Intro Tremolo (16 notes)
        D5, D5, D5, D5, D5, D5, D5, D5, D5, D5, D5, D5, D5, D5, D5, D5,
        // 2. Initial Fast Descent/Ascent (16 notes)
        E6, D6, C6, B5, A5, G5, F5, E5,
        D5, E5, F5, G5, A5, B5, C6, D6,
        // 3. Quick Flourish (4 notes)
        E6, D_SHARP_6, D6, C6,

        // 4. Main Arpeggios (16 notes)
        C6, G5, E5, C5,
        D6, A5, F5, D5,
        E6, B5, G5, E5,
        F6, C6, A5, F5,

        // 5. Extended Speed Runs (16 notes)
        A5, B5, C6, D6, E6, F6, G6, A6,
        A6, G6, F6, E6, D6, C6, B5, A5,

        // 6. Climax Build (Staccato hits - 16 notes)
        E6, C6, E6, C6,
        D6, B5, D6, B5,
        C6, A5, C6, A5,
        B5, G5, B5, G5,

        // 7. Final Chaos Run (16 notes)
        A6, F6, D6, B5,
        G6, E6, C6, A5,
        F5, D5, B4, G4,
        E4, C4, G4, REST,
    };

    // The single duration array (92 elements) with adjusted timing.
    int durations[] = {
        // 1. Intro Tremolo (16 notes @ 45ms) - SLOWED DOWN for clarity
        45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
        // 2. Descent/Ascent (16 notes @ 15ms) - FAST
        15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15,
        // 3. Quick Flourish (4 notes @ 20ms) - FAST
        20, 20, 20, 20,

        // 4. Main Arpeggios (16 notes @ 35ms) - SLOWED DOWN for clarity
        35, 35, 35, 35, 35, 35, 35, 35,
        35, 35, 35, 35, 35, 35, 35, 35,

        // 5. Extended Speed Runs (16 notes @ 10ms) - EXTREME SPEED
        10, 10, 10, 10, 10, 10, 10, 10,
        10, 10, 10, 10, 10, 10, 10, 10,

        // 6. Climax Build (16 notes @ 40ms) - SLOWED DOWN for stability
        40, 40, 40, 40, 40, 40, 40, 40,
        40, 40, 40, 40, 40, 40, 40, 40,

        // 7. Final Chaos Run (16 notes)
        20, 20, 20, 20,
        20, 20, 20, 20,
        20, 20, 20, 20,
        20, 20, 20, 500,
    };

    int pattern_length = sizeof(frequencies) / sizeof(frequencies[0]);

    if (pattern_length != (sizeof(durations) / sizeof(durations[0]))) {
        printf("Error: Frequency and duration arrays are not the same length!\n");
        return;
    }

    for (int i = 0; i < iterations; i++) {
        for (int j = 0; j < pattern_length; j++) {
            linux_play_note(frequencies[j], durations[j]);
        }
    }
}

int main() {
    int loop_count = 1;

    playRushEBeat(loop_count);

    return 0;
}
