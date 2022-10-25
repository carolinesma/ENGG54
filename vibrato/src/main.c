/*
 */

#include <stdio.h>
#include <stdlib.h>
#include "vibrato.h"

vibrato *t;
vibrato param;

char temp[2*MAX_BUF_SIZE];
unsigned char waveHeader[44];

void wHeader(unsigned char *w, float f1, float f2, unsigned long bytes);

void main()
{
    FILE *fpIn,*fpOut;
    unsigned long cnt;
    float delay;
    int lfo, sample, i, j, yOut;


    printf("Efeito Vibrato\n");

    printf("Entre com o delay em ms (aceita valores entre 5 e 10 ms)\n");
    scanf ("%lf", &delay);
    printf("Entre com a frequência de oscilação para o LFO modulador em Hz (aceita valores entre 5 e 14)\n");
    scanf ("%d", &lfo);

    fpIn = fopen("..\\data\\acoustic.wav", "rb");
    fpOut = fopen("..\\data\\acoustic_vibrato.wav", "wb");


    if (fpIn == NULL)                            // Check if the input file exists
    {
        printf("Failed to open input audio file\n");
        exit(0);
    }

    fread(waveHeader, sizeof(unsigned char), 44, fpIn);
    fwrite(waveHeader, sizeof(unsigned char), 44, fpOut);

    cnt = 0;
    t = &param;
    vibratoInit(delay, lfo, t);

    while ((fread(&temp, sizeof(char),2*MAX_BUF_SIZE, fpIn)) == 2*MAX_BUF_SIZE ) {
        for (j=0, i=0; i<MAX_BUF_SIZE; i++)
        {
            sample = (temp[j]&0xFF)|(temp[j+1]<<8);
            modulation(t, sample);
            yOut = interpolation(t);

            temp[j++] = yOut&0xFF;
            temp[j++] = (yOut>>8)&0xFF;
        }

        fwrite(&temp, sizeof(short),2*MAX_BUF_SIZE, fpOut);
        cnt += MAX_BUF_SIZE;
        printf("%ld data samples processed\n", cnt);
    }

    wHeader(waveHeader, 8000, 8000, cnt<<1);
    rewind(fpOut);
    fwrite(waveHeader, sizeof(char), 44, fpOut);

    fclose(fpIn);
    fclose(fpOut);

    printf("\nProcesso Finalizado\n");
}

// Create the wave file header
void wHeader(unsigned char *w, float f1, float f2, unsigned long bytes)
{
    long t;

    t = bytes;
    w[40] = (t>>0)&0xff;    // Set up output file size
    w[41] = (t>>8)&0xff;
    w[42] = (t>>16)&0xff;
    w[43] = (t>>24)&0xff;
    t += 36;
    w[4] = (t>>0)&0xff;
    w[5] = (t>>8)&0xff;
    w[6] = (t>>16)&0xff;
    w[7] = (t>>24)&0xff;
    t = w[24]|(w[25]<<8)|((long)w[26]<<16)|((long)w[27]<<24);
    t = (long)((float)t*f2/f1);
    w[24] = (t>>0)&0xff;    // Set up output file frequency
    w[25] = (t>>8)&0xff;
    w[26] = (t>>16)&0xff;
    w[27] = (t>>24)&0xff;
    t = w[28]|(w[29]<<8)|((long)w[30]<<16)|((long)w[31]<<24);
    t = (long)((float)t*f2/f1);
    w[28] = (t>>0)&0xff;    // Set up output file byte rate
    w[29] = (t>>8)&0xff;
    w[30] = (t>>16)&0xff;
    w[31] = (t>>24)&0xff;
    return;
}
