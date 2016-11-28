/* 
 * File:   Graphe.h
 * Author: Flav
 *
 * Created on 27 novembre 2016, 16:54
 */

#include <vector>
#include "Etat.h"
using namespace std;
#ifndef GRAPHE_H
#define	GRAPHE_H

class Graphe {
public:
    Graphe();
protected:
    vector<Etat> lesEtats;
    
};

#endif	/* GRAPHE_H */

