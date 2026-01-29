#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "pso.h"
#include "map.h"
#include "logger.h"

int main(int argc, char** argv)
{
    if(argc == 1){
        fprintf(stderr,"[%s] Error 1: Nie podano zadnych argumentow.\nProgram wymaga podania przynajmniej sciezki do pliku z mapa.\n",argv[0]);
        return 1;
    }

    srand(time(NULL));

    Map* map = LoadMap(argv[1]);

    if (map == NULL) {
        fprintf(stderr, "[%s] Error 2: Nieudalo sie wczytac mapy.\n", argv[0]);
        return 2;
    }

    int debug = 0;
    double w = 0.5, c1 = 1.0, c2 = 1.0, r1 = ((double)rand()) / RAND_MAX, r2 = ((double)rand()) / RAND_MAX;
    int p = 30, n = 0, i = 100, j;
    FILE* c = NULL;

    for (j = 2; j < argc; j++) {
        if (strcmp(argv[j], "-p") == 0) {
            j++;
            if (j < argc)
                if(sscanf(argv[j], "%d", &p) != 1) {}
        }
        if (strcmp(argv[j], "-i") == 0) {
            j++;
            if (j < argc)
                if(sscanf(argv[j], "%d", &i) != 1) {}
        }
        if (strcmp(argv[j], "-n") == 0) {
            j++;
            if (j < argc)
                if(sscanf(argv[j], "%d", &n) != 1) {}
        }
        if (strcmp(argv[j], "-c") == 0) {
            j++;
            if (j < argc)
                c = fopen(argv[j], "r");
            if (c != NULL) {
                if (fscanf(c, "%lf %lf %lf %lf %lf", &w, &c1, &c2, &r1, &r2) != 5) {}
			    fclose(c);
            }
        }
        if (strcmp(argv[j], "-d") == 0) {
            debug = 1;
        }
    }

	if(p <= 0){
		fprintf(stderr, "[%s] Error 3: Nie poprawna ilosc czasteczek.\n", argv[0]);
		return 3;
	}

    Swarm* swarm = CreateSwarm(p, map->w, map->h, map);

    FILE* out = n == 0 ? NULL : fopen("csv.txt", "w");

    for(j = 0; j < i; j++){
        PSOIteration(swarm, w, c1, c2, r1, r2, map);
		r1 = ((double)rand()) / RAND_MAX;
        r2 = ((double)rand()) / RAND_MAX;
        if(n > 0 && j % n == 0){
            if (out != NULL) {
                fprintf(out, "ITERACJA %d\n", j);
                for(int k = 0; k < p; k++){
                    LogPosition(out, k, (int)swarm->particles[k]->x[0], (int)swarm->particles[k]->x[1], GetValue(map, swarm->particles[k]->x[0], swarm->particles[k]->x[1]));
                }
            }
		}
    }
    if(out!=NULL)
        fclose(out);


    int xBest = (int)swarm->gbest[0];
    int yBest = (int)swarm->gbest[1];
    double vBest = GetValue(map, xBest, yBest);
	
	printf("Znaleziona pozycja to [%d]	[%d] : %.2lf\n", xBest+1, yBest+1, vBest);
	
    if(debug == 1){
        double* max = GetMax(map); 
        if(vBest == max[0]){
            printf("Znaleziono najwyzsza wartosc sygnalu!\n");
        }
        else{
            printf("Nie znaleziono najwyzszej wartosci sygnalu...\n");
            printf("\\\\\nMax w: [%d]  [%d] : %.2lf\n", (int)max[1]+1, (int)max[2]+1, max[0]);
            double dystans = sqrt( (max[1] - xBest)*(max[1] - xBest) + (max[2] - yBest)*(max[2] - yBest) );
            printf("Roznica sygnalu: %.2lf\nOdpleglosc od celu: %.2lf\n", max[0] - vBest, dystans);
        }
        free(max);
    }

    FreeSwarm(swarm);
    FreeMap(map);
    return 0;
}
