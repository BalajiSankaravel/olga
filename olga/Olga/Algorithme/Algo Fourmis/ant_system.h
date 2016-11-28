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

		// on d�roule l'ex�cution sur n it�rations
		void run(int n);

		int pathCount;
	    
	private:
		// fourmis g�r�es
		std::list<ant*> ants;

		// donn�es du probl�me
		problem &data;

		// meilleure solution trouv�e
		int bestLength;
		std::vector<int> bestSolution;

		int curIteration;

		void notifySolution(int , std::vector<int>& );

};

#endif
