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
    for (int i = 0; i < nbDepot; i++) {
        Voyage* unDepot = new Voyage("", "", 0, "Depot" + to_string(i));
        DepotDepart.push_back(new Etat(unDepot));
        DepotArrive.push_back(new Etat(unDepot));
    }
    for (int i = 0; i < DepotDepart.size(); i++) {
        cout << "Depart " << DepotDepart[i]->voyage->getName() << endl;
        cout << "Arrive " << DepotArrive[i]->voyage->getName() << endl;
    }
}

void Graphe::CreationEtat(vector<Ligne>* lesLignes) {
    ///////////////////generation des etats
    for (int i = 0; i < lesLignes->size(); i++) {
        for (int j = 0; j < (*lesLignes)[i].lesVoyages.size(); j++) {
            lesEtats.push_back(new Etat(&(*lesLignes)[i].lesVoyages[j]));
        }
    }
    for (int z = 0; z < DepotDepart.size(); z++) {
        for (int i = 0; i < lesEtats.size(); i++) {
            DepotDepart[z]->LesChemins.push_back(lesEtats[i]->voyage);
            lesEtats[i]->LesChemins.push_back(DepotArrive[z]->voyage);
        }
    }
    
    s
    
    
    for (int i = 0; i < lesEtats.size(); i++) {
        cout << "n : " << lesEtats[i]->voyage->name<<endl;
        cout << "Depart : " << lesEtats[i]->voyage->TermDeb<<endl;
        cout << lesEtats[i]->voyage->HeureDeb.tm_hour;
        cout << "h" << lesEtats[i]->voyage->HeureDeb.tm_min<<endl;
        cout << "Arrive : " << lesEtats[i]->voyage->TermFin<<endl;
        cout << lesEtats[i]->voyage->HeureFin.tm_hour;
        cout << "h" << lesEtats[i]->voyage->HeureFin.tm_min<<endl;
        cout << "dist : " << lesEtats[i]->voyage->distance<<endl<<endl;
    }
    cout << "nb : " << lesEtats.size();
    
    
}


