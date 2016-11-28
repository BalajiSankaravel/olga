#ifndef H__ant_system__
#define H__ant_system__

#include <list>
#include <vector>

class problem;
class ant;

/**
 * moteur d'algorithme
 */
class antSystem{
	public:
		antSystem(int, problem&);

		~antSystem();

		// on déroule l'exécution sur n itérations
		void run(int n);

		int pathCount;
	    
	private:
		// fourmis gérées
		std::list<ant*> ants;

		// données du problème
		problem &data;

		// meilleure solution trouvée
		int bestLength;
		std::vector<int> bestSolution;

		int curIteration;

		void notifySolution(int , std::vector<int>& );

};

#endif
