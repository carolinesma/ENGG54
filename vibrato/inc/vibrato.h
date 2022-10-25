/*
 * vibrato.h

 */

#ifndef INC_VIBRATO_H_
#define INC_VIBRATO_H_

#define MAX_BUF_SIZE 1024
#define MAX_DELAY_SIZE 255
#define PI (double) 3.1415926
#define SF 12000

typedef struct {
    int   mod;
    float max_delay;
    float var_delay;
    float delayline[MAX_DELAY_SIZE];
    int  delay_size;
    long n;
} vibrato;

void  vibratoInit(float delay, int lfo, vibrato *t);
void modulation(vibrato *t, int dataIn);
int interpolation(vibrato *t);


#endif /* INC_VIBRATO_H_ */
