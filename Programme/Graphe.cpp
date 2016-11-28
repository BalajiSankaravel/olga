/* 
 * File:   Graphe.cpp
 * Author: Flav
 * 
 * Created on 27 novembre 2016, 16:54
 */

#include "Graphe.h"
#include <iostream>

using namespace std;

Graphe::Graphe(int nbDepot) {
    for (int i = 0; i < nbDepot; i++){
        Voyage* unDepot = new  Voyage("","",0,"Depot" + to_string(i));
        DepotDepart.push_back(unDepot);
        DepotArrive.push_back(unDepot);
    }
       for (int i = 0; i < DepotDepart.size(); i++){
           cout<<"Depart "<<DepotDepart[i].getName()<<endl;
           cout<<"Arrive "<<DepotArrive[i].getName()<<endl;
    }
}

void Graphe::CreationEtat(vector<Ligne>* lesLignes){
    for(int i = 0 ; i < lesLignes->size(); i++){
        for(int j = 0 ; j < (*lesLignes)[i].lesVoyages.size(); j++){
           lesEtats.push_back(Etat(&((*lesLignes)[i].lesVoyages[j]))); 
           for(int z = 0; z < DepotDepart.size(); z++){
               DepotDepart[z].LesChemins.push_back(&((*lesLignes)[i].lesVoyages[j]));
               lesEtats[j].LesChemins.push_back(DepotArrive[z].voyage);
           }
        }
    }
}


