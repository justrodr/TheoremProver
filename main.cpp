#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map> 
using namespace std;

struct Term {
    char val;
    bool isConstant;
    Term(char value, bool constant) {
      val = value;
      isConstant = constant;
    };
};

struct Predicate {
    string name;
    Predicate(string n) {
        name = n;
    }
    Predicate() {
        name = "-1";
    }
};

struct Literal {
    Predicate pred;
    vector<Term> terms; //order matters
    bool isPositive;
    Literal(Predicate p, vector<Term> t, bool pos) {
        pred = p;
        terms = t;
        isPositive = pos;
    }
    Literal(Predicate p) {
        pred = p;
        vector<Term> t;
        terms = t;
        isPositive = true;
    }
};

struct Clause {
    vector<Literal> literals;
    int clauseNumber;
    Clause(int c) {
        clauseNumber = c;
    }
};

struct Theorem {
    vector<Clause> clauses;
    int startSolutionIndex;
    string name;
};

Theorem constructHowling() {
    
}

Theorem constructRR() {

}

Theorem constructCustoms() {

}

int main(int argc, char** argv) 
{ 
    //Construct theorems
    unordered_map<string, Theorem> theorems;
    theorems["howling"] = constructHowling();
    theorems["rr"] = constructRR();
    theorems["customs"] = constructCustoms();

    


    return 0;
}