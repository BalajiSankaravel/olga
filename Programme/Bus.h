/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bus.h
 * Author: Alex
 *
 * Created on 28 novembre 2016, 11:52
 */

#ifndef BUS_H
#define BUS_H
#include <vector>
#include "Voyage.h"

using namespace std;

class Bus {
public:
    Bus();
    Bus(int,int);
    void pushVoyage(Voyage* voy);
    void setDepot(int depot);
    void setNumero(int numero);
    void setTauxUtilisation(int tauxUtilisation);
    int getTauxUtilisation();
    string getText();
private:
    int numero;
    int depotdepart;
    vector< Voyage* > itineraire;
    int tauxUtilisation;
};

#endif /* BUS_H */

