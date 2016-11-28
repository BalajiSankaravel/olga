#include "ant.h"

#include "problem.h"
#include "ant_exception.h"
#include <algorithm>

ant::ant(problem& d):data(d){
    tmpVisitedLength = 0;
    currentArcPos = -1;
    currentDestination = 0;
    currentOrigin = 0;
    state = NOTHING;

    for (int i=0; i<data.nbCities; i++)
        citiesStillToVisit.push_back(i);
}


void ant::frame(){
    switch(state){
        case SEARCHING_PATH:
            tmpVisitedLength ++;
        case RETURNING:
            currentArcPos++;               
            if (currentArcPos >= currentArcSize)
                findNextSearchDestination();
            break;                                       
        case NOTHING:
            findNextSearchDestination();
            break;                
    }
}

void ant::findNextSearchDestination(){
	switch(state){
		case NOTHING:{
			visitedCities.push_back(0);
			std::vector<int>::iterator tmp = citiesStillToVisit.begin();
			while (tmp != citiesStillToVisit.end()){
				if (*tmp == 0){
					citiesStillToVisit.erase(tmp);
					break;
				}
				tmp++;
			}			
			
			int dest = getNearCity(0);
			state = SEARCHING_PATH;
			currentOrigin = 0;
			currentDestination = dest;
			currentArcPos = 0;
			currentArcSize = data.distances[0][currentDestination];

			break;
		}
		case SEARCHING_PATH:{
			// on a atteint currentDestination
            
			visitedCities.push_back( currentDestination );  

			std::vector<int>::iterator tmp = citiesStillToVisit.begin();
			while (tmp != citiesStillToVisit.end()){
				if (*tmp == currentDestination){
					citiesStillToVisit.erase(tmp);
					break;
				}
				tmp++;	
			}

			//std::remove(citiesStillToVisit.begin(), citiesStillToVisit.end(), currentDestination );
            //citiesStillToVisit.resize(citiesStillToVisit.size() -1);

            if (citiesStillToVisit.size() == 0){
                // plus rien à visiter, le chemin est complet
                // on revient vers le nid
				tmpVisitedLength += data.distances[currentDestination][0];

                state = RETURNING;
                currentOrigin =  int(visitedCities.size())-1;
                currentDestination = int(visitedCities.size())-2;    
                currentArcSize = data.distances[ visitedCities[currentOrigin] ][ visitedCities[currentDestination] ];
                currentArcPos = currentArcSize;       
                return;                                
            }

			int dest = getNearCity(currentDestination);
			currentOrigin = currentDestination;
			currentDestination = dest;			
			currentArcSize = data.distances[currentOrigin][currentDestination];
			currentArcPos = 0;
			break;
		}
		case RETURNING:{
			if (currentDestination == 0){
				// retourné au nid avec succès
				data.setPheromones(visitedCities[currentOrigin], visitedCities[currentDestination], tmpVisitedLength);

				// sauver le résultat, changer de fourmi
				antException e;
				e.a = this;
				e.state = antException::TO_REGISTER;
				throw e;
            }
           
            // trouver la ville précédemment visitée et la passer en destination
            // mettre des phéromones sur l'arc parcouru
            data.setPheromones(visitedCities[currentOrigin], visitedCities[currentDestination], tmpVisitedLength );
            currentOrigin = currentDestination;
            currentDestination --;           
            currentArcSize = data.distances[  visitedCities[currentOrigin ] ][  visitedCities[currentDestination ] ];                                          
			currentArcPos = currentArcSize;
			
			break;
		}
	}	
}

int ant::getNearCity(int from){
    // roulette sur les chemins restants, pondérés par les phéromones
    float pheromoneSize = 0;           
	for (int i = 0; i < int(citiesStillToVisit.size()); i++){
		if (citiesStillToVisit[i] == from)
			continue;
		pheromoneSize  += data.pheromones[from][ citiesStillToVisit[i] ];
	}

    float found = float(rand()%int(pheromoneSize*10))/float(10)  ;
    float tmpPheromones = 0;
    int ii = 0;
    while (ii < int(citiesStillToVisit.size())){
		if (citiesStillToVisit[ii] == from){
			ii++;
			continue;
		}

        tmpPheromones  += data.pheromones[currentDestination][ citiesStillToVisit[ii] ];
   
        if (tmpPheromones   > found)
            break;

        ii ++;
    }
    if (ii == citiesStillToVisit.size()){
		// aucune solution acceptable, détruire la fourmi courante
		antException e;
		e.a = this;
		e.state = antException::TO_DELETE;
		throw e;
    }

	return citiesStillToVisit[ii];
}
