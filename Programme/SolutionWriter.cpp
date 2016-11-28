/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SolutionWriter.cpp
 * Author: Alex
 * 
 * Created on 28 novembre 2016, 09:07
 */

#include "SolutionWriter.h"

SolutionWriter::SolutionWriter() {
}

SolutionWriter::SolutionWriter(int NbBus, double dureeTotal, double KmTotal) {
    this->NbBus = NbBus;
    this->dureeTotal = dureeTotal;
    this->KmTotal = KmTotal;
}

SolutionWriter::write(vector <Bus*> lesBus){
    time_t now = time(0);
    char* dt = ctime(&now);
    string filename = "solution_" + dt + ".txt";

    string content = 
            this->equipe + "\r" + 
            this->NbBus + "," + this->dureeTotal + "," + this->KmTotal + "\r";
    
    for (Bus elem : lesBus) {
        content += elem.getText() + "\n";
    }
    
    ofstream outfile (filename, std::ofstream::binary);
    outfile.write (content,content.length());
    outfile.close();
}

SolutionWriter::~SolutionWriter() {
}

/*
    # Antoine Eon, Flavien Berard, Thibaut Curbera, Jeremie Gidenne, Alexandre Bizien
    NbBus,duréeTotal,KmTotal
    busi,depot,numeroLigne:aller/retour:numeroVoyage,numeroLigne:aller/retour:numeroVoyage,.... 
    bus1,3,l2:a:v1,l2:r:v3,l1:r:v1,. . .
    bus2,1,l2:r:v1,l2:a:v2,l1:r:v2,. . .
    bus3,3,l3:a:v1,l4:a:v2,l3:a:v3,. . .
    bus4,2,l4:r:v2,l3:r:v1,l4:r:v
*/