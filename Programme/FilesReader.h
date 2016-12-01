/* 
 * File:   FilesReader.h
 * Author: Flav
 *
 * Created on 25 novembre 2016, 11:06
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include "Structure.h"

using namespace std;


#ifndef FILESREADER_H
#define	FILESREADER_H


class FilesReader {
public:
    FilesReader();
    string OpenFile(string);
    int getNombreTerm(string);
    vector < vector<int> > createMatrice(string);
    vector<T_UneLigne> extractHoraire(string);
    vector <string> getIndexMatrice(string);
protected:

};

#endif	/* FILESREADER_H */

