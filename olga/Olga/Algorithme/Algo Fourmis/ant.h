#ifndef H__ant__
#define H__ant__

#include <vector>

class problem;

/**
 * une fourmi
 */
class ant{
public:
    ant(problem&);

	// liste des villes vivitées / à visiter
    std::vector<int> visitedCities;
    std::vector<int> citiesStillToVisit;

    long tmpVisitedLength;
  
	// états possibles pour une fourmi
    enum {
        SEARCHING_PATH,
        RETURNING,
        NOTHING,
    };
    int state;

	// à chaque itération
    void frame();

protected:
	// données courantes
    long currentArcSize;
    long currentArcPos;
    int currentDestination;
    int currentOrigin;

	// référence sur les données du problème
    problem& data;

    void findNextSearchDestination();   

	int getNearCity(int);
};


#endif
