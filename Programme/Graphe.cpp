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
        unDepot->TermDeb = "T0";
        unDepot->TermFin = "T0";
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
            DepotDepart[z]->LesChemins.push_back(lesEtats[i]);
            lesEtats[i]->LesChemins.push_back(DepotArrive[z]);
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
    //   cout << "nb : " << lesEtats.size();


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
//    int arc = 0;
//    for (auto i : lesEtats) {
//        cout << "Etat : " << i->getName() << endl;
//        for (auto j : i->LesChemins) {
//            arc++;
//            cout << "Arc : " << j->voyage->name << endl;
//        }
//    }
//    cout << "Nb arc : " << arc << endl;
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
    
//        int arc = 0;
//        for (auto i : lesEtats) {
//            cout << "Etat : " << i->getName() << endl;
//            for (auto j : i->LesChemins) {
//                arc++;
//                cout << "Arc : " << j->voyage->name << endl;
//            }
//        }
//        cout<<"Nb arc : "<<arc<<endl;
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


vector < vector < Etat*> >  Graphe::Resolution(int* temps, int* distance){
    int nbBus = 0;
    vector <Etat*> tabou;
    vector < vector < Etat* > > ListeBus;
    
    while(tabou.size() < lesEtats.size()){
        vector < Etat* > trajetBus;
        Etat* Bus = DepotDepart[rand() % DepotDepart.size()];     
        trajetBus.push_back(Bus);
        nbBus++;
        bool listeArrive = false;
        while(!listeArrive){
            int indexC = GestionCheminSuivant(Bus,tabou);
            if(indexC < 0) exit(0);
            
            *distance += (*matriceDist)[stoi(RemFirstChar(Bus->voyage->TermDeb))][stoi(RemFirstChar(Bus->voyage->TermFin))];
            int i = (*matriceTemps)[stoi(RemFirstChar(Bus->voyage->TermDeb))][stoi(RemFirstChar(Bus->voyage->TermFin))];
            if (i < 5) i = 5;
            *temps += i;
            
            *distance += (*matriceDist)[stoi(RemFirstChar(Bus->voyage->TermFin))][stoi(RemFirstChar(Bus->LesChemins[indexC]->voyage->TermDeb))];
            i = (*matriceTemps)[stoi(RemFirstChar(Bus->voyage->TermFin))][stoi(RemFirstChar(Bus->LesChemins[indexC]->voyage->TermDeb))];
            if (i < 5) i = 5;
            *temps += i;            
            
            trajetBus.push_back(Bus->LesChemins[indexC]);
            Bus = Bus->LesChemins[indexC];
            
            bool nonTabou = false;
            for (auto i : DepotArrive){
                if(Bus == i) listeArrive = true;
                if(Bus == i ) nonTabou = true;
            }
            if (!nonTabou) tabou.push_back(Bus);
        }
        ListeBus.push_back(trajetBus);
    }
//    for(int i = 0; i <  ListeBus.size(); i++){
//        cout<<"Bus: "<<i<<endl;
//        for(int j = 0; j <  ListeBus[i].size(); j++){
//            cout<<"Trajet "<<j<<": "<<ListeBus[i][j]->voyage->name<<endl;
//        }
//    }
    return ListeBus;
}

int Graphe::GestionCheminSuivant(Etat* EtatActuel,vector <Etat*> listeTabou){
    //Verification des transitions
    vector <Etat*> listeTransitionDepot;
    vector <Etat*> listeTransitionEtat;
    for(int i = 0; i < EtatActuel->LesChemins.size(); i++){
        bool trouve = false;
        for(int j = 0; j < listeTabou.size(); j++){
            if(EtatActuel->LesChemins[i] == listeTabou[j]){
                trouve = true;
            }
        }
        if(trouve == false){
            bool arrive = false;
            for(int j = 0; j < DepotArrive.size(); j++){
                if(EtatActuel->LesChemins[i] == DepotArrive[j]){
                    arrive = true;
                } 
            }
            if(arrive == true){
                listeTransitionDepot.push_back(EtatActuel->LesChemins[i]);
            }else{
                listeTransitionEtat.push_back(EtatActuel->LesChemins[i]);
            }
        }
    }
    
    Etat* choix;
    if(listeTransitionEtat.size() > 0){
        choix = listeTransitionEtat[rand() % listeTransitionEtat.size()];
    }else{
        choix = listeTransitionDepot[rand() % listeTransitionDepot.size()];
    }
    for(int i = 0; EtatActuel->LesChemins.size(); i ++){
        if(EtatActuel->LesChemins[i] == choix){
            return i;
        }
    }
    return -1;
}
