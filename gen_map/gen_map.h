#ifndef _GENMAP_H_
#define _GENMAP_H_

void GenerateMap(const char* f, int w, int h, double signal, double streng);
double RandDouble(double min, double max);
double GenerateSignalAtPoint(double signal, double streng);

#endif