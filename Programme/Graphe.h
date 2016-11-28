/* 
 * File:   Graphe.h
 * Author: Flav
 *
 * Created on 27 novembre 2016, 16:54
 */

#include <vector>
#include "Etat.h"
#include "Ligne.h"
using namespace std;
#ifndef GRAPHE_H
#define	GRAPHE_H

class Graphe {
public:
    Graphe(int);
    void CreationEtat(vector <Ligne>*);
    void GenerationEtatSameLine();
    void GenerationetatMultiLine();
    vector<Etat*> lesEtats;
    vector<Etat*> DepotDepart;
    vector<Etat*> DepotArrive;
    
};

#endif	/* GRAPHE_H */

