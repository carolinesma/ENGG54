/*
 * vibrato.c
 *
 */
#include "stdio.h"
#include <math.h>
#include "vibrato.h"

void vibratoInit(float delay, int lfo, vibrato *t)
{
    t->max_delay = delay;
    t->var_delay = 0;
    t->delay_size = 2+round(delay*SF)*(1+2);
    t->mod     = lfo;
    t->n       = 1;

    unsigned char i = 0;
    for (i = 0; i <= MAX_DELAY_SIZE-1; i++) {
            t->delayline[i] = 0.0;
        }

    printf( "vibratoInit() at delay [%f] and LFO [%d]\n", t->max_delay, t->mod);
}

void modulation(vibrato *t, int dataIn)
{
    int i;

    t->var_delay = 1 + (t->max_delay * (1.0 + sin(t->mod*2*PI*t->n)));

    for (i = t->delay_size-2; i >= 0; i--)
            t->delayline[i] = t->delayline[i - 1];

    t->delayline[0] = dataIn;

}

int interpolation(vibrato *t) {
    int yOut, i;
    float frac, next;

    i = floor(t->var_delay);
    frac = t->var_delay - (float)i;

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


