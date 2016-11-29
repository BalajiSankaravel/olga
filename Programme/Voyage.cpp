/* 
 * File:   Voyage.cpp
 * Author: Flav
 * 
 * Created on 27 novembre 2016, 15:25
 */

#include "Voyage.h"
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Voyage::Voyage(string terminus, string heure, int dist, string pName) {
    TermDeb = terminus;
    if (heure != "") {
        HeureDeb.tm_hour = atoi(this->split(heure, ':')[0].c_str());
        HeureDeb.tm_min = atoi(this->split(heure, ':')[1].c_str());
    }
    distance = dist;
    name = pName;
}

void Voyage::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

vector<string> Voyage::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void Voyage::setTermFin(string terminus) {
    TermFin = terminus;
}

void Voyage::setTermDeb(string terminus) {
    TermDeb = terminus;
}

void Voyage::setHeureDeb(string heure) {
    if (heure != "") {
        HeureDeb.tm_hour = atoi(this->split(heure, ':')[0].c_str());
        HeureDeb.tm_min = atoi(this->split(heure, ':')[1].c_str());
    }
}

void Voyage::setHeureFin(string heure) {
    if (heure != "") {
        HeureFin.tm_hour = atoi(this->split(heure, ':')[0].c_str());
        HeureFin.tm_min = atoi(this->split(heure, ':')[1].c_str());
    }
}

void Voyage::setDistance(int dist) {
    distance = dist;
}

string Voyage::getTermDeb() {
    return TermDeb;
}

string Voyage::getTermFin() {
    return TermFin;
}

int Voyage::getDistance() {
    return distance;
}

string Voyage::getName() {
    return name;
}

