/*
 * vibrato.h

 */

#ifndef INC_VIBRATO_H_
#define INC_VIBRATO_H_

#define MAX_BUF_SIZE    1024
#define MAX_DELAY_SIZE  255
#define PI              (float) 3.1415926
#define LFO             (float)10.0
#define DELAY           (float) 0.0008

typedef struct {
    float   mod_n;
    float   delay;
    float   mod;
    int     delayline[MAX_DELAY_SIZE];
    int     delay_size;
    long    n;
} vibrato;

void  vibratoInit(unsigned long fs, vibrato *t);
void modulation(vibrato *t, int dataIn);
int interpolation(vibrato *t);


#endif /* INC_VIBRATO_H_ */
