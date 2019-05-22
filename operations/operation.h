#ifndef OPERATION_H
#define OPERATION_H

#include<string>
#include<stack>
#include<vector>
#include<cmath>
#include<iostream>
#include<unordered_map>

using namespace std;

class Operation {
    protected:
        string equation;
        int l,r,ind;
        vector<int> posBrackets;
        unordered_map<char,float> dict;
    public:
        static Operation* buildFromEquation(string equation);
        static Operation* buildFromEquationWithVariables(string equation,unordered_map<char,float> &dict);
        static vector<int> positionsBrackets(int,string);

        inline string name() { return equation; }

        virtual float operate() = 0;
};

#endif
