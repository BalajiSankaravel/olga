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

	// liste des villes vivit�es / � visiter
    std::vector<int> visitedCities;
    std::vector<int> citiesStillToVisit;

    long tmpVisitedLength;
  
	// �tats possibles pour une fourmi
    enum {
        SEARCHING_PATH,
        RETURNING,
        NOTHING,
    };
    int state;

	// � chaque it�ration
    void frame();

protected:
	// donn�es courantes
    long currentArcSize;
    long currentArcPos;
    int currentDestination;
    int currentOrigin;

	// r�f�rence sur les donn�es du probl�me
    problem& data;

    void findNextSearchDestination();   

	int getNearCity(int);
};


#endif
