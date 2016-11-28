/* 
 * File:   Ligne.h
 * Author: Flav
 *
 * Created on 26 novembre 2016, 22:26
 */
#include <iostream>

#include "Voyage.h"
using namespace std;
#ifndef LIGNE_H
#define	LIGNE_H

class Ligne {
public:
    Ligne(string,bool);
    string getName();
    bool getAller();
    void ajoutVoyage(string,string,int);
    void afficheLesVoyage();
    void modificationArrivee(string,string,int);
    void modificationDepart(string,string,int);
protected:
    string name;
    bool aller;
    vector< Voyage> lesVoyages;

};

#endif	/* LIGNE_H */

