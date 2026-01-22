#include "pso.h"
#include <stdio.h>
#include <stdlib.h>
#include "utilis.h"
#include "map.h"

Swarm* CreateSwarm(int p, int w, int h, Map* map) {

    Swarm* swarm = (Swarm*)malloc(sizeof(Swarm));

    if (swarm != NULL) {
        swarm->particles = (Particle**)malloc(p * sizeof(Particle*));
        swarm->gbest = (double*)malloc(2 * sizeof(double));

        if (!swarm->particles || !swarm->gbest) {
            fprintf(stderr, "[src/pso.c] Blad alokacji pamieci dla roju.\n");
			free(swarm->particles);
			free(swarm->gbest);
            free(swarm);
            return NULL;
        }

        swarm->p = p;

        for (int i = 0; i < p; i++) {
            swarm->particles[i] = CreateParticle(w, h);
            if (!swarm->particles[i]) {
				FreeSwarm(swarm);
				return NULL;
            }
        }

		double bestValue1 = GetValue(map, swarm->particles[0]->pbest[0], swarm->particles[0]->pbest[1]);
		swarm->gbest[0] = swarm->particles[0]->pbest[0];
		swarm->gbest[1] = swarm->particles[0]->pbest[1];
        for (int i = 1; i < p; i++) {
            double bestValue2 = GetValue(map, swarm->particles[i]->pbest[0], swarm->particles[i]->pbest[1]);
            if (bestValue2 > bestValue1) {
                bestValue1 = bestValue2;
                swarm->gbest[0] = swarm->particles[i]->pbest[0];
                swarm->gbest[1] = swarm->particles[i]->pbest[1];
			}
        }
    }
    return swarm;
}

Particle* CreateParticle(int w, int h) {

	Particle* particle = (Particle*)malloc(sizeof(Particle));

    if (particle != NULL) {
        particle->x = (double*)malloc(2 * sizeof(double));
        particle->v = (double*)malloc(2 * sizeof(double));
        particle->pbest = (double*)malloc(2 * sizeof(double));
    }
    if (!particle || !particle->x || !particle->v || !particle->pbest) {
		fprintf(stderr, "[src/pso.c] Blad alokacji pamieci dla czastki.\n");
        free(particle->x);
		free(particle->v);
		free(particle->pbest);
		free(particle);
        return NULL;
    }
    particle->x[0] = (double)(rand() % w);
    particle->x[1] = (double)(rand() % h);
	particle->v[0] = RandDouble(-1.0, 1.0);
	particle->v[1] = RandDouble(-1.0, 1.0); 
	particle->pbest[0] = particle->x[0];
	particle->pbest[1] = particle->x[1];
    return particle;
}

void FreeSwarm(Swarm* swarm) {
    if (!swarm) return;

    for (int i = 0; i < swarm->p; i++) {
        free(swarm->particles[i]->x);
        free(swarm->particles[i]->v);
        free(swarm->particles[i]->pbest);
        free(swarm->particles[i]);
    }
    free(swarm->particles);
    free(swarm->gbest);
    free(swarm);
}

void PSOIteration(Swarm* swarm, double w, double c1, double c2, double r1, double r2, Map* map)
{
    for (int i = 0; i < swarm->p; i++) {
        Particle* particle = swarm->particles[i];
        particle->v[0] = w * particle->v[0] 
                        + c1 * r1 * (particle->pbest[0] - particle->x[0]) 
                        + c2 * r2 * (swarm->gbest[0] - particle->x[0]);
        particle->v[1] = w * particle->v[1] 
                        + c1 * r1 * (particle->pbest[1] - particle->x[1]) 
                        + c2 * r2 * (swarm->gbest[1] - particle->x[1]);

        particle->x[0] += particle->v[0];
        particle->x[1] += particle->v[1];

        if ((int)particle->x[0] > map->w - 1) particle->x[0] = map->w - 1;
		if ((int)particle->x[0] < 0) particle->x[0] = 0;
        if ((int)particle->x[1] > map->h - 1) particle->x[1] = map->h - 1;
		if ((int)particle->x[1] < 0) particle->x[1] = 0;

        double currentValue = GetValue(map, particle->x[0], particle->x[1]);
        double pbestValue = GetValue(map, particle->pbest[0], particle->pbest[1]);
        if (currentValue > pbestValue) {
            particle->pbest[0] = particle->x[0];
            particle->pbest[1] = particle->x[1];
            pbestValue = currentValue;
        }

        double gbestValue = GetValue(map, swarm->gbest[0], swarm->gbest[1]);
        if (pbestValue > gbestValue) {
            swarm->gbest[0] = particle->x[0];
            swarm->gbest[1] = particle->x[1];
        }
	}
}


