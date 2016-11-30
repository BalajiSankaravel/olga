/* 
 * File:   FilesReader.cpp
 * Author: Flav
 * 
 * Created on 25 novembre 2016, 11:06
 */

#include "FilesReader.h"
#include <vector>



FilesReader::FilesReader() {
}

string FilesReader::OpenFile(string fileName) {
    ifstream fichier(fileName);
    if (fichier) {
        string ligne;
        string contenu;
        while (getline(fichier, ligne)) {
            contenu += ligne + '\n';
        }
        fichier.close();
        return contenu;
    } else return 0;
}

int FilesReader::getNombreTerm(string information) {
    int nbTerminus = -1;
    istringstream lesinfos(information);
    string line;
    getline(lesinfos, line);
    stringstream lineStream(line);
    string cell;
    while (getline(lineStream, cell, ',')) {
        nbTerminus++;
    }
    return nbTerminus;
}

 vector < vector<int> > FilesReader::createMatrice(string information) {
    int i = -1;
    int j = -1;
    int nbTerminus = getNombreTerm(information);
    vector < vector<int> > laMatrice(nbTerminus, vector<int>(nbTerminus));
    istringstream lesinfos(information);
    string line;
    while (getline(lesinfos, line)) {
        stringstream lineStream(line);
        string cell;
        while (getline(lineStream, cell, ',')) {
            if (j != -1 && i != -1) {
                if (j < nbTerminus && i < nbTerminus) {
                    laMatrice[i][j] = stoi(cell);
                }
            }
            j++;
        }
        i++;
        j = -1;
    }
    return laMatrice;
}

vector<T_UneLigne>  FilesReader::extractHoraire(string lesInformations) {
    vector <T_UneLigne> pLignes;
    int indexLigne = 0;
    int Terminus = -1;
    int mode;
    bool debut = true;
    bool aller = true;
    int etape;
    int j = 0;
    T_UneLigne resetLigne;
    T_UneLigne uneLigne;
    istringstream lesinfos(lesInformations);
    string line;
    while (getline(lesinfos, line)) {
        etape = 2;
        if (getNombreTerm(line) == 0) {
            etape = 1;
            if (!debut) {
                pLignes.push_back(uneLigne);
                indexLigne++;
                Terminus = -1;
                uneLigne = resetLigne;
            }
        }
        stringstream lineStream(line);
        string cell;
        while (getline(lineStream, cell, ',')) {
            switch (etape) {
                case 1:
                    uneLigne.Nom = cell;
                    uneLigne.Aller = aller;
                    aller = !aller;
                    etape = 2;
                    break;
                case 2:
                    if (cell[0] != 'D') {
                        uneLigne.Terminus.push_back(cell);
                        Terminus++;
                        uneLigne.Horaire.push_back(vector<string>());
                        mode = 1;
                    } else mode = 2;
                    etape = 3;
                    break;
                case 3:if (mode == 1) {
                        uneLigne.Horaire[Terminus].push_back(cell);
                    }
                    if (mode == 2) {
                        uneLigne.Distance.push_back(stoi(cell));
                    }
                    break;
            }
        }
        if (debut) debut = false;
    }
    pLignes.push_back(uneLigne);
    return pLignes;
}



