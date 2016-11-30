/* 
 * File:   Graphe.cpp
 * Author: Flav
 * 
 * Created on 27 novembre 2016, 16:54
 */

#include "Graphe.h"
#include <iostream>
#include <sstream>
#include <limits.h>
#include "PARAMETRE.h"
using namespace std;

Graphe::Graphe(int nbDepot, vector <vector<int> >* pTemps, vector <vector<int> >* pDist) {
    matriceTemps = pTemps;
    matriceDist = pDist;
    for (int i = 0; i < nbDepot; i++) {
        Voyage* unDepot = new Voyage("", "", 0, "Depot" + to_string(i));
        unDepot->TermDeb = "T0";
        unDepot->TermFin = "T0";
        unDepot->HeureDeb.tm_hour = 0;
        unDepot->HeureDeb.tm_min = 0;
        unDepot->HeureFin.tm_hour = 0;
        unDepot->HeureFin.tm_min = 0;
        unDepot->distance = 0;
        DepotDepart.push_back(new Etat(unDepot));
        DepotArrive.push_back(new Etat(unDepot));
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
            DepotDepart[z]->LesChemins.push_back(lesEtats[i]);
            lesEtats[i]->LesChemins.push_back(DepotArrive[z]);
        }
    }

}

void Graphe::GenerationArcMemeLigne() {

    for (auto i : lesEtats) {
        for (auto j : lesEtats) {
            if (i != j) {
                if ((this->split(i->voyage->name, ':')[0]) == (split(j->voyage->name, ':')[0])) {
                    if ((j->voyage->HeureDeb.tm_hour * 60 + j->voyage->HeureDeb.tm_min - 5) -
                            (i->voyage->HeureFin.tm_hour * 60 + i->voyage->HeureFin.tm_min) >= 0 && i->voyage->TermFin == j->voyage->TermDeb) {
                        i->LesChemins.push_back(j);
                    } else {

                        int l = (*matriceTemps)[stoi(RemFirstChar(i->voyage->TermFin))]
                                [stoi(RemFirstChar(j->voyage->TermDeb))];
                        if (l < 5) l = 5;
                        if ((j->voyage->HeureDeb.tm_hour * 60 + j->voyage->HeureDeb.tm_min - l) -
                                ((i->voyage->HeureFin.tm_hour * 60 + i->voyage->HeureFin.tm_min)
                                ) >= 0) {
                            i->LesChemins.push_back(j);
                        }
                    }
                }
            }
        }
    }
}

