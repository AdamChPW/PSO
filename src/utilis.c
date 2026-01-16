#include <stdlib.h>
#include "utilis.h"

double RandDouble(double min, double max){
    return (double)rand()/RAND_MAX * (max-min) + min; 
}