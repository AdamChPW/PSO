#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gen_map.h"

int main(int argc, char* argv[]) {
	printf("Program przyjmuje dane w formacie:\n");
	printf("<wymagane> [opcjonalne]\n");
	printf("./%s <plik_do_zapisu> [szerokosc_mapy] [wysokosc_mapy] [max_sygnal] [mocnosc_sygnalu]\n", argv[0]);

	if (argc < 2) {
		fprintf(stderr, "[%s]: Za malo argumentow!\n", argv[0]);
		return 1;
	}

	srand(time(NULL));

	int w = argc > 2 ? atoi(argv[2]) : 100;
	int h = argc > 3 ? atoi(argv[3]) : 100;
	double signal = argc > 4 ? atof(argv[4]) : 30.0;
	double streng = argc > 5 ? atof(argv[5]) : 60.0;

	GenerateMap(argv[1], w, h, signal, streng);

	return 0;
}