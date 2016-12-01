#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include "Bus.h"

class Solution {
public:
    Solution();
    Solution(int nbBus, int TpsTotal, int KmTotal, vector < Bus* >* lesBus);
    string getText();
    int nbBus;
    int TpsTotal;
    int KmTotal;
    vector < Bus* >* lesBus;
};

#endif /* SOLUTION_H */