void Graphe::GenerationArcLigneDiff() {

    for (auto i : lesEtats) {
        for (auto j : lesEtats) {
            if (i != j) {
                if ((j->voyage->HeureDeb.tm_hour * 60 + j->voyage->HeureDeb.tm_min - 5) -
                        (i->voyage->HeureFin.tm_hour * 60 + i->voyage->HeureFin.tm_min) >= 0 && i->voyage->TermFin == j->voyage->TermDeb) {
                    i->LesChemins.push_back(j);
                } else {
                    int l = (*matriceTemps)[stoi(RemFirstChar(i->voyage->TermFin))]
                            [stoi(RemFirstChar(j->voyage->TermDeb))];

                    if (l < 5) l = 5;

                    if ((j->voyage->HeureDeb.tm_hour * 60 + j->voyage->HeureDeb.tm_min - l) -
                            ((i->voyage->HeureFin.tm_hour * 60 + i->voyage->HeureFin.tm_min)
                            ) >= 0) {
                        i->LesChemins.push_back(j);
                    }
                }
            }
        }
    }
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

vector < vector < Etat*> > Graphe::Resolution(int* temps, int* distance) {
    int nbBus = 0;
    vector <Etat*> tabou;
    vector < vector < Etat* > > ListeBus;

    while (tabou.size() < lesEtats.size()) {
        vector < Etat* > trajetBus;
        Etat* Bus = DepotDepart[rand() % DepotDepart.size()];
        trajetBus.push_back(Bus);
        nbBus++;
        bool listeArrive = false;
        while (!listeArrive) {
            int indexC = GestionCheminSuivantGRASPDepotLast(Bus, tabou);
            if (indexC < 0) exit(0);

            /////////////Distance

            *distance += Bus->voyage->distance;
            *distance += (*matriceDist)[stoi(RemFirstChar(Bus->voyage->TermFin))][stoi(RemFirstChar(Bus->LesChemins[indexC]->voyage->TermDeb))];

            trajetBus.push_back(Bus->LesChemins[indexC]);
            Bus = Bus->LesChemins[indexC];

            bool nonTabou = false;
            for (auto i : DepotArrive) {
                if (Bus == i) listeArrive = true;
                if (Bus == i) nonTabou = true;
            }
            if (!nonTabou) tabou.push_back(Bus);
        }
        ListeBus.push_back(trajetBus);
    }
    for (int i = 0; i < ListeBus.size(); i++) {
        int tps = 0;
//        for (int j = 0; j < ListeBus[i].size(); j++) {
//            cout << ListeBus[i][j]->voyage->name << " ";
//        }
        tps = (*matriceTemps)[stoi(RemFirstChar(ListeBus[i][0]->voyage->TermFin))][stoi(RemFirstChar(ListeBus[i][1]->voyage->TermDeb))];
        *temps += tps;
        //cout << endl << "matrice[" << stoi(RemFirstChar(ListeBus[i][0]->voyage->TermFin)) << "][" << stoi(RemFirstChar(ListeBus[i][1]->voyage->TermDeb)) << "] = " << tps << endl;
        tps = ((ListeBus[i][ListeBus[i].size() - 2]->voyage->HeureFin.tm_hour * 60 + ListeBus[i][ListeBus[i].size() - 2]->voyage->HeureFin.tm_min)-((ListeBus[i][1]->voyage->HeureDeb.tm_hour * 60 + ListeBus[i][1]->voyage->HeureDeb.tm_min)));
        *temps += tps;
        //cout << "((" << (ListeBus[i][ListeBus[i].size() - 2]->voyage->HeureFin.tm_hour * 60) << " + " << (ListeBus[i][ListeBus[i].size() - 2]->voyage->HeureFin.tm_min) << ") - (" << (ListeBus[i][1]->voyage->HeureDeb.tm_hour * 60) << " + " << (ListeBus[i][1]->voyage->HeureDeb.tm_min) << " = " << tps << endl;
        tps = (*matriceTemps)[stoi(RemFirstChar(ListeBus[i][ListeBus[i].size() - 2]->voyage->TermFin))][stoi(RemFirstChar(ListeBus[i][ListeBus[i].size() - 1]->voyage->TermDeb))];
        *temps += tps;
        //cout << "matrice[" << stoi(RemFirstChar(ListeBus[i][0]->voyage->TermFin)) << "][" << stoi(RemFirstChar(ListeBus[i][1]->voyage->TermDeb)) << "] = " << tps << endl << endl;

    }
    //cout << "nb Bus: " << ListeBus.size() << endl;
    //cout << "total : " << *temps << endl;
    return ListeBus;
}

int Graphe::getTempsDiff(Etat* a, Etat* b) {
    int i = (a->voyage->HeureFin.tm_hour * 60 + a->voyage->HeureFin.tm_min)-(b->voyage->HeureDeb.tm_hour * 60 + b->voyage->HeureDeb.tm_min);
    if (i < 0) {
        cout << " ! ! ! Erreur temps entre " << a->voyage->name << " et " << b->voyage->name << endl;
        exit(0);
    }
    return i;
}

int Graphe::GestionCheminSuivantGloutonDepotLast(Etat* EtatActuel, vector <Etat*> listeTabou) {
    //Verification des transitions
    vector <Etat*> listeTransitionDepot;
    vector <Etat*> listeTransitionEtat;
    for (int i = 0; i < EtatActuel->LesChemins.size(); i++) {
        bool trouve = false;
        for (int j = 0; j < listeTabou.size(); j++) {
            if (EtatActuel->LesChemins[i] == listeTabou[j]) {
                trouve = true;
            }
        }
        if (trouve == false) {
            bool arrive = false;
            for (int j = 0; j < DepotArrive.size(); j++) {
                if (EtatActuel->LesChemins[i] == DepotArrive[j]) {
                    arrive = true;
                }
            }
            if (arrive == true) {
                listeTransitionDepot.push_back(EtatActuel->LesChemins[i]);
            } else {
                listeTransitionEtat.push_back(EtatActuel->LesChemins[i]);
            }
        }
    }

    Etat* choix;

    if (listeTransitionEtat.size() > 0) {
        int min = INT_MAX;
        for (int k = 0; k < listeTransitionEtat.size(); k++) {
            int temps;
            if (EtatActuel->voyage->name == "Depot0") {//TODO
                temps = listeTransitionEtat[k]->voyage->HeureDeb.tm_hour * 60 + listeTransitionEtat[k]->voyage->HeureDeb.tm_min;
            } else {
                temps = getTempsDiff(listeTransitionEtat[k], EtatActuel);
            }

            if (temps < min) {
                min = temps;
                choix = listeTransitionEtat[k];
            }
        }
    } else {
        int min = INT_MAX;
        for (int k = 0; k < listeTransitionDepot.size(); k++) {
            if ((*matriceTemps)[stoi(RemFirstChar(EtatActuel->voyage->TermFin))][stoi(RemFirstChar(listeTransitionDepot[k]->voyage->TermDeb))] < min) {
                min = (*matriceTemps)[stoi(RemFirstChar(EtatActuel->voyage->TermFin))][stoi(RemFirstChar(listeTransitionDepot[k]->voyage->TermDeb))];
                choix = listeTransitionDepot[k];
            }
        }
    }
    for (int i = 0; EtatActuel->LesChemins.size(); i++) {
        if (EtatActuel->LesChemins[i] == choix) {

            return i;
        }
    }
    return -1;
}

int Graphe::GestionCheminSuivantGRASPDepotLast(Etat* EtatActuel, vector <Etat*> listeTabou) {
    //Verification des transitions
    vector <Etat*> listeTransitionDepot;
    vector <Etat*> listeTransitionEtat;
    for (int i = 0; i < EtatActuel->LesChemins.size(); i++) {
        bool trouve = false;
        for (int j = 0; j < listeTabou.size(); j++) {
            if (EtatActuel->LesChemins[i] == listeTabou[j]) {
                trouve = true;
            }
        }
        if (trouve == false) {
            bool arrive = false;
            for (int j = 0; j < DepotArrive.size(); j++) {
                if (EtatActuel->LesChemins[i] == DepotArrive[j]) {
                    arrive = true;
                }
            }
            if (arrive == true) {
                listeTransitionDepot.push_back(EtatActuel->LesChemins[i]);
            } else {
                listeTransitionEtat.push_back(EtatActuel->LesChemins[i]);
            }
        }
    }

    Etat* choix;

    int histeresys = GRASP_HYSTERESIS;
    if (listeTransitionEtat.size() > 0) {
        int min = INT_MAX - histeresys;
        for (int k = 0; k < listeTransitionEtat.size(); k++) {
            int temps;
            min = (min + ((rand() % (histeresys * 2)) - histeresys));
            if (min < 0) min = 0;
            if (EtatActuel->voyage->name == "Depot0") {//TODO
                temps = listeTransitionEtat[k]->voyage->HeureDeb.tm_hour * 60 + listeTransitionEtat[k]->voyage->HeureDeb.tm_min;
            } else {
                temps = getTempsDiff(listeTransitionEtat[k], EtatActuel);
            }
            if (temps < min) {
                min = temps;
                choix = listeTransitionEtat[k];
            }
        }
    } else {
        int min = INT_MAX - histeresys;
        for (int k = 0; k < listeTransitionDepot.size(); k++) {
            if ((*matriceTemps)[stoi(RemFirstChar(EtatActuel->voyage->TermFin))][stoi(RemFirstChar(listeTransitionDepot[k]->voyage->TermDeb))] < (min + ((rand() % (histeresys * 2)) - histeresys))) {
                min = (*matriceTemps)[stoi(RemFirstChar(EtatActuel->voyage->TermFin))][stoi(RemFirstChar(listeTransitionDepot[k]->voyage->TermDeb))];
                choix = listeTransitionDepot[k];
            }
        }
    }
    for (int i = 0; EtatActuel->LesChemins.size(); i++) {
        if (EtatActuel->LesChemins[i] == choix) {

            return i;
        }
    }
    return -1;
}

int Graphe::GestionCheminSuivantRandowDepotLast(Etat* EtatActuel, vector <Etat*> listeTabou) {
    //Verification des transitions
    vector <Etat*> listeTransitionDepot;
    vector <Etat*> listeTransitionEtat;
    for (int i = 0; i < EtatActuel->LesChemins.size(); i++) {
        bool trouve = false;
        for (int j = 0; j < listeTabou.size(); j++) {
            if (EtatActuel->LesChemins[i] == listeTabou[j]) {
                trouve = true;
            }
        }
        if (trouve == false) {
            bool arrive = false;
            for (int j = 0; j < DepotArrive.size(); j++) {
                if (EtatActuel->LesChemins[i] == DepotArrive[j]) {
                    arrive = true;
                }
            }
            if (arrive == true) {
                listeTransitionDepot.push_back(EtatActuel->LesChemins[i]);
            } else {
                listeTransitionEtat.push_back(EtatActuel->LesChemins[i]);
            }
        }
    }

    Etat* choix;
    if (listeTransitionEtat.size() > 0) {
        choix = listeTransitionEtat[rand() % listeTransitionEtat.size()];
    } else {
        choix = listeTransitionDepot[rand() % listeTransitionDepot.size()];
    }
    for (int i = 0; EtatActuel->LesChemins.size(); i++) {
        if (EtatActuel->LesChemins[i] == choix) {
            return i;
        }
    }
    return -1;
}
