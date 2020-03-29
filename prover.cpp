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
    Term() {
        val = "";
        isConstant = true;
    }
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
    int d1;
    int d2;
    Clause(int c) {
        clauseNumber = c;
        d1 = -1;
        d2 = -1;
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

struct SingleSubstitution {
    Term origTerm;
    Term newTerm;
    bool isFail;
    SingleSubstitution(Term o, Term n) {
        origTerm = o;
        newTerm = n;
        isFail = false;
    }

    SingleSubstitution() { //For when unify returns fail
        origTerm = Term();
        newTerm = Term();
        isFail = true;
    }
};

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
    if (c.d1 != -1 && c.d2 != -1) {
        cout << " " << c.d1 << "," << c.d2;
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

void printSubstitution(vector<SingleSubstitution> sub) {
    cout << "{";
    for (int i = 0; i < sub.size(); i++) {
        cout << sub.at(i).origTerm.val << "/" << sub.at(i).newTerm.val << ",";
    }
    cout << "}" << endl;
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

    Clause clause4 = Clause(4);
    Literal l4_1 = Literal(Predicate("coyote"));
    Literal l4_2 = Literal(Predicate("rr"));
    Literal l4_3 = Literal(Predicate("catch"));
    Literal l4_4 = Literal(Predicate("smart"));
    l4_1.isPositive = false;
    l4_1.terms.push_back(Term("w", false));
    l4_2.isPositive = false;
    l4_2.terms.push_back(Term("u", false));
    l4_3.isPositive = false;
    l4_3.terms.push_back(Term("w", false));
    l4_3.terms.push_back(Term("u", false));
    l4_4.isPositive = false;
    l4_4.terms.push_back(Term("u", false));
    clause4.literals.push_back(l4_1);
    clause4.literals.push_back(l4_2);
    clause4.literals.push_back(l4_3);
    clause4.literals.push_back(l4_4);
    rrTheorem.clauses.push_back(clause4);

    Clause clause5 = Clause(5);
    Literal l5_1 = Literal(Predicate("frustrated"));
    Literal l5_2 = Literal(Predicate("catch"));
    Literal l5_3 = Literal(Predicate("coyote"));
    Literal l5_4 = Literal(Predicate("rr"));
    Literal l5_5 = Literal(Predicate("chase"));
    l5_1.isPositive = true;
    l5_1.terms.push_back(Term("s", false));
    l5_2.isPositive = true;
    l5_2.terms.push_back(Term("s", false));
    l5_2.terms.push_back(Term("t", false));
    l5_3.isPositive = false;
    l5_3.terms.push_back(Term("s", false));
    l5_4.isPositive = false;
    l5_4.terms.push_back(Term("t", false));
    l5_5.isPositive = false;
    l5_5.terms.push_back(Term("s", false));
    l5_5.terms.push_back(Term("t", false));
    clause5.literals.push_back(l5_1);
    clause5.literals.push_back(l5_2);
    clause5.literals.push_back(l5_3);
    clause5.literals.push_back(l5_4);
    clause5.literals.push_back(l5_5);
    rrTheorem.clauses.push_back(clause5);

    Clause clause6 = Clause(6);
    Literal l6_1 = Literal(Predicate("beep"));
    Literal l6_2 = Literal(Predicate("rr"));
    l6_1.isPositive = true;
    l6_1.terms.push_back(Term("r", false));
    l6_2.isPositive = false;
    l6_2.terms.push_back(Term("r", false));
    clause6.literals.push_back(l6_1);
    clause6.literals.push_back(l6_2);
    rrTheorem.clauses.push_back(clause6);

    Clause clause7 = Clause(7);
    Literal l7_1 = Literal(Predicate("coyote"));
    l7_1.isPositive = true;
    l7_1.terms.push_back(Term("b", true));
    clause7.literals.push_back(l7_1);
    rrTheorem.clauses.push_back(clause7);

    Clause clause8 = Clause(8);
    Literal l8_1 = Literal(Predicate("frustrated"));
    l8_1.isPositive = false;
    l8_1.terms.push_back(Term("b", true));
    clause8.literals.push_back(l8_1);
    rrTheorem.clauses.push_back(clause8);

    rrTheorem.startSolutionIndex = 6;

    return rrTheorem;
}

Theorem constructCustoms() {
    Theorem customsTheorem = Theorem("customs");

    Clause clause1 = Clause(1);
    Literal l1_1 = Literal(Predicate("v"));
    Literal l1_2 = Literal(Predicate("s"));
    Literal l1_3 = Literal(Predicate("e"));
    l1_1.isPositive = true;
    l1_1.terms.push_back(Term("x", false));
    l1_2.isPositive = true;
    l1_2.terms.push_back(Term("x", false));
    l1_2.terms.push_back(Term("f(x)", false));
    l1_3.isPositive = false;
    l1_3.terms.push_back(Term("x", false));
    clause1.literals.push_back(l1_1);
    clause1.literals.push_back(l1_2);
    clause1.literals.push_back(l1_3);
    customsTheorem.clauses.push_back(clause1);

    Clause clause2 = Clause(2);
    Literal l2_1 = Literal(Predicate("v"));
    Literal l2_2 = Literal(Predicate("c"));
    Literal l2_3 = Literal(Predicate("e"));
    l2_1.isPositive = true;
    l2_1.terms.push_back(Term("y", false));
    l2_2.isPositive = true;
    l2_2.terms.push_back(Term("f(y)", false));
    l2_3.isPositive = false;
    l2_3.terms.push_back(Term("y", false));
    clause2.literals.push_back(l2_1);
    clause2.literals.push_back(l2_2);
    clause2.literals.push_back(l2_3);
    customsTheorem.clauses.push_back(clause2);

    Clause clause3 = Clause(3);
    Literal l3_1 = Literal(Predicate("e"));
    l3_1.isPositive = true;
    l3_1.terms.push_back(Term("a", true));
    clause3.literals.push_back(l3_1);
    customsTheorem.clauses.push_back(clause3);

    Clause clause4 = Clause(4);
    Literal l4_1 = Literal(Predicate("d"));
    l4_1.isPositive = true;
    l4_1.terms.push_back(Term("a", true));
    clause4.literals.push_back(l4_1);
    customsTheorem.clauses.push_back(clause4);

    Clause clause5 = Clause(5);
    Literal l5_1 = Literal(Predicate("d"));
    Literal l5_2 = Literal(Predicate("s"));
    l5_1.isPositive = true;
    l5_1.terms.push_back(Term("z", false));
    l5_2.isPositive = false;
    l5_2.terms.push_back(Term("a", true));
    l5_2.terms.push_back(Term("z", false));
    clause5.literals.push_back(l5_1);
    clause5.literals.push_back(l5_2);
    customsTheorem.clauses.push_back(clause5);

    Clause clause6 = Clause(6);
    Literal l6_1 = Literal(Predicate("d"));
    Literal l6_2 = Literal(Predicate("v"));
    l6_1.isPositive = false;
    l6_1.terms.push_back(Term("w", false));
    l6_2.isPositive = false;
    l6_2.terms.push_back(Term("w", true));
    clause6.literals.push_back(l6_1);
    clause6.literals.push_back(l6_2);
    customsTheorem.clauses.push_back(clause6);

    Clause clause7 = Clause(7);
    Literal l7_1 = Literal(Predicate("d"));
    Literal l7_2 = Literal(Predicate("c"));
    l7_1.isPositive = false;
    l7_1.terms.push_back(Term("r", false));
    l7_2.isPositive = false;
    l7_2.terms.push_back(Term("r", true));
    clause7.literals.push_back(l7_1);
    clause7.literals.push_back(l7_2);
    customsTheorem.clauses.push_back(clause7);

    customsTheorem.startSolutionIndex = 6;

    return customsTheorem;
}

Theorem constructHarmonia() {
    Theorem harmoniaTheorem = Theorem("harmonia");

    Clause clause1 = Clause(1);
    Literal l1_1 = Literal(Predicate("Parent"));
    Literal l1_2 = Literal(Predicate("Parent"));
    Literal l1_3 = Literal(Predicate("Grandparent"));
    l1_1.isPositive = true;
    l1_2.isPositive = true;
    l1_3.isPositive = false;
    l1_1.terms.push_back(Term("x", false));
    l1_1.terms.push_back(Term("z", false));
    l1_2.terms.push_back(Term("z", false));
    l1_2.terms.push_back(Term("y", false));
    l1_3.terms.push_back(Term("x", false));
    l1_3.terms.push_back(Term("y", false));
    clause1.literals.push_back(l1_1);
    clause1.literals.push_back(l1_2);
    clause1.literals.push_back(l1_3);
    harmoniaTheorem.clauses.push_back(clause1);

    Clause clause2 = Clause(2);
    Literal l2_1 = Literal(Predicate("Mother"));
    Literal l2_2 = Literal(Predicate("Parent"));
    l2_1.isPositive = true;
    l2_2.isPositive = false;
    l2_1.terms.push_back(Term("w", false));
    l2_1.terms.push_back(Term("u", false));
    l2_2.terms.push_back(Term("w", false));
    l2_2.terms.push_back(Term("u", false));
    clause2.literals.push_back(l2_1);
    clause2.literals.push_back(l2_2);
    harmoniaTheorem.clauses.push_back(clause2);

    Clause clause3 = Clause(3);
    Literal l3_1 = Literal(Predicate("Father"));
    Literal l3_2 = Literal(Predicate("Parent"));
    l3_1.isPositive = true;
    l3_2.isPositive = false;
    l3_1.terms.push_back(Term("w", false));
    l3_1.terms.push_back(Term("u", false));
    l3_2.terms.push_back(Term("w", false));
    l3_2.terms.push_back(Term("u", false));
    clause3.literals.push_back(l3_1);
    clause3.literals.push_back(l3_2);
    harmoniaTheorem.clauses.push_back(clause3);

    Clause clause4 = Clause(4);
    Literal l4_1 = Literal(Predicate("Father"));
    l4_1.isPositive = true;
    l4_1.terms.push_back(Term("Zeus", true));
    l4_1.terms.push_back(Term("Ares", true));
    clause4.literals.push_back(l4_1);
    harmoniaTheorem.clauses.push_back(clause4);

    Clause clause5 = Clause(5);
    Literal l5_1 = Literal(Predicate("Mother"));
    l5_1.isPositive = true;
    l5_1.terms.push_back(Term("Hera", true));
    l5_1.terms.push_back(Term("Ares", true));
    clause5.literals.push_back(l5_1);
    harmoniaTheorem.clauses.push_back(clause5);

    Clause clause6 = Clause(6);
    Literal l6_1 = Literal(Predicate("Father"));
    l6_1.isPositive = true;
    l6_1.terms.push_back(Term("Ares", true));
    l6_1.terms.push_back(Term("Harmonia", true));
    clause6.literals.push_back(l6_1);
    harmoniaTheorem.clauses.push_back(clause6);

    Clause clause7 = Clause(7);
    Literal l7_1 = Literal(Predicate("Grandparent"));
    l7_1.isPositive = true;
    l7_1.terms.push_back(Term("Zeus", true));
    l7_1.terms.push_back(Term("Harmonia", true));
    clause7.literals.push_back(l7_1);
    harmoniaTheorem.clauses.push_back(clause7);

    harmoniaTheorem.startSolutionIndex = 3;

    return harmoniaTheorem;
}

Theorem constructCustom() {
    Theorem customTheorem = Theorem("custom");

    Clause clause1 = Clause(1);
    Literal l1_1 = Literal(Predicate("S"));
    Literal l1_2 = Literal(Predicate("P"));
    l1_1.isPositive = true;
    l1_2.isPositive = true;
    l1_1.terms.push_back(Term("x", false));
    l1_2.terms.push_back(Term("x", false));
    clause1.literals.push_back(l1_1);
    clause1.literals.push_back(l1_2);
    customTheorem.clauses.push_back(clause1);

    Clause clause2 = Clause(2);
    Literal l2_1 = Literal(Predicate("S"));
    Literal l2_2 = Literal(Predicate("R"));
    l1_1.isPositive = false;
    l1_2.isPositive = false;
    l1_1.terms.push_back(Term("x", false));
    l1_2.terms.push_back(Term("x", false));
    clause1.literals.push_back(l1_1);
    clause1.literals.push_back(l1_2);
    customTheorem.clauses.push_back(clause1);
}

bool equalLiterals(Literal l1, Literal l2) {
    if (l1.pred.name != l2.pred.name) {
        return false;
    }

    if (l1.terms.size() != l2.terms.size()) {
        return false;
    }

    if (l1.isPositive != l2.isPositive) {
        return false;
    }

    for (int i = 0; i < l1.terms.size(); i++) {
        if (l1.terms.at(i).val != l2.terms.at(i).val) {
            return false;
        }
    }

    return true;
}

bool complementaryLiterals(Literal l1, Literal l2) {

    if (l1.pred.name != l2.pred.name) {
        return false;
    }

    if (l1.terms.size() != l2.terms.size()) {
        return false;
    }

    if (l1.isPositive == l2.isPositive) {
        return false;
    }

    for (int i = 0; i < l1.terms.size(); i++) {
        if (l1.terms.at(i).val != l2.terms.at(i).val) {
            return false;
        }
    }

    return true;
}

Clause resolve(Clause c1, Clause c2, vector<SingleSubstitution> sub) {
    cout << "Resolving" << endl;
    printClause(c1);
    printClause(c2);
    printSubstitution(sub);

    //Combine clauses into one clause
    vector<Literal> c1Literals = c1.literals;
    vector<Literal> newLiterals;
    c1Literals.insert(c1Literals.end(), c2.literals.begin(), c2.literals.end());
    newLiterals = c1Literals;

    //Apply substitution
    if (!sub.empty()) {
        for (int i = 0; i < newLiterals.size(); i++) {
            for (int j = 0; j < newLiterals.at(i).terms.size(); j++) {
                for (int k = 0; k < sub.size(); k ++) {
                    size_t found = newLiterals.at(i).terms.at(j).val.find(sub.at(k).origTerm.val);
                    if (found != string::npos) {
                        if (newLiterals.at(i).terms.at(j).val == sub.at(k).origTerm.val) {
                            newLiterals.at(i).terms.at(j) = sub.at(k).newTerm;
                        } else {
                            string newNewTerm = newLiterals.at(i).terms.at(j).val.substr(0, found) + sub.at(k).newTerm.val + newLiterals.at(i).terms.at(j).val.substr(found + sub.at(k).origTerm.val.length());
                            newLiterals.at(i).terms.at(j).val = newNewTerm;
                            newLiterals.at(i).terms.at(j).isConstant = sub.at(k).newTerm.isConstant;
                        }
                    }
                }
            }
        }
    }
    
    Clause newClause = Clause(-1);
    newClause.literals = newLiterals;

    cout << "Applied Substitution on new Clause" << endl;
    printClause(newClause);


    //Take out complimentary literals
    for (int i = 0; i < newClause.literals.size() - 1; i++) {
        bool remove = false;
        for (int j = i + 1; j < newClause.literals.size(); j++) {
            if (complementaryLiterals(newClause.literals.at(i), newClause.literals.at(j))) {
                //Remove both
                cout << "removing literal: " << j << endl;
                newClause.literals.erase(newClause.literals.begin()+j);
                j--;
                remove = true;
            // }
            } else if (equalLiterals(newClause.literals.at(i), newClause.literals.at(j))) {
                //remove second occurance
                cout << "removing literal: " << j << endl;
                newClause.literals.erase(newClause.literals.begin()+j);
                j--;
            }
        }
        if (remove) {
            //remove literal at i
            cout << "removing literal: " << i << endl;
            newClause.literals.erase(newClause.literals.begin()+i);
            i--;
        }
    }


    cout << "Removed Complimentary Literals" << endl;
    printClause(newClause);
    return newClause;
}

bool valOccursInTerm(string val, string Term) {
    if (Term.find(val) != string::npos) {
        //.. found.
        return true;
    } else {
        return false;
    }
}

vector<SingleSubstitution> composition(vector<SingleSubstitution> s1, vector<SingleSubstitution> s2) {

    cout << "Composition" << endl;
    printSubstitution(s1);
    printSubstitution(s2);

    //Apply s2 to each s1
    for (int i = 0; i < s1.size(); i++) {
        for (int j = 0; j < s2.size(); j++) {
            if (valOccursInTerm(s2.at(j).origTerm.val, s1.at(i).newTerm.val)) {
                //Update s1.at(i).newTerm
                if (s2.at(j).origTerm.val.length() == s1.at(i).newTerm.val.length()) {
                    s1.at(i).newTerm = s2.at(j).newTerm;
                } else { //s1 newTerm contains s2 origTerm as a substring
                    //Find s2 origTerm in s1 newTerm and replace with s2 newTerm
                    size_t found = s1.at(i).newTerm.val.find(s2.at(j).origTerm.val);
                    if (found != string::npos) {
                        string newNewTerm = s1.at(i).newTerm.val.substr(0, found) + s2.at(j).newTerm.val + s1.at(i).newTerm.val.substr(found + s2.at(j).origTerm.val.length());
                        s1.at(i).newTerm.val = newNewTerm;
                    }
                }
            }
        }
    }

    cout << "applied s2 to s1" << endl;
    printSubstitution(s1);
    printSubstitution(s2);

    //Combine s1 and s2
    s1.insert( s1.end(), s2.begin(), s2.end() );

    //Remove identity and duplicate origTerms
    for (int i = 0; i < s1.size() - 1; i++) {
        for (int j = i + 1; j < s1.size(); j++) {
            if (s1.at(i).origTerm.val == s1.at(j).origTerm.val) {
                //Remove element at j
                s1.erase(s1.begin()+j);
                j--;
            }
        }
    }

    for (int i = 0; i < s1.size(); i++) {
        if (s1.at(i).origTerm.val == s1.at(i).newTerm.val) {
            s1.erase(s1.begin()+i);
            i--;
        }
    }

    cout << "Returning composition" << endl;
    printSubstitution(s1);
    return s1;
}

vector<SingleSubstitution> unifyTerms(vector<Term> e1, vector<Term> e2) {

    vector<SingleSubstitution> substitution;
    SingleSubstitution failSub = SingleSubstitution();

    if (e1.size() <= 0 || e2.size() <= 0) {
        cout << "Unify Fail due to expression sizes being zero" << endl;
        substitution.push_back(failSub);
        return substitution;
    } else if (e1.size() <= 1 && e2.size() <= 1) {
        if (e1.at(0).isConstant && e2.at(0).isConstant) { //Case 1 Both are constants
            cout << "Case 1" << endl;
            if (e1.at(0).val == e2.at(0).val) {
                return substitution; //Return empty sub
            } else {
                cout << "Fail" << endl;
                substitution.push_back(failSub);
                return substitution;
            }
        } else if (!e1.at(0).isConstant) { //Case 2 If e1 is a variable
            cout << "Case 2" << endl;
            if (valOccursInTerm(e1.at(0).val, e2.at(0).val)) {
                cout << "Fail" << endl;
                substitution.push_back(failSub);
                return substitution;
            } else {
                SingleSubstitution newSub = SingleSubstitution(e1.at(0), e2.at(0));
                substitution.push_back(newSub);
                return substitution;
            }
        } else if (!e2.at(0).isConstant) { //Case 3 If e2 is a variable
            cout << "Case 3" << endl;
            if (valOccursInTerm(e2.at(0).val, e1.at(0).val)) {
                cout << "Fail" << endl;
                substitution.push_back(failSub);
                return substitution;
            } else {
                SingleSubstitution newSub = SingleSubstitution(e2.at(0), e1.at(0));
                substitution.push_back(newSub);
                return substitution;
            }
        }
    } else { //Case 4 Not a single term
        //Get first element of each 
        cout << "Case 4" << endl;
        vector<Term> he1;
        he1.push_back(e1.at(0));
        vector<Term> he2;
        he2.push_back(e2.at(0));

        //Get unification of first two terms
        vector<SingleSubstitution> sub1 = unifyTerms(he1, he2);

        if (!sub1.empty() && sub1.at(0).isFail) { //If sub is fail return fail
            cout << "Fail" << endl;
            return sub1;
        }

        //Get tails
        vector<Term> t1;
        for (int i = 1; i < e1.size(); i++) {
            t1.push_back(e1.at(i));
        }
        vector<Term> t2;
        for (int i = 1; i < e2.size(); i++) {
            t2.push_back(e2.at(i));
        }

        //Get unification of tails
        vector<SingleSubstitution> sub2 = unifyTerms(t1,t2);

        if (!sub2.empty() && sub2.at(0).isFail) { //If sub is fail return fail
            cout << "Fail" << endl;
            return sub2;
        }

        if (sub1.empty() && sub2.empty()) {
            return sub1;
        }

        return composition(sub1,sub2);
    }

    return substitution;
    
}

vector<SingleSubstitution> unify(Literal l1, Literal l2) {
    cout << "Attempting to unify ";
    printLiteral(l1);
    cout << ", ";
    printLiteral(l2);
    cout << endl;

    vector<SingleSubstitution> substitution;
    SingleSubstitution failSub = SingleSubstitution();

    if (l1.pred.name != l2.pred.name) {
        cout << "Fail: Pred names don't match" << endl;
        substitution.push_back(failSub); 
        return substitution;
    }

    if (l1.terms.size() != l2.terms.size()) {
        cout << "Fail: term sizes don't match" << endl;
        substitution.push_back(failSub);
        return substitution;
    }

    substitution = unifyTerms(l1.terms, l2.terms);

    return substitution;
}

bool literalsAreEqual(Literal l1, Literal l2) {
    if (l1.pred.name != l2.pred.name) {
        return false;
    }

    if (l1.terms.size() != l2.terms.size()) {
        return false;
    }

    if ((l1.isPositive && !l2.isPositive) || (!l1.isPositive && l2.isPositive)) { 
        return false;
    }

    for (int i = 0; i < l1.terms.size(); i++) {

        if (l1.terms.at(i).val != l2.terms.at(i).val) {
            if (l1.terms.at(i).isConstant || l2.terms.at(i).isConstant) {
                return false;
            }
        }
    }

    return true;
}

bool clausesAreEqual(Clause c1, Clause c2) {
    //For each literal in c1 there must be a matching literal in c2

    if (c1.literals.size() != c2.literals.size()) {
        return false;
    }

    for (int i = 0; i < c1.literals.size(); i++) {
        bool found = false;
        for (int j = 0; j < c2.literals.size(); j++) {
            if (literalsAreEqual(c1.literals.at(i), c2.literals.at(j))) {
                found = true;
            }
        }
        if (!found) {
            return false;
        }
    }

    return true;
}

// bool clausesAreEqual(Clause c1, Clause c2) {
//     // cout << "Checking if clauses are equal" << endl;
//     // printClause(c1);
//     // printClause(c2);
    

//     if (c1.literals.size() != c2.literals.size()) {
//         return false;
//     }

//     for (int i = 0; i < c1.literals.size(); i++) { //For each pair of literals

//         if (c1.literals.at(i).pred.name == c2.literals.at(i).pred.name) { //If pred names match

//             if (c1.literals.at(i).terms.size() == c2.literals.at(i).terms.size()) { //If the literal sizes match

//                 for (int j = 0; j < c1.literals.at(i).terms.size(); j++) { //for each term

//                     if (c1.literals.at(i).terms.at(j).isConstant && c2.literals.at(i).terms.at(j).isConstant) {
//                         if (c1.literals.at(i).terms.at(j).val != c2.literals.at(i).terms.at(j).val) {
//                             cout << "Not equal. both are constants but not equal" << endl;
//                             return false;
//                         }
//                     } else if ((c1.literals.at(i).terms.at(j).isConstant && !c2.literals.at(i).terms.at(j).isConstant) || (!c1.literals.at(i).terms.at(j).isConstant && c2.literals.at(i).terms.at(j).isConstant)) { //if one is a variable and the other isn't
//                             cout << "Not equal. One is constant and the other is not " <<  c1.literals.at(i).terms.at(j).isConstant << c2.literals.at(i).terms.at(j).isConstant << endl;
//                             return false;
//                     } else {
//                         cout << "both are variables" << endl;
//                     }
//                 }
//             } else {
//                 return false;
//             }

//         } else {
//             // cout << "Not equal" << endl;
//             return false;
//         }
//     }

//     // cout << "Equal!" << endl;
//     return true;
// }

bool clauseAlreadyExists(Clause newClause, vector<Clause> existingClauses) {
    cout << "Checking for duplicates: " << endl;
    printClause(newClause); 
    for (int i = 0; i < existingClauses.size(); i++) {
        if (clausesAreEqual(newClause, existingClauses.at(i))) {
            cout << "Already exists at " << i << endl;
            return true;
        }
    }
    cout << "Doesn't exist yet!" << endl;
    return false;
}

void printAllSingleLiteralClauses(Theorem t) {
    for (int i = 0; i < t.clauses.size(); i++) {
        if (t.clauses.at(i).literals.size() <= 1) {
            printClause(t.clauses.at(i));
        }
    }
}

void solveTheorem(Theorem theorem) {
    //Set pointers
    //While 

    cout << "Solving: " << theorem.name << endl;
    printTheorem(theorem);

    int innerLoopIndex = 0;
    int outerLoopIndex = theorem.startSolutionIndex;

    bool keepRunning = true;

    while (outerLoopIndex < theorem.clauses.size()) {
        cout << "Inner Loop Index: " << innerLoopIndex << endl;
        cout << "Outer Loop Index: " << outerLoopIndex << endl;
        cout << "Num clauses: " << theorem.clauses.size() << endl;

        if (innerLoopIndex == 10 && outerLoopIndex == 1036) {
            printTheorem(theorem);
            printAllSingleLiteralClauses(theorem);
            int c;
            cin >> c;
        }
        if (theorem.clauses.size() % 100 == 0) {
            printTheorem(theorem);
            printAllSingleLiteralClauses(theorem);
            int d;
            cin >> d;
        }

        //Find all unifiable pairs of literals
        //For each pair of literals, resolve the clauses and add to newClause to theorem clauses
        Clause innerClause = theorem.clauses.at(innerLoopIndex);
        Clause outerClause = theorem.clauses.at(outerLoopIndex);
        printClause(innerClause);
        printClause(outerClause);

        for (int i = 0; i < outerClause.literals.size(); i++) {
            for (int j = 0; j < innerClause.literals.size(); j++) {
                vector<SingleSubstitution> sub = unify(outerClause.literals.at(i), innerClause.literals.at(j));
                if (!sub.empty() && sub.at(0).isFail != true) { //Unifiable
                    cout << "Unifiable!" << endl;
                    printSubstitution(sub);

                    Clause newClause = resolve(outerClause, innerClause, sub);
                    cout << "New Clause" << endl;
                    printClause(newClause);

                    if (newClause.literals.empty()) {
                        cout << "SOLVED!!!" << endl;
                        printTheorem(theorem);
                        return;
                    }

                    if (!clauseAlreadyExists(newClause, theorem.clauses)) { //Clause doesn't already exist
                        cout << "Adding clause to theorem" << endl;
                        newClause.clauseNumber = theorem.clauses.size() + 1;
                        newClause.d1 = innerLoopIndex + 1;
                        newClause.d2 = outerLoopIndex + 1;
                        theorem.clauses.push_back(newClause);
                        printTheorem(theorem);
                        if (innerLoopIndex == 10 && outerLoopIndex == 1036) {
                            int d;
                            cin >> d;
                        }

                    } else {
                        cout << "Duplicate. No new clause added" << endl;
                        if (innerLoopIndex == 10 && outerLoopIndex == 1036) {
                            int d;
                            cin >> d;
                        }
                    }       
                } else if (sub.empty()) {
                    cout << "Unifiable!" << endl;
                    printSubstitution(sub);

                    Clause newClause = resolve(outerClause, innerClause, sub);
                    cout << "New Clause" << endl;
                    printClause(newClause);

                    if (newClause.literals.empty()) {
                        cout << "SOLVED!!!" << endl;
                        printTheorem(theorem);
                        return;
                    }

                    if (!clauseAlreadyExists(newClause, theorem.clauses)) { //Clause doesn't already exist
                        cout << "Adding clause to theorem" << endl;
                        newClause.clauseNumber = theorem.clauses.size() + 1;
                        newClause.d1 = innerLoopIndex + 1;
                        newClause.d2 = outerLoopIndex + 1;
                        theorem.clauses.push_back(newClause);
                        printTheorem(theorem);
                        cout << "Derived from clauses " << innerLoopIndex + 1 << " and " << outerLoopIndex + 1 << endl;
                        if (innerLoopIndex == 10 && outerLoopIndex == 1036) {
                            int d;
                            cin >> d;
                        }

                    } else {
                        cout << "Duplicate. No new clause added" << endl;
                        if (innerLoopIndex == 10 && outerLoopIndex == 1036) {
                            int d;
                            cin >> d;
                        }
                    }  

                } else {
                    cout << "Not unifiable" << endl;
                    if (innerLoopIndex == 10 && outerLoopIndex == 1036) {
                        int d;
                        cin >> d;
                    }
                }
                cout << endl << endl << endl;
            }
        }

        innerLoopIndex++;
        if (innerLoopIndex == outerLoopIndex) {
            innerLoopIndex = 0;
            outerLoopIndex++;
        }
    }

    cout << "Not solvable" << endl;
}

int main(int argc, char** argv) 
{ 
    Theorem howlingTheorem = constructHowling();
    Theorem rrTheorem = constructRR();
    Theorem customsTheorem = constructCustoms();
    Theorem harmoniaTheorem = constructHarmonia();

    if (argc < 3) { return 0; }
    vector<string> inputs;
    for (int i = 1; i < argc; ++i) { 
        istringstream ss(argv[i]);
        string x;
        if (!(ss >> x)) {
            std::cerr << "Invalid number: " << argv[1] << '\n';
        } else if (!ss.eof()) {
            std::cerr << "Trailing characters after number: " << argv[1] << '\n';
        } else {
            inputs.push_back(x);
        }
    }

    if (inputs.at(0) == "howling") {
        solveTheorem(howlingTheorem);
    } else if (inputs.at(0) == "rr") {
        solveTheorem(rrTheorem);
    } else if (inputs.at(0) == "customs") {
        solveTheorem(customsTheorem);
    } else if (inputs.at(0) == "harmonia") {
        solveTheorem(harmoniaTheorem);
    } else {
        cout << "No theorem to solve" << endl;
    }

    


    return 0;
}