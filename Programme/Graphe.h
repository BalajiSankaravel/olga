/* 
 * File:   Graphe.h
 * Author: Flav
 *
 * Created on 27 novembre 2016, 16:54
 */

#include <vector>
#include "Etat.h"
#include "Ligne.h"
using namespace std;
#ifndef GRAPHE_H
#define	GRAPHE_H

class Graphe {
public:
    Graphe(int,vector <vector<int> >*,vector <vector<int> >*);
    void CreationEtat(vector <Ligne>*);
    void GenerationEtatSameLine();
    void GenerationetatMultiLine();
    void GenerationArcMemeLigne();
    void GenerationArcLigneDiff();
    string RemFirstChar(string);
    int getTempsDiff(Etat* , Etat* );
    vector < vector < Etat*> > Resolution(int*,int*);
    int GestionCheminSuivantRandowDepotLast(Etat*,vector <Etat*>);
    int GestionCheminSuivantGloutonDepotLast(Etat*,vector <Etat*>);
    int GestionCheminSuivantGRASPDepotLast(Etat*,vector <Etat*>);
    void split(const std::string &s, char delim, std::vector<std::string> &elems);
    vector<string> split(const std::string &s, char delim);
    vector<Etat*> lesEtats;
    vector<Etat*> DepotDepart;
    vector<Etat*> DepotArrive;
    vector <vector<int> >* matriceTemps;
    vector <vector<int> >* matriceDist;
    
};

#endif	/* GRAPHE_H */

