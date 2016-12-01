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
#include <math.h>

using namespace std;

Graphe::Graphe(int nbDepot, vector <vector<int> >* pTemps, vector <vector<int> >* pDist, vector<string>* pIndex) {
    matriceTemps = pTemps;
    matriceDist = pDist;
    indexMatrice = pIndex;
    for (int i = 0; i < nbDepot; i++) {
<<<<<<< HEAD
        Voyage* unDepot = new Voyage("", "", 0, "Depot" + to_string(i));
        unDepot->TermDeb = "T0";
        unDepot->TermFin = "T0";
        //unDepot->TermDeb = to_string(i);
        //unDepot->TermFin = to_string(i);
=======
        Voyage* unDepot = new Voyage("", "", 0, "Depot");
        unDepot->TermDeb = "T0";
        unDepot->TermFin = "T0";
//        unDepot->TermDeb = to_string(i);
//        unDepot->TermFin = to_string(i);
>>>>>>> origin/master
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
    typeGen = 0;
    for (auto i : lesEtats) {
        for (auto j : lesEtats) {
            if (i != j) {
                if ((this->split(i->voyage->name, ':')[0]) == (split(j->voyage->name, ':')[0])) {
                    if ((j->voyage->HeureDeb.tm_hour * 60 + j->voyage->HeureDeb.tm_min - 5) -
                            (i->voyage->HeureFin.tm_hour * 60 + i->voyage->HeureFin.tm_min) >= 0 && i->voyage->TermFin == j->voyage->TermDeb) {
                        i->LesChemins.push_back(j);
                    } else {

                        int l = getTemps(i->voyage->TermFin, j->voyage->TermDeb);
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
    typeGen = 1;
    for (auto i : lesEtats) {
        for (auto j : lesEtats) {
            if (i != j) {
                if ((j->voyage->HeureDeb.tm_hour * 60 + j->voyage->HeureDeb.tm_min - 5) -
                        (i->voyage->HeureFin.tm_hour * 60 + i->voyage->HeureFin.tm_min) >= 0 && i->voyage->TermFin == j->voyage->TermDeb) {
                    i->LesChemins.push_back(j);
                } else {
                    int l = getTemps(i->voyage->TermFin, j->voyage->TermDeb);

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

vector < vector < Etat*> > Graphe::ResolutionSame(int* temps, int* distance) {
    int nbBus = 0;
    vector <Etat*> tabou;
    vector < vector < Etat* > > ListeBus;

    while (tabou.size() < lesEtats.size()) {
        vector < Etat* > trajetBus;
        Etat* Bus = DepotDepart[rand() % DepotDepart.size()];
        trajetBus.push_back(Bus);
        nbBus++;
        bool listeArrive = false;
        int limit = 0;
        while (!listeArrive) {

            int indexC = GestionCheminSuivantGloutonDepotLast(Bus, tabou);
            if (indexC < 0) exit(0);
            limit++;
            /////////////Distance

            *distance += Bus->voyage->distance;
            *distance += getDistance(Bus->voyage->TermFin, Bus->LesChemins[indexC]->voyage->TermDeb);

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
        tps = getTemps(ListeBus[i][0]->voyage->TermFin, ListeBus[i][1]->voyage->TermDeb);
        tps = ((ListeBus[i][ListeBus[i].size() - 2]->voyage->HeureFin.tm_hour * 60 + ListeBus[i][ListeBus[i].size() - 2]->voyage->HeureFin.tm_min)-((ListeBus[i][1]->voyage->HeureDeb.tm_hour * 60 + ListeBus[i][1]->voyage->HeureDeb.tm_min)));
        *temps += tps;
        tps = getTemps(ListeBus[i][ListeBus[i].size() - 2]->voyage->TermFin, ListeBus[i][ListeBus[i].size() - 1]->voyage->TermDeb);
        *temps += tps;

    }
    return ListeBus;
}

vector < vector < Etat*> > Graphe::ResolutionMulti(int* temps, int* distance) {
    int nbBus = 0;
    vector <Etat*> tabou;
    vector < vector < Etat* > > ListeBus;

    while (tabou.size() < lesEtats.size()) {
        vector < Etat* > trajetBus;
        Etat* Bus = DepotDepart[rand() % DepotDepart.size()];
        trajetBus.push_back(Bus);
        nbBus++;
        bool listeArrive = false;
        int limit = 0;
        while (!listeArrive) {
            int indexC = GestionCheminSuivantGRASPDepotLastLimited(Bus, tabou, limit);
            if (indexC < 0) exit(0);
            limit++;
            /////////////Distance

            *distance += Bus->voyage->distance;
            *distance += getDistance(Bus->voyage->TermFin, Bus->LesChemins[indexC]->voyage->TermDeb);

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
        tps = getTemps(ListeBus[i][0]->voyage->TermFin, ListeBus[i][1]->voyage->TermDeb);
        tps = ((ListeBus[i][ListeBus[i].size() - 2]->voyage->HeureFin.tm_hour * 60 + ListeBus[i][ListeBus[i].size() - 2]->voyage->HeureFin.tm_min)-((ListeBus[i][1]->voyage->HeureDeb.tm_hour * 60 + ListeBus[i][1]->voyage->HeureDeb.tm_min)));
        *temps += tps;
        tps = getTemps(ListeBus[i][ListeBus[i].size() - 2]->voyage->TermFin, ListeBus[i][ListeBus[i].size() - 1]->voyage->TermDeb);
        *temps += tps;

    }
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

int Graphe::calculDistFromBus(vector<Bus*> ListeBus) {
    int distance = 0;
    for (int i = 0; i < ListeBus.size(); i++) {
        for (int j = 0; j < ListeBus[i]->getItineraire().size(); j++) {
            distance += ListeBus[i]->getItineraire()[j]->distance;
            if (j != ListeBus[i]->getItineraire().size() - 1) {
                distance += getDistance(ListeBus[i]->getItineraire()[j]->TermFin, ListeBus[i]->getItineraire()[j + 1]->TermDeb);
            }
        }
    }
    return distance;
}

int Graphe::calculTimeFromBus(vector<Bus*> ListeBus) {
    int tps = 0;
    for (int i = 0; i < ListeBus.size(); i++) {
        int tps = 0;
        tps += getTemps(ListeBus[i]->getItineraire()[0]->TermFin, ListeBus[i]->getItineraire()[1]->TermDeb);
        tps += ((ListeBus[i]->getItineraire()[ListeBus[i]->getItineraire().size() - 2]->HeureFin.tm_hour * 60 + ListeBus[i]->getItineraire()[ListeBus[i]->getItineraire().size() - 2]->HeureFin.tm_min)-((ListeBus[i]->getItineraire()[1]->HeureFin.tm_hour * 60 + ListeBus[i]->getItineraire()[1]->HeureFin.tm_min)));
        tps += getTemps(ListeBus[i]->getItineraire()[ListeBus[i]->getItineraire().size() - 2]->TermFin, ListeBus[i]->getItineraire()[ListeBus[i]->getItineraire().size() - 1]->TermDeb);
    }
    return tps;
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
<<<<<<< HEAD
            if (EtatActuel->voyage->name.find("Depot") != string::npos) {//TODO
=======
            if (EtatActuel->voyage->name.find("Depot")  != string::npos) {//TODO
>>>>>>> origin/master
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
            if (getTemps(EtatActuel->voyage->TermFin, listeTransitionDepot[k]->voyage->TermDeb) < min) {
                min = getTemps(EtatActuel->voyage->TermFin, listeTransitionDepot[k]->voyage->TermDeb);
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

    if (listeTransitionEtat.size() > 0) {
        int min = INT_MAX - hysteresis;
        for (int k = 0; k < listeTransitionEtat.size(); k++) {
            int temps;
            int random = 0;
            if (hysteresis == 0) {
                random = 0;
            } else {
                random = ((rand() % (hysteresis * 2)) - hysteresis);
            }
            min = (min + random);
            if (min < 0) min = 0;
<<<<<<< HEAD
            if (EtatActuel->voyage->name.find("Depot") != string::npos) {//TODO
                                cout<<"Ok"<<endl;
=======
            if (EtatActuel->voyage->name.find("Depot")  != string::npos) {
>>>>>>> origin/master
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
        int min = INT_MAX - hysteresis;
        for (int k = 0; k < listeTransitionDepot.size(); k++) {
            int random = 0;
            if (hysteresis == 0) {
                random = 0;
            } else {
                random = ((rand() % (hysteresis * 2)) - hysteresis);
            }
            min = (min + random);
            if (min < 0) min = 0;
            if (getTemps(EtatActuel->voyage->TermFin, listeTransitionDepot[k]->voyage->TermDeb) < min) {
                min = getTemps(EtatActuel->voyage->TermFin, listeTransitionDepot[k]->voyage->TermDeb);
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

int Graphe::GestionCheminSuivantGRASPDepotLastLimited(Etat* EtatActuel, vector <Etat*> listeTabou, int limit) {
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

    if (limit > (limitation - 1))listeTransitionEtat.clear();

    if (listeTransitionEtat.size() > 0) {
        int min = INT_MAX - hysteresis;
        for (int k = 0; k < listeTransitionEtat.size(); k++) {
            int temps;
            int random = 0;
            if (hysteresis == 0) {
                random = 0;
            } else {
                random = ((rand() % (hysteresis * 2)) - hysteresis);
            }
            min = (min + random);
            if (min < 0) min = 0;
<<<<<<< HEAD
            if (EtatActuel->voyage->name.find("Depot") != string::npos) {//TODO
                cout<<"Ok"<<endl;
=======
            if (EtatActuel->voyage->name.find("Depot")  != string::npos) {
>>>>>>> origin/master
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
        int min = INT_MAX - hysteresis;
        for (int k = 0; k < listeTransitionDepot.size(); k++) {
            int random = 0;
            if (hysteresis == 0) {
                random = 0;
            } else {
                random = ((rand() % (hysteresis * 2)) - hysteresis);
            }
            min = (min + random);
            if (min < 0) min = 0;
            if (getTemps(EtatActuel->voyage->TermFin, listeTransitionDepot[k]->voyage->TermDeb) < min) {
                min = getTemps(EtatActuel->voyage->TermFin, listeTransitionDepot[k]->voyage->TermDeb);
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

int Graphe::getDistance(string TermA, string TermB) {
    int indexA;
    int indexB;
    int i = 0;
    while (TermA != (*indexMatrice)[i]) {
        i++;
    }
    indexA = i;
    i = 0;
    while (TermB != (*indexMatrice)[i]) {
        i++;
    }
    indexB = i;
    if (indexA > indexB) {
        int tmp = indexA;
        indexA = indexB;
        indexB = tmp;
    }


    return (*matriceDist)[indexA][indexB];

}

int Graphe::getTemps(string TermA, string TermB) {
    int indexA;
    int indexB;
    int i = 0;
    while (TermA != (*indexMatrice)[i]) {
        i++;
    }
    indexA = i;
    i = 0;
    while (TermB != (*indexMatrice)[i]) {
        i++;
    }
    indexB = i;
    if (indexA > indexB) {
        int tmp = indexA;
        indexA = indexB;
        indexB = tmp;
    }
    return (*matriceTemps)[indexA][indexB];

}