#include "pso.h"
#include <stdio.h>
#include <stdlib.h>
#include "utilis.h"

Swarm* CreateSwarm(int p, int w, int h) {

    Swarm* swarm = (Swarm*)malloc(sizeof(Swarm));

    if (swarm != NULL) {
        swarm->particles = (Particle**)malloc(p * sizeof(Particle*));
        swarm->gbest = (double*)malloc(2 * sizeof(double));
        swarm->p = p;

        if (swarm->particles != NULL) {
            for (int i = 0; i < p; i++) {
                swarm->particles[i] = CreateParticle(w, h);
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


