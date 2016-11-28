#include "ant_system.h"
#include "problem.h"
#include "ant.h"
#include "ant_exception.h"
#include <algorithm>
#include <iostream>


antSystem::antSystem(int nbAnt, problem& d):data(d){
    for (int i=0; i<nbAnt; i++)
        ants.push_back(new ant(data));

	bestLength = 999999;
	pathCount = 0;
	curIteration = 0;
}

antSystem::~antSystem(){
    for (std::list<ant*>::iterator i = ants.begin(); i != ants.end(); i++)
        delete *i;
}

void antSystem::run(int n){        
    for (curIteration=0; curIteration<n; curIteration++){
        // process each ant
        std::list<ant*>::iterator it = ants.begin();
        while (it != ants.end()){
            try{
                 (*it)->frame();
            }catch(antException &e){
				if (e.state == antException::TO_REGISTER)
                    notifySolution(e.a->tmpVisitedLength, e.a->visitedCities);      

                if(bestLength <= data.optimalLength)
                     return;                

				*it = new ant(data);       
                delete e.a;                                           
            }
            it++;
        }         
       
        // evaporate the pheromones
		if (curIteration % 20 == 0)
			data.evaporate();  

		if (curIteration%50==0)
			std::cout << bestLength << std::endl;
    }
}

       
void antSystem::notifySolution(int value, std::vector<int>& cities){
    if (bestLength == -1){
        bestLength  = value;
        bestSolution = cities;
    }else{
		pathCount ++;

		if (value < bestLength){
			bestLength = value;
			bestSolution = cities;

			//std::cout << curIteration << " " << bestLength << " ";
			/*for (int i=0; i<int(cities.size()); i++)
				std::cout << cities[i] << ",";
*/
			//std::cout << std::endl;
		}
    }
}