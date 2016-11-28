/* 
 * File:   Voyage.h
 * Author: Flav
 *
 * Created on 27 novembre 2016, 15:25
 */

#ifndef VOYAGE_H
#define	VOYAGE_H

#include <string>
#include <vector>
using namespace std;

class Voyage {
public:
    Voyage(string,string,int,string);
    void setTermFin(string);
    void setHeureFin(string);
    void setDistance(int);
    void setTermDeb(string);
    void setHeureDeb(string);
    void split(const string&, char, vector<string> &);
    vector<string> split(const string &, char);
    string getTermDeb();
    string getTermFin();
    int getDistance();
    string getName();
    string TermDeb;
    string TermFin;
    tm HeureDeb;
    tm HeureFin;
    string name;
    int distance;

};

#endif	/* VOYAGE_H */

