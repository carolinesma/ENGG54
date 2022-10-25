/*
 * vibrato.c
 *
 */
#include "stdio.h"
#include <math.h>
#include "vibrato.h"

void vibratoInit(unsigned long fs, vibrato *t)
{
    t->mod_n = LFO/fs;
    t->delay = round(DELAY*fs);
    t->mod = 0;
    t->delay_size = 2+(t->delay*3);
    t->n       = 1;

    unsigned char i = 0;
    for (i = 0; i <= MAX_DELAY_SIZE-1; i++) {
            t->delayline[i] = 0;
        }

    printf( "vibratoInit() at delay [%f] and LFO [%f]\n", DELAY, LFO);
}

#define W (float)(t->mod_n*2*PI)
void up_delayline(vibrato *t, int dataIn)
{
    int i;

    t->mod = (1.0 + t->delay) + (t->delay*sin(W*t->n));

    for (i = t->delay_size-2; i >= 0; i--)
            t->delayline[i] = t->delayline[i - 1];

    t->delayline[0] = dataIn;

}

int linear_interpolation(vibrato *t) {
    int yOut, i;
    float frac, next;

    i = floor(t->mod);
    frac = t->mod - (float)i;

    if (i != t->delay_size-1) {
        next = t->delayline[i+1];
    }
    else {
        next = t->delayline[0];
    }

    yOut = round((next * frac) + t->delayline[i]*(1.0-frac));
    t->n++;

    return yOut;
}


