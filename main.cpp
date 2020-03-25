#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map> 
using namespace std;

struct Term {
    string val;
    bool isConstant;
    Term(string value, bool constant) {
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
    Theorem(string n) {
        name = n;
    }
};

void printTerm(Term t) {

}

void printPredicate(Predicate p) {

}

void printLiteral(Literal l) {
    if (!l.isPositive) {
        cout << "-";
    }
    cout << l.pred.name << "(";
    for (int i = 0; i < l.terms.size(); i++) {
        cout << l.terms.at(i).val;
        if (i + 1 < l.terms.size()) { //Is last term
            cout << ",";
        }
    }
    cout << ")";
}

void printClause(Clause c) {
    cout << c.clauseNumber << " ";
    for (int i = 0; i < c.literals.size(); i++) {
        printLiteral(c.literals.at(i));
        cout << " ";
    }
    cout << endl;
}

void printTheorem(Theorem t) {
    cout << "Clause name " << t.name << endl;
    cout << "Start Index " << t.startSolutionIndex << endl;
    cout << "Number of clauses: " << t.clauses.size() << endl;
    for (int i = 0; i < t.clauses.size(); i++) {
        printClause(t.clauses.at(i));
    }
    cout << endl;
}

Theorem constructHowling() {
    Theorem howlingTheorem = Theorem("howling");

    Clause clause1 = Clause(1);
    Literal l1_1 = Literal(Predicate("howl"));
    Literal l1_2 = Literal(Predicate("hound"));
    l1_1.terms.push_back(Term("z",false));
    l1_1.isPositive = true;
    l1_2.terms.push_back(Term("z",false));
    l1_2.isPositive = false;
    clause1.literals.push_back(l1_1);
    clause1.literals.push_back(l1_2);
    howlingTheorem.clauses.push_back(clause1);

    Clause clause2 = Clause(2);
    Literal l2_1 = Literal(Predicate("have"));
    Literal l2_2 = Literal(Predicate("cat"));
    Literal l2_3 = Literal(Predicate("have"));
    Literal l2_4 = Literal(Predicate("mouse"));
    l2_1.isPositive = false;
    l2_1.terms.push_back(Term("x", false));
    l2_1.terms.push_back(Term("y", false));
    l2_2.isPositive = false;
    l2_2.terms.push_back(Term("y", false));
    l2_3.isPositive = false;
    l2_3.terms.push_back(Term("x", false));
    l2_3.terms.push_back(Term("z", false));
    l2_4.isPositive = false;
    l2_4.terms.push_back(Term("z", false));
    clause2.literals.push_back(l2_1);
    clause2.literals.push_back(l2_2);
    clause2.literals.push_back(l2_3);
    clause2.literals.push_back(l2_4);
    howlingTheorem.clauses.push_back(clause2);

    Clause clause3 = Clause(3);
    Literal l3_1 = Literal(Predicate("ls"));
    Literal l3_2 = Literal(Predicate("have"));
    Literal l3_3 = Literal(Predicate("howl"));
    l3_1.isPositive = false;
    l3_1.terms.push_back(Term("w", false));
    l3_2.isPositive = false;
    l3_2.terms.push_back(Term("w", false));
    l3_2.terms.push_back(Term("v", false));
    l3_3.isPositive = false;
    l3_3.terms.push_back(Term("v", false));
    clause3.literals.push_back(l3_1);
    clause3.literals.push_back(l3_2);
    clause3.literals.push_back(l3_3);
    howlingTheorem.clauses.push_back(clause3);
    
    Clause clause4 = Clause(4);
    Literal l4_1 = Literal(Predicate("have"));
    l4_1.isPositive = true;
    l4_1.terms.push_back(Term("john", true));
    l4_1.terms.push_back(Term("a", true));
    clause4.literals.push_back(l4_1);
    howlingTheorem.clauses.push_back(clause4);

    Clause clause5 = Clause(5);
    Literal l5_1 = Literal(Predicate("cat"));
    Literal l5_2 = Literal(Predicate("hound"));
    l5_1.isPositive = true;
    l5_1.terms.push_back(Term("a", true));
    l5_2.isPositive = true;
    l5_2.terms.push_back(Term("a", true));
    clause5.literals.push_back(l5_1);
    clause5.literals.push_back(l5_2);
    howlingTheorem.clauses.push_back(clause5); 

    Clause clause6 = Clause(6);
    Literal l6_1 = Literal(Predicate("mouse"));
    l6_1.isPositive = true;
    l6_1.terms.push_back(Term("b", true));
    clause6.literals.push_back(l6_1);
    howlingTheorem.clauses.push_back(clause6);  

    Clause clause7 = Clause(7);
    Literal l7_1 = Literal(Predicate("ls"));
    l7_1.isPositive = true;
    l7_1.terms.push_back(Term("john", true));
    clause7.literals.push_back(l7_1);
    howlingTheorem.clauses.push_back(clause7);   

    Clause clause8 = Clause(8);
    Literal l8_1 = Literal(Predicate("have"));
    l8_1.isPositive = true;
    l8_1.terms.push_back(Term("john", true));
    l8_1.terms.push_back(Term("b", true));
    clause8.literals.push_back(l8_1);
    howlingTheorem.clauses.push_back(clause8);

    howlingTheorem.startSolutionIndex = 5;

    return howlingTheorem;
}

Theorem constructRR() {

    Theorem rrTheorem = Theorem("rr");

    Clause clause1 = Clause(1);
    Literal l1_1 = Literal(Predicate("rr"));
    Literal l1_2 = Literal(Predicate("coyote"));
    l1_1.isPositive = true;
    l1_1.terms.push_back(Term("a", true));
    l1_2.isPositive = false;
    l1_2.terms.push_back(Term("y", false));
    clause1.literals.push_back(l1_1);
    clause1.literals.push_back(l1_2);
    rrTheorem.clauses.push_back(clause1);

    Clause clause2 = Clause(2);
    Literal l2_1 = Literal(Predicate("chase"));
    Literal l2_2 = Literal(Predicate("coyote"));
    l2_1.isPositive = true;
    l2_1.terms.push_back(Term("z", false));
    l2_1.terms.push_back(Term("a", true));
    l2_2.isPositive = false;
    l2_2.terms.push_back(Term("z", false));
    clause2.literals.push_back(l2_1);
    clause2.literals.push_back(l2_2);
    rrTheorem.clauses.push_back(clause2);

    Clause clause3 = Clause(3);
    Literal l3_1 = Literal(Predicate("smart"));
    Literal l3_2 = Literal(Predicate("rr"));
    Literal l3_3 = Literal(Predicate("beep"));
    l3_1.isPositive = true;
    l3_1.terms.push_back(Term("x", false));
    l3_2.isPositive = false;
    l3_2.terms.push_back(Term("x", false));
    l3_3.isPositive = false;
    l3_3.terms.push_back(Term("x", false));
    clause3.literals.push_back(l3_1);
    clause3.literals.push_back(l3_2);
    clause3.literals.push_back(l3_3);
    rrTheorem.clauses.push_back(clause3);

    return rrTheorem;

}

// Theorem constructCustoms() {

// }

int main(int argc, char** argv) 
{ 
    //Construct theorems
    // unordered_map<string, Theorem> theorems;
    Theorem howlingTheorem = constructHowling();
    Theorem rrTheorem = constructRR();
    // theorems["howling"] = cool;
    // theorems["rr"] = constructRR();
    // theorems["customs"] = constructCustoms();

    // printTheorem(howlingTheorem);
    printTheorem(rrTheorem);

    


    return 0;
}