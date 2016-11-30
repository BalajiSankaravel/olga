/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Solution.cpp
 * Author: Alex
 * 
 * Created on 30 novembre 2016, 15:29
 */

#include "Solution.h"

Solution::Solution() {
}

Solution::Solution(int nbBus, int TpsTotal, int KmTotal, vector < Bus* > lesBus) {
    this->nbBus = nbBus;
    this->TpsTotal = TpsTotal;
    this->KmTotal = KmTotal;
    this->lesBus = lesBus;
}

string Solution::getText(){
    string text = to_string(nbBus) + "," + to_string(TpsTotal) + "," + to_string(KmTotal) + "\n";
    for (auto elem : lesBus) {
            text += elem->getText() + "\n";
    }
    return text;
    
}

