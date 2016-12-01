#include <iostream>
#include "Graphe.h"
#include "Bus.h"
using namespace std;
#ifndef GENETIQUE_H
#define GENETIQUE_H


class Genetique {
public:
    Genetique(vector<Bus*>*, Graphe*,vector <vector<int> >* pTemps, vector <vector<int> >* pDist);
    vector < vector < Etat*>>* voyageToEtat();
    bool CheckIfEtatsPresents (vector < vector < Etat*>>*);
    bool CheckIfEtatsPresentsOnlyOnce(vector < vector < Etat*>>*);
    bool CheckTrajetAdmissible(vector < vector < Etat*>>*);
    vector<long*>* calculScore();

    bool Fitness();


    Graphe* leGraphe;
    vector <Bus*>* lesBus;
    vector <vector<int> >* matriceTemps;
    vector <vector<int> >* matriceDist;
    
private:

};

#endif /* GENETIQUE_H */

