/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bus.cpp
 * Author: Alex
 * 
 * Created on 28 novembre 2016, 11:52
 */

#include "Bus.h"

Bus::Bus() {
}

Bus::Bus(int numero, int depotdepart) {
    this->numero = numero;
    this->depotdepart = depotdepart;
    this->tauxUtilisation = 0;
}

void Bus::pushVoyage(Voyage* voy) {
    this->itineraire.push_back(voy);
}

void Bus::setNumero(int numero){
    this->numero = numero;
}

void Bus::setDepot(int depot){
    this->depotdepart = depot;
}

void Bus::setTauxUtilisation(int tauxUtilisation){
    this->tauxUtilisation = tauxUtilisation;
}

int Bus::getTauxUtilisation(){
    return this->tauxUtilisation;
}

string Bus::getText(){
    string text = "bus" + to_string(numero) + "," + to_string(depotdepart);
    for (auto elem : itineraire) {
        text += "," + elem->getName();
    }
    return text;
    
}


