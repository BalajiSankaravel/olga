/* 
 * File:   Ligne.cpp
 * Author: Flav
 * 
 * Created on 26 novembre 2016, 22:26
 */

#include <vector>

#include "Ligne.h"

Ligne::Ligne(string pName,bool pAller) {
    name = pName;
    aller = pAller;
}

string Ligne::getName(){
    return name;
}

bool Ligne::getAller(){
    return aller;
}

void Ligne::ajoutVoyage(string terminus, string heure,int dist){
    lesVoyages.push_back(Voyage(terminus,heure,dist));
}

void Ligne::modificationArrivee(string terminus, string heure,int index){
    lesVoyages[index].setTermFin(terminus);
    lesVoyages[index].setHeureFin(heure);
}

void Ligne::modificationDepart(string terminus, string heure,int index){
    lesVoyages[index].setTermDeb(terminus);
    lesVoyages[index].setHeureDeb(heure);
}


void Ligne::afficheLesVoyage(){
    for (int i= 0; i < lesVoyages.size();i++){
        cout<<lesVoyages[i].getTermDeb()<<": ";
        cout<<lesVoyages[i].getHeureDeb()<<" --> ";
        cout<<lesVoyages[i].getTermFin()<<": ";
        cout<<lesVoyages[i].getHeureFin()<<"   distance : ";
        cout<<lesVoyages[i].getDistance()<<endl;
    }
}