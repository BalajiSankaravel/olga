/* 
 * File:   main.cpp
 * Author: Flav
 *
 * Created on 25 novembre 2016, 11:06
 */


#include "FilesReader.h"
#include "Ligne.h"
#include <string>


using namespace std;

/*
 * 
 */



vector<Ligne> generationDesLignes(vector <T_UneLigne> lesHoraires) {
    vector <Ligne> lesLignes;
    for (int i = 0; i < lesHoraires.size(); i++) {
        lesLignes.push_back(Ligne(lesHoraires[i].Nom, lesHoraires[i].Aller));
        int validTrajet[lesHoraires[i].Horaire[1].size()];
        for (int z = 0; z < lesHoraires[i].Horaire[1].size(); z++) {
            validTrajet[z] = 0;
        }
        
        for (int j = 0; j < lesHoraires[i].Terminus.size(); j++) {
            for (int z = 0; z < lesHoraires[i].Horaire[j].size(); z++) {
                if (lesHoraires[i].Horaire[j][z] != "") {
                    if (validTrajet[z] == 0) {
                        lesLignes[i].ajoutVoyage(lesHoraires[i].Terminus[j], lesHoraires[i].Horaire[j][z],lesHoraires[i].Distance[z],z);
                        validTrajet[z] = 2;
                    } else if (validTrajet[z] == 1) {
                        lesLignes[i].modificationDepart(lesHoraires[i].Terminus[j], lesHoraires[i].Horaire[j][z], z);
                        validTrajet[z] = 2;
                    } else if (validTrajet[z] == 2) {
                        lesLignes[i].modificationArrivee(lesHoraires[i].Terminus[j], lesHoraires[i].Horaire[j][z], z);
                    }
                } else {
                    if (validTrajet[z] == 0) {
                        lesLignes[i].ajoutVoyage("", "",lesHoraires[i].Distance[z],z);
                        validTrajet[z] = 1;
                    }
                }
            }
        }
    }
    return lesLignes;
}

int main(int argc, char** argv) {

    FilesReader leFichier;

    /*Recuperation des informations dans les fichiers*/
    string contenu = leFichier.OpenFile("horaires.csv");
    vector <T_UneLigne> lesHoraires = leFichier.extractHoraire(contenu);

    contenu = leFichier.OpenFile("terminus.csv");
    vector <vector<int> > lesTempsTerminus = leFichier.createMatrice(contenu);

    contenu = leFichier.OpenFile("dist_terminus.csv");
    vector <vector<int> > lesDistTerminus = leFichier.createMatrice(contenu);

    /*Creation des Voyages*/
    vector <Ligne> lesLignes = generationDesLignes(lesHoraires);
    
    for (int i = 0; i < lesLignes.size(); i++) {
        cout<<lesLignes[i].getName()<<endl;
        lesLignes[i].afficheLesVoyage();
        cout<<endl;
    }
    

    /*Creation Graphe*/
    
    

    return 0;
}

