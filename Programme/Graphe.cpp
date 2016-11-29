/* 
 * File:   Graphe.cpp
 * Author: Flav
 * 
 * Created on 27 novembre 2016, 16:54
 */

#include "Graphe.h"
#include <iostream>
#include <sstream>

using namespace std;

Graphe::Graphe(int nbDepot, vector <vector<int> >* pTemps, vector <vector<int> >* pDist) {
    matriceTemps = pTemps;
    matriceDist = pDist;
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



    //    for (int i = 0; i < lesEtats.size(); i++) {
    //        cout << "n : " << lesEtats[i]->voyage->name << endl;
    //        cout << "Depart : " << lesEtats[i]->voyage->TermDeb << endl;
    //        cout << lesEtats[i]->voyage->HeureDeb.tm_hour;
    //        cout << "h" << lesEtats[i]->voyage->HeureDeb.tm_min << endl;
    //        cout << "Arrive : " << lesEtats[i]->voyage->TermFin << endl;
    //        cout << lesEtats[i]->voyage->HeureFin.tm_hour;
    //        cout << "h" << lesEtats[i]->voyage->HeureFin.tm_min << endl;
    //        cout << "dist : " << lesEtats[i]->voyage->distance << endl << endl;
    //    }
    //    cout << "nb : " << lesEtats.size();


}

void Graphe::GenerationArcMemeLigne() {

    for (auto i : lesEtats) {
        for (auto j : lesEtats) {
            if (i != j) {
                if ((this->split(i->voyage->name, ':')[0]) == (split(j->voyage->name, ':')[0])) {
                    if ((j->voyage->HeureDeb.tm_hour * 60 + j->voyage->HeureDeb.tm_min - 5) -
                            (i->voyage->HeureFin.tm_hour * 60 + i->voyage->HeureFin.tm_min) >= 0 && i->voyage->TermFin == j->voyage->TermDeb) {
                        i->LesChemins.push_back(j->voyage);
                    } else {

                        int l = (*matriceTemps)[stoi(RemFirstChar(i->voyage->TermFin))]
                                [stoi(RemFirstChar(j->voyage->TermDeb))];
                        if (l < 5) l = 5;
                        if ((j->voyage->HeureDeb.tm_hour * 60 + j->voyage->HeureDeb.tm_min - l) -
                                ((i->voyage->HeureFin.tm_hour * 60 + i->voyage->HeureFin.tm_min)
                                ) >= 0) {
                            i->LesChemins.push_back(j->voyage);
                        }
                    }
                }
            }
        }
    }
    int arc = 0;
    for (auto i : lesEtats) {
        cout << "Etat : " << i->getName() << endl;
        for (auto j : i->LesChemins) {
            arc++;
            cout << "Arc : " << j->name << endl;
        }
    }
    cout << "Nb arc : " << arc << endl;
}

void Graphe::GenerationArcLigneDiff() {

    for (auto i : lesEtats) {
        for (auto j : lesEtats) {
            if (i != j) {
                if ((j->voyage->HeureDeb.tm_hour * 60 + j->voyage->HeureDeb.tm_min - 5) -
                        (i->voyage->HeureFin.tm_hour * 60 + i->voyage->HeureFin.tm_min) >= 0 && i->voyage->TermFin == j->voyage->TermDeb) {
                    i->LesChemins.push_back(j->voyage);
                } else {
                    int l = (*matriceTemps)[stoi(RemFirstChar(i->voyage->TermFin))]
                            [stoi(RemFirstChar(j->voyage->TermDeb))];
                    
                    if (l < 5) l = 5;
                   
                    if ((j->voyage->HeureDeb.tm_hour * 60 + j->voyage->HeureDeb.tm_min - l) -
                            ((i->voyage->HeureFin.tm_hour * 60 + i->voyage->HeureFin.tm_min)
                            ) >= 0) {
                        i->LesChemins.push_back(j->voyage);
                    }
                }
            }
        }
    }
    
        int arc = 0;
        for (auto i : lesEtats) {
            cout << "Etat : " << i->getName() << endl;
            for (auto j : i->LesChemins) {
                arc++;
                cout << "Arc : " << j->name << endl;
            }
        }
        cout<<"Nb arc : "<<arc<<endl;
}

void Graphe::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

vector<string> Graphe::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

string Graphe::RemFirstChar(string chaine) {
    string result;
    for (int i = 1; i < chaine.size(); i++) {
        result += chaine[i];
    }
    return result;
}


