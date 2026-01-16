#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilis.h"


int ReadRow(char *s, int w, double *target)
{
    int i, offset, wystopienia = 0;
    int str_len = strlen(s);
    for(i=0; i<w && offset < str_len; i++){
        sscanf(s+offset,"%lf%n", &target[i], &offset);
        wystopienia++;
    }
    return wystopienia;
}

double RandDouble(double min, double max){
    return (double)rand()/RAND_MAX * (max-min) + min; 
}