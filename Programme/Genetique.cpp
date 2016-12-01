/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Genetique.cpp
 * Author: antoine
 * 
 * Created on 30 novembre 2016, 15:29
 */

#include "Genetique.h"
#include <vector>
#include "Bus.h"
#include "Graphe.h"
#include <iostream>
#include <sstream>
#include <limits.h>
#include "PARAMETRE.h"
using namespace std;



Genetique::Genetique(vector<Bus*>* listeBus, Graphe* graphe,vector <vector<int> >* pTemps, vector <vector<int> >* pDist) {
    leGraphe = graphe;
    lesBus = listeBus;
    matriceTemps = pTemps;
    matriceDist= pDist;

}

vector < vector<Etat*> >* Genetique::voyageToEtat(){

    vector < vector<Etat*> >* listeEtatSolution = new vector < vector < Etat*> >();
    //parcours des bus
    for (int i = 0; i< (*lesBus).size(); i++){
        vector<Etat*>* trajetGraphe = new vector<Etat*>();
        //parcours des voyages du bus
        for (int j = 0; j < (*lesBus)[i]->getItineraire().size(); j++){            
            //parcours des etats du Graphe
            for (int k = 0; k < leGraphe->lesEtats.size(); k++){
                if (leGraphe->lesEtats[k]->voyage == (*lesBus)[i]->getItineraire()[j]){
                    trajetGraphe->push_back(leGraphe->lesEtats[k]);
                }                
            }
        }
        listeEtatSolution->push_back(*trajetGraphe);
    }
    return listeEtatSolution;
}
   
bool Genetique::CheckIfEtatsPresents (vector < vector < Etat*>>* listeEtatSolution){
    
    bool solutionAdmissible = true;
    // parcours des etats
    for (int indexEtat = 0; indexEtat < leGraphe->lesEtats.size(); indexEtat++){        
        bool etatSolution = false;
        // parcours des bus
        for (int indexBus = 0; indexBus < (*listeEtatSolution).size(); indexBus++){ 
            //parcours des etats du bus
            for (int indexEtatBus = 0; indexEtatBus < (*listeEtatSolution)[indexBus].size(); indexEtatBus++){                
                if (leGraphe->lesEtats[indexEtat] == (*listeEtatSolution)[indexBus][indexEtatBus]){
                    etatSolution = true;                    
                }
            }                
        }  
        if (etatSolution == false) solutionAdmissible = false;
    }
    return solutionAdmissible;    
}


bool Genetique::CheckIfEtatsPresentsOnlyOnce(vector < vector < Etat*>>* listeEtatSolution){
    
    bool solutionAdmissible = true;
    // parcours des bus
    for (int indexBusCandidat = 0; indexBusCandidat < (*listeEtatSolution).size(); indexBusCandidat++){
        //parcours des etats du bus
        for (int indexEtatBusCandidat = 0; indexEtatBusCandidat < (*listeEtatSolution)[indexBusCandidat].size(); indexEtatBusCandidat++){ 
            int result = 0;
            // reparcours des bus
            for (int indexBusRecherche = 0; indexBusRecherche < (*listeEtatSolution).size(); indexBusRecherche++){
                //reparcours des etats du bus
                for (int indexEtatBusRecherche = 0; indexEtatBusRecherche < (*listeEtatSolution)[indexBusRecherche].size(); indexEtatBusRecherche++){ 
                    if ((*listeEtatSolution)[indexBusCandidat][indexEtatBusCandidat] == (*listeEtatSolution)[indexBusRecherche][indexEtatBusRecherche]){
                        result ++;
                    }            
                }
            }
            if (result != 1) solutionAdmissible = false;
        }
    }   
    return solutionAdmissible;
}


bool Genetique::CheckTrajetAdmissible(vector < vector < Etat*>>* listeEtatSolution){
    bool solutionAdmissible = true;    
    // parcours des bus
    for (int indexBusCandidat = 0; indexBusCandidat < (*listeEtatSolution).size(); indexBusCandidat++){        
        //pracours des etats du bus
        for (int indexEtatBusCandidat = 1; indexEtatBusCandidat < (*listeEtatSolution)[indexBusCandidat].size(); indexEtatBusCandidat++){
            bool trajetAdmissible = false;
            //parcours liste des etats suivants de l'etat precedant
            for (int indexVoyage = 0; indexVoyage < (*listeEtatSolution)[indexBusCandidat][indexEtatBusCandidat - 1]->LesChemins.size();  indexVoyage++){        
                if ((*listeEtatSolution)[indexBusCandidat][indexEtatBusCandidat]->voyage == (*listeEtatSolution)[indexBusCandidat][indexEtatBusCandidat - 1]->LesChemins[indexVoyage]->voyage){
                    trajetAdmissible = true;
                } 
            }            
            if (trajetAdmissible == false) solutionAdmissible = false;
        }        
    }
    return solutionAdmissible;
}

vector<long*>* Genetique::calculScore(){
    
    vector<long*>* resultat = new vector<long*>();
    // nombre de bus
    long* nombreBus = new long(); 
    (*nombreBus) = lesBus->size();
    
    //Distance totale
    long* distTotale = new long;
    *distTotale = 0;
    
    //parcours des bus
    for (int indexBus = 0; indexBus < lesBus->size(); indexBus ++){
        //parcours les voyages du bus
        for (int indexVoyagesBus = 0; indexVoyagesBus < (*lesBus)[indexBus]->getItineraire().size(); indexVoyagesBus ++){
            
            *distTotale += (*lesBus)[indexBus]->getItineraire()[indexVoyagesBus]->distance;
        }        
    }
    
    resultat->push_back(nombreBus);
    resultat->push_back(distTotale);
    //Temps total
    return resultat;
    
}

bool Genetique::Fitness(){
    
    vector < vector < Etat*>>* busEtat = voyageToEtat();
    bool rep = CheckIfEtatsPresents(busEtat);
    rep = CheckIfEtatsPresentsOnlyOnce(busEtat);
    rep = CheckTrajetAdmissible(busEtat);
    vector<long*>* resultat = calculScore();
    cout << "nombre bus : " << *(*resultat)[0];
    cout << "distance bus : " << *(*resultat)[1];

    
}