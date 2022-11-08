#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>

#define WAV_HEADER_SIZE 44
#define WAV_SAMPLE_SIZE 16
#define MAX_SAMPLE_GAIN 32768
#define GAIN 11
#define MIX 0.1

float sign(int16_t value)
{
    if (value > 0) {
        return 1.0;
    }

    if (value < 0) {
        return -1.0;
    }

    return 0.0;
}

void main(void)
{
    FILE *inputTrack = fopen("..\\Data\\acoustic.wav", "rb");
    FILE *outputTrack = fopen("..\\Data\\fuzz.wav", "wb");
    int16_t sample, y, q, z;
    short int header[WAV_HEADER_SIZE];

    if (inputTrack == NULL) {
        printf("[Error] Failed to open input file\n");
        return;
    }

    // Writing WAV header to output track
    printf("[Info] Writing WAV header to output audio track...\n");

    fread(header, WAV_HEADER_SIZE, 1, inputTrack);
    fwrite(header, WAV_HEADER_SIZE, 1, outputTrack);

    printf("[Info] Started copying audio track...\n");

    // Processing input file and write to output file
    while(!feof(inputTrack)) {
        fread(&sample, sizeof(int16_t), 1, inputTrack);

        q = (int16_t) sample * GAIN / MAX_SAMPLE_GAIN;
        z = (int16_t) sign(-q) * (1 - exp(sign(-q) * q));
        y = (int16_t) (MIX * z) + (1 - MIX) * sample;

        fwrite(&y, 1, sizeof(int16_t), outputTrack);
    }

    fclose(inputTrack);
    fclose(outputTrack);

    printf("[Info] Audio effect applied to the track successfully!\n");
}
