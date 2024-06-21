#include <iostream>
#include "includes/APTED.hpp"
#include "includes/json.hpp"
#include "generator/Tree_generator.hpp"
#include "includes/StringNodeData.hpp"
#include "includes/StringNodeDataa.hpp"


using namespace std;
using json = nlohmann::json;


void test_TreeEditDistance(){
    ifstream testFile("tests/trees.json");

    json tests;
    testFile >> tests;

    for(json test : tests){
        int id = test["ID"];
        string t1 = test["t1"];
        string t2 = test["t2"];


        stringCostModel costModel;
        Apted<StringNodeData> algorithm(&costModel);
        BracketStringParser p1(t1);
        BracketStringParser p2(t2);
        Node<StringNodeData>* n1 = p1.getRoot();
        Node<StringNodeData>* n2 = p2.getRoot();

        float TED = algorithm.computeEditDistance(n1, n2);
        cout << "ID: " << setw(3) << id <<" :: the cost of editing t1 or t2 so that they become the same is: " << TED << endl;

        delete n1;
        delete n2;

    }

}

void test_correctness_test_cases(){
    ifstream testFile("tests/trees.json");

    json tests;
    testFile >> tests;

    for(json test : tests){
        int id             = test["ID"];
        string t1          = test["t1"];
        string t2          = test["t2"];
        float realDistance = test["d" ];


        stringCostModel costModel;
        Apted<StringNodeData> algorithm(&costModel);
        BracketStringParser p1(t1);
        BracketStringParser p2(t2);
        Node<StringNodeData>* n1 = p1.getRoot();
        Node<StringNodeData>* n2 = p2.getRoot();

        float TED = algorithm.computeEditDistance(n1, n2);
        cout << setw(3) << id << " " << TED << " && " << realDistance << ": " << (realDistance == TED ? "✓" : "FAIL") << endl;

        delete n1;
        delete n2;

    }
}


int main() {

    Tree_generator TG;

    TG.generateTree(3,3);

    test_correctness_test_cases();
    test_TreeEditDistance();
    
}