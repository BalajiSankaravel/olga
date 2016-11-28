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

void Ligne::ajoutVoyage(string terminus, string heure,int dist,int index){
    char sens = 'r';
    if(aller) sens = 'a';
    string numLigne = name;
    numLigne = numLigne.replace( 1, 5,"");
    string nom = numLigne +':'+sens+':'+'v'+ to_string(index+1);
    lesVoyages.push_back(Voyage(terminus,heure,dist,nom));
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
        cout<<lesVoyages[i].HeureDeb.tm_hour<<":"<<lesVoyages[i].HeureDeb.tm_min<<" --> ";
        cout<<lesVoyages[i].getTermFin()<<": ";
        cout<<lesVoyages[i].HeureFin.tm_hour<<":"<<lesVoyages[i].HeureFin.tm_min<<"   distance : ";
        cout<<lesVoyages[i].getDistance()<<"  Voyage: ";
        cout<<lesVoyages[i].getName()<<endl;;
    }
}
