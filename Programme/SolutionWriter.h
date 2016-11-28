/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SolutionWriter.h
 * Author: Alex
 *
 * Created on 28 novembre 2016, 09:07
 */

#ifndef SOLUTIONWRITTER_H
#define SOLUTIONWRITTER_H
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

class SolutionWriter {
public:
    SolutionWriter();
    SolutionWriter(int NbBus, double dureeTotal, double KmTotal);
    SolutionWriter::write(vector <Bus*>);
    virtual ~SolutionWriter();
private:
    int NbBus;
    double dureeTotal, KmTotal;
    string equipe = "# Antoine Eon, Flavien Berard, Thibaut Curbera, Jeremie Gidenne,Alexandre Bizien";
};

/*
    # Antoine Eon, Flavien Berard, Thibaut Curbera, Jeremie Gidenne, Alexandre Bizien
    NbBus,duréeTotal,KmTotal
    busi,depot,numeroLigne:aller/retour:numeroVoyage,numeroLigne:aller/retour:numeroVoyage,.... 
    bus1,3,l2:a:v1,l2:r:v3,l1:r:v1,. . .
    bus2,1,l2:r:v1,l2:a:v2,l1:r:v2,. . .
    bus3,3,l3:a:v1,l4:a:v2,l3:a:v3,. . .
    bus4,2,l4:r:v2,l3:r:v1,l4:r:v
*/



#endif /* SOLUTIONWRITTER_H */

