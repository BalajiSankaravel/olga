#include "FilesReader.h"
#include "Ligne.h"
#include "Graphe.h"
#include <string>
#include <limits.h>
#include "Voyage.h"
#include "Bus.h"
#include "SolutionWriter.h"
#include "PARAMETRE.h"
#include "Solution.h"


using namespace std;

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
                        lesLignes[i].ajoutVoyage(lesHoraires[i].Terminus[j], lesHoraires[i].Horaire[j][z], lesHoraires[i].Distance[z], z);
                        validTrajet[z] = 2;
                    } else if (validTrajet[z] == 1) {
                        lesLignes[i].modificationDepart(lesHoraires[i].Terminus[j], lesHoraires[i].Horaire[j][z], z);
                        validTrajet[z] = 2;
                    } else if (validTrajet[z] == 2) {
                        lesLignes[i].modificationArrivee(lesHoraires[i].Terminus[j], lesHoraires[i].Horaire[j][z], z);
                    }
                } else {
                    if (validTrajet[z] == 0) {
                        lesLignes[i].ajoutVoyage("", "", lesHoraires[i].Distance[z], z);
                        validTrajet[z] = 1;
                    }
                }
            }
        }
    }
    return lesLignes;
}

void gestionDiff(FilesReader* leFichier) {
    /*Recuperation des informations dans les fichiers*/
    string contenu = leFichier->OpenFile("horaires.csv");
    vector <T_UneLigne> lesHoraires = leFichier->extractHoraire(contenu);

    contenu = leFichier->OpenFile("terminus.csv");
    vector <vector<int> > lesTempsTerminus = leFichier->createMatrice(contenu);

    contenu = leFichier->OpenFile("dist_terminus.csv");
    vector <vector<int> > lesDistTerminus = leFichier->createMatrice(contenu);
    vector <string> lesIndexMatrice = leFichier->getIndexMatrice(contenu);
    
    
    
    /*Creation des Voyages*/
    vector <Ligne> lesLignes = generationDesLignes(lesHoraires);
    Graphe leGraphe(1, &lesTempsTerminus, &lesDistTerminus, &lesIndexMatrice);
    leGraphe.CreationEtat(&lesLignes);
    leGraphe.GenerationArcLigneDiff();
    int distance = 0;
    int temps = 0;
    int nbBusMin = INT_MAX;
    float score = 99999.99;
    int disMin = 0;
    int tpsMin = 0;
    vector < vector <Etat*> > resolutionMin;
    for (int k = LIMIT_MIN; k <= LIMIT_MAX; k++) {
        leGraphe.limitation = k;
        cout << "l : " << leGraphe.limitation << endl;
        for (int j = 0; j <= HYSTERESIS_MAX; j++) {
            leGraphe.hysteresis = j;
            cout << "h : " << leGraphe.hysteresis << endl;
            for (int i = 0; i < NOMBRE_ITERATION; i++) {
                vector < vector <Etat*> > resolution = leGraphe.ResolutionMulti(&temps, &distance);
                if (resolution.size() <= nbBusMin) {
                    if ((((float) temps) * (float) COEF_TEMPS + (float) distance) < score) {
                        disMin = distance;
                        tpsMin = temps;
                        score = ((float) temps) * (float) COEF_TEMPS + (float) distance;
                        cout << "Sol, s : " << score << " l : " << leGraphe.limitation << " h : " << leGraphe.hysteresis << " n : " << resolution.size() << endl;
                        nbBusMin = resolution.size();
                        resolutionMin = resolution;
                    }
                }
                distance = 0;
                temps = 0;
            }
        }
    }
    vector< Bus*>* lesBus = new vector<Bus*>();
    for (int i = 0; i < resolutionMin.size(); i++) {
        Bus* bus = new Bus(i, 0);
        for (int j = 1; j < resolutionMin[i].size() - 1; j++) {
            bus->pushVoyage(resolutionMin[i][j]->voyage);
        }
        lesBus->push_back(bus);
    }
    vector<Solution*>* v = new vector<Solution*>();
    Solution* s = new Solution();
    s->nbBus = lesBus->size();
    s->KmTotal = disMin;
    s->TpsTotal = tpsMin;
    s->lesBus = lesBus;
    v->push_back(s);
    cout << (*v)[0]->getText() << endl;
    SolutionWriter sw;
    sw.write(*v);
    
}

int main(int argc, char** argv) {

    FilesReader leFichier;
    srand(time(NULL));
    gestionDiff(&leFichier);
    //    cout << "r";
    cout << "-----FIN" << endl;
    return 0;
}

