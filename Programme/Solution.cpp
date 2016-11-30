#include "Solution.h"
#include <iostream>

Solution::Solution() {
}

Solution::Solution(int nbBus, int TpsTotal, int KmTotal, vector < Bus* >* lesBus) {
    this->nbBus = nbBus;
    this->TpsTotal = TpsTotal;
    this->KmTotal = KmTotal;
    this->lesBus = lesBus;
}

string Solution::getText(){
    string text = to_string(nbBus) + "," + to_string(TpsTotal) + "," + to_string(KmTotal) + "\n";
    for (auto elem : (*lesBus)) {
            text += elem->getText() + "\n";
    }
    return text;
    
}