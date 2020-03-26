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

struct SingleSubstitution {
    Term origTerm;
    Term newTerm;
    SingleSubstitution(Term o, Term n) {
        origTerm = o;
        newTerm = n;
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

    return customsTheorem;
}

Clause resolve(Clause c1, Clause c2) {
    cout << "Resolving" << endl;
    return c1;
}

vector<SingleSubstitution> unify(Clause c1, Clause c2) {
    cout << "unifying clause " << c1.clauseNumber << " and clause " << c2.clauseNumber << endl;
    vector<SingleSubstitution> subsitution;
    return subsitution;
}

bool clausesAreEqual(Clause c1, Clause c2) {
    cout << "Checking if clauses are equal" << endl;
    printClause(c1);
    printClause(c2);
    

    if (c1.literals.size() != c2.literals.size()) {
        return false;
    }

    for (int i = 0; i < c1.literals.size(); i++) {
        if (c1.literals.at(i).pred.name == c2.literals.at(i).pred.name) {
            for (int j = 0; j < c1.literals.at(i).terms.size(); j++) {
                if (c1.literals.at(i).terms.at(j).val == c2.literals.at(i).terms.at(j).val) {
                    if (c1.literals.at(i).terms.at(j).isConstant || c2.literals.at(i).terms.at(j).isConstant) {
                        cout << "Not equal" << endl;
                        return false;
                    }
                }
            }
        } else {
            cout << "Not equal" << endl;
            return false;
        }
    }

    cout << "Equal!" << endl;
    return true;
}

bool clauseAlreadyExists(Clause newClause, vector<Clause> existingClauses) {
    cout << "Checking for duplicates: " << endl;
    printClause(newClause); 
    for (int i=0; i < existingClauses.size(); i++) {
        if (clausesAreEqual(newClause, existingClauses.at(i))) {
            cout << "Already exists" << endl;
            return true;
        }
    }
    cout << "Doesn't exist yet!" << endl;
    return false;
}

void solveTheorem(Theorem theorem) {
    //Set pointers
    //While 

    cout << "Solving: " << theorem.name << endl;

    int innerLoopIndex = 0;
    int outerLoopIndex = theorem.startSolutionIndex;

    while (outerLoopIndex < theorem.clauses.size()) {
        cout << "Inner Loop Index: " << innerLoopIndex << endl;
        cout << "Outer Loop Index: " << outerLoopIndex << endl;
        cout << "Num clauses: " << theorem.clauses.size() << endl;

        vector<SingleSubstitution> substitution = unify(theorem.clauses.at(innerLoopIndex), theorem.clauses.at(outerLoopIndex));
        if (!substitution.empty()) {
            Clause newClause = resolve(theorem.clauses.at(innerLoopIndex), theorem.clauses.at(innerLoopIndex));
            if (!clauseAlreadyExists(newClause, theorem.clauses)) {
                cout << "Adding clause to theorem" << endl;
                theorem.clauses.push_back(newClause);
                printTheorem(theorem);
            } else {
                cout << "Duplicate. No new clause added" << endl;
            }
            
        } else {
            cout << "Substitution is empty. No new clause added" << endl;
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
    } else {
        cout << "No theorem to solve" << endl;
    }

    


    return 0;
}