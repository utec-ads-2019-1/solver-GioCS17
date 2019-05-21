#ifndef OPERATION_H
#define OPERATION_H

#include<string>
#include<stack>
#include<vector>
#include<cmath>
#include<iostream>

using namespace std;

class Operation {
    protected:
        string equation;
        int l,r,ind;
        vector<int> posBrackets;
    public:
        static Operation* buildFromEquation(string equation);

        inline string name() { return equation; }

        virtual float operate() = 0;
};

#endif
