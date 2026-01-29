#include <stdio.h>
#include <stdlib.h>
#include "gen_map.h"

void GenerateMap(const char* f, int w, int h, double signal, double streng)
{
	if (w <= 0 || h <= 0 || signal < 0) {
		fprintf(stderr, "Tablica nie moze miec ujemnych ani zerowych wymiarowm, a sygnal nie moze byc ujemny!\n");
		return;
	}
	if(streng < 0 || streng > 100) {
		fprintf(stderr, "Moc sygnalu powinna byc w przedziale <0, 100>!\n");
		return;
	}
	FILE* out = fopen(f, "w");
	if (!out) {
		fprintf(stderr, "Blad otwarcia pliku do zapisu!\n");
		return;
	}
	fprintf(out, "%d %d\n", w, h);
	int  i, j;
	for(i = 0; i < h; i++) {
		for (j = 0; j < w; j++)
			fprintf(out, "%.2lf ", GenerateSignalAtPoint(signal, streng));
		fprintf(out, "\n");
	}
	fclose(out);
}

double RandDouble(double min, double max) {
    return (double)rand() / RAND_MAX * (max - min) + min;
}

double GenerateSignalAtPoint(double signal, double streng) {
	if (RandDouble(streng - 100.0, streng) > 0)
		return RandDouble(0.0, signal);
	else
		return -1000.0;
}