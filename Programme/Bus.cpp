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
}

Bus::pushVoyage(Voyage* voy) {
    this->itineraire.push_back(voy);
}

Bus::setNumero(int numero){
    this->numero = numero;
}

Bus::setDepot(int depot){
    this->depotdepart = depot;
}

Bus::getText(){
    string text = "bus" + this->numero + "," + this->depotdepart;
    for (Voyage elem : itineraire) {
        text += "," + elem->getName();
    }
    
}

Bus::~Bus() {
}

