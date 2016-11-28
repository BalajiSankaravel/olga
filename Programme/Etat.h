/* 
 * File:   Etat.h
 * Author: Flav
 *
 * Created on 27 novembre 2016, 16:54
 */

#ifndef ETAT_H
#define	ETAT_H
#include <vector>
#include "Voyage.h"

using namespace std;


class Etat {
public:
    Etat(Voyage*);
    string getName();
    Voyage* voyage;
    vector<Voyage*> LesChemins;
    
};

#endif	/* ETAT_H */

