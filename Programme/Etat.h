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
protected:
    Voyage* voyage;
    vector< Voyage* > Suivant;
};

#endif	/* ETAT_H */

