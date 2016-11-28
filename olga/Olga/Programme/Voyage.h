/* 
 * File:   Voyage.h
 * Author: Flav
 *
 * Created on 27 novembre 2016, 15:25
 */

#include <string>
using namespace std;
#ifndef VOYAGE_H
#define	VOYAGE_H


class Voyage {
public:
    Voyage(string,string,int);
    void setTermFin(string);
    void setHeureFin(string);
    void setDistance(int);
    void setTermDeb(string);
    void setHeureDeb(string);
    string getTermDeb();
    string getHeureDeb();
    string getTermFin();
    string getHeureFin();
    int getDistance();
    
protected:
    string TermDeb;
    string TermFin;
    string HeureDeb;
    string HeureFin;
    int distance;

};

#endif	/* VOYAGE_H */

