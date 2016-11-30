#include "SolutionWriter.h"
#include "Solution.h"
#include <iostream>

void SolutionWriter::write(vector <Solution*> solutions){
    time_t now = time(0);
    char* dt = ctime(&now);
    string filename = "solutiezfezfzefon_";
    filename += dt;
    filename += ".txt";

    cout << solutions.size() << endl;
    
    if ( solutions.size() == 1 ){//// SI UN RESULTATS
        
        string content = this->equipe + "\n";
        
        content += solutions[0]->getText();

        ofstream outfile (filename, std::ofstream::binary);
        if(!outfile) cout << "erreur lol";
            outfile.write (content.c_str(),content.length());
            outfile.close();
            
    }
    else if (solutions.size() > 1){ //// SI PLUSIEURS RESULTATS
        
        string content = this->equipe + "\n";
        
        for (auto elem : solutions) {
            content += elem->getText();
        }
        
        ofstream outfile (filename, std::ofstream::binary);
        if(!outfile) cout << "erreur lol";
            outfile.write (content.c_str(),content.length());
            outfile.close();
        
    }

    
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