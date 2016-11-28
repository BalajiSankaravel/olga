#ifndef H__problem__
#define H__problem__

#include <vector>

/**
 * donn�es du probl�me : distances + ph�romones 
 */
class problem{
public:
	problem(int, float, float, float);

    void setPheromones(int, int, int);

    void evaporate();

    int nbCities;
    float borneMax, borneMin;
    float evaporation;

    int optimalLength;

	// arcs
    // pheromones
	std::vector<std::vector<int> > distances;
	std::vector<std::vector<float> > pheromones;
};

#endif
