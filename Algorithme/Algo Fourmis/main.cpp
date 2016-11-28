#include "problem.h"
#include "ant_system.h"
#include <iostream>

int main(int argc, char **argv){
	// villes, borne sup, borne inf, coeff d'évaporation en %

	int nbVilles = 10, nbIterations = 5000, nbFourmis = 10;
	if (argc > 1){
		nbVilles = atoi(argv[1]);
		nbIterations = atoi(argv[2]);
		nbFourmis = atoi(argv[3]);
	}

	srand(0);
    problem p(nbVilles, 5000, 1, .05);

	std::cout << "donnees creees" << std::endl;

	// nombre de fourmis
    antSystem sys(nbFourmis, p);

	std::cout << "systeme cree" << std::endl;

	// unités de temps
    sys.run(nbIterations);

	std::cout << sys.pathCount << " chemins testes" << std::endl;
}