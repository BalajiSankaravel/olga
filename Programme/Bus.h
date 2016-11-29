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
#include <Voyage>

using namespace std;

class Bus {
public:
    Bus();
    Bus(const Bus& orig);
    Bus::pushVoyage(Voyage voy);
    Bus::setDepot(int depot);
    Bus::setNumero(int numero);
    string Bus::getText();
    virtual ~Bus();
private:
    int numero;
    int depotdepart;
    vector< Voyage* > itineraire;
};

#endif /* BUS_H */

