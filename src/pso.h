#ifndef _PSO_H_
#define _PSO_H_
#include "map.h"

typedef struct Particle { 
	double* x; 
	double* v; 
	double* pbest; 
} Particle; 

typedef struct Swarm { 
	Particle** particles; 
	double* gbest; 
	int p; 
} Swarm;

Particle* CreateParticle(int h, int w);
Swarm* CreateSwarm(int p, int h, int w, Map* map);
void FreeSwarm(Swarm* swarm);
void PSOIteration(Swarm* swarm, double w, double c1, double c2, double r1, double r2, Map* map);
#endif
