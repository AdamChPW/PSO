#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilis.h"


int ReadRow(char *s, int w, double *target)
{
    int i = 0, offset = 0, roznica = 0, wystopienia = 0;
    int str_len = strlen(s);
    
    for(i = 0; i < w && offset < str_len; i++)
        if(sscanf(s+offset,"%lf%n", &target[i], &roznica)){
            offset += roznica;
            wystopienia++;
        }

    return wystopienia;
}

double RandDouble(double min, double max){
    return (double)rand()/RAND_MAX * (max-min) + min; 
}