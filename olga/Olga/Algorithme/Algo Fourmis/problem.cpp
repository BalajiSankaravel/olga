#include "problem.h"

problem::problem(int nbVilles, float borne1, float borne2, float coeff)
	:nbCities(nbVilles), borneMax(borne1), borneMin(borne2), evaporation(coeff){

	distances.assign(nbCities, 0);
	pheromones.assign(nbCities, 0);
	for (int i = 0; i<nbCities; i++){
        distances[i].assign(nbCities, 0);
		pheromones[i].assign(nbCities, borneMin);
	}

    for (int i = 0; i<nbCities; i++){
        distances[i][i] = 0;
		for (int j = i+1; j<nbCities; j++)
            distances[i][j] = distances[j][i] = rand()%100;
    }

    // solution optimale
    for (int i=0; i<nbCities; i++)
        distances[i][(i+1)%nbCities] = distances[(i+1)%nbCities][i] = 1;

	optimalLength = nbCities;
}

void problem::setPheromones(int i, int j, int wayLength){
    float ph = 100*optimalLength / float(wayLength + 1 - optimalLength);

    pheromones[i][j] += ph;

	if( pheromones[i][j] < borneMin) pheromones[i][j] = borneMin;
	if (pheromones[i][j] > borneMax) pheromones[i][j] = borneMax;

    pheromones[j][i] = pheromones[i][j];
}

void problem::evaporate(){
    for (int i=0; i<nbCities; i++)
        for (int j=0; j<i; j++){
            pheromones[i][j] = float(pheromones[i][j]*(100-evaporation) /100);
            if (int(pheromones[i][j]) < borneMin)
                pheromones[i][j] = float(borneMin);

            pheromones[j][i] = pheromones[i][j];                
        }
}

    // int nbCities;
    // int borneMax = 500, borneMin = 2;
    // evaporation = 1%

    // optimalLength