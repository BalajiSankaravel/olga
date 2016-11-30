/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Solution.h
 * Author: Alex
 *
 * Created on 30 novembre 2016, 15:29
 */

#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include "Bus.h"

class Solution {
public:
    Solution();
    Solution(int nbBus, int TpsTotal, int KmTotal, vector < Bus* > lesBus);
    string Solution::getText();
    virtual ~Solution();
private:
    int nbBus;
    int TpsTotal;
    int KmTotal;
    vector < Bus* > lesBus;
};

#endif /* SOLUTION_H */

