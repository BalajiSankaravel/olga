/* 
 * File:   Structure.h
 * Author: Flav
 *
 * Created on 26 novembre 2016, 21:33
 */

#ifndef STRUCTURE_H
#define	STRUCTURE_H
#include <string>
#include <vector>

using namespace std;
#ifdef	__cplusplus
extern "C" {
#endif

typedef struct {
    string Nom;
    vector <string> Terminus;
    vector< vector <string> > Horaire;
    vector <int> Distance;
    bool Aller;
} T_UneLigne;



#ifdef	__cplusplus
}
#endif

#endif	/* STRUCTURE_H */

