/* 
 * File:   Voyage.cpp
 * Author: Flav
 * 
 * Created on 27 novembre 2016, 15:25
 */

#include "Voyage.h"

Voyage::Voyage(string terminus, string heure, int dist) {
    TermDeb = terminus;
    HeureDeb = heure;
    distance = dist;
}

void Voyage::setTermFin(string terminus) {
    TermFin = terminus;
}

void Voyage::setTermDeb(string terminus) {
    TermDeb = terminus;
}
void Voyage::setHeureDeb(string heure) {
    HeureDeb = heure;
}


void Voyage::setHeureFin(string heure) {
    HeureFin = heure;
}

void Voyage::setDistance(int dist) {
    distance = dist;
}

string Voyage::getTermDeb() {
    return TermDeb;
}

string Voyage::getHeureDeb() {
    return HeureDeb;
}

string Voyage::getTermFin() {
    return TermFin;
}

string Voyage::getHeureFin() {
    return HeureFin;
}

int Voyage::getDistance() {
    return distance;
}

