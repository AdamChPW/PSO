#ifndef _PSO_H_
#define _PSO_H_

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

Particle* CreateParticle(int w, int h);
Swarm* CreateSwarm(int p, int w, int h, Map* map);
void FreeSwarm(Swarm* swarm);
void PSOIteration(Swarm* swarm, double w, double c1, double c2, double r1, double r2, Map* map);
#endif
