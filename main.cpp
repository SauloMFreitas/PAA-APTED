/**
 * @file main.cpp
 * @author Bernardo Marques
 * @author Bruno Santiago
 * @author Fabio Freire
 * @author Marcos Antônio Lommez
 * @author Saulo de Moura
 * @date 2024-06-22
 * 
 * Algoritmo original retirado de:
 * <p>See the source code para mais comentários relacionados ao algoritmo.
 *
 * <p>Referências:
 * <ul>
 * <li>[1] M. Pawlik e N. Augsten. Efficient Computation of the Tree Edit
 *      Distance. ACM Transactions on Database Systems (TODS) 40(1). 2015.
 * <li>[2] M. Pawlik e N. Augsten. Tree edit distance: Robust and memory-
 *      efficient. Information Systems 56. 2016.
 * </ul>
 * 
 * Algoritmo Original retirado de: https://github.com/DatabaseGroup/apted.git
 * Algoritmo traduzido retirado de: https://github.com/Trinovantes/capted.git
 * 
 * Algumas funções foram alteradas do algoritmo original ou traduzido para melhor compreensão do grupo.
 */
#include "MemoryAccessTracker.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <vector>
#include "includes/json.hpp"
#include "APTED/lib/Capted.h"
#include "ZHSH/forest_dist.hpp"
#include "generator/Tree_generator.hpp"
#include <sys/resource.h>

using namespace capted;
using std::cout;
using std::endl;
using std::string;
using json = nlohmann::json;



NodeZHSH* buildTree(const std::string& str, size_t& pos) {
    if (pos >= str.size()) return nullptr;

    if (str[pos] == '{') {
        ++pos;
    }

    std::string label;
    while (pos < str.size() && str[pos] != '{' && str[pos] != '}') {
        label += str[pos];
        ++pos;
    }

    NodeZHSH* root = new NodeZHSH(label);

    while (pos < str.size() && str[pos] != '}') {
        root->children.push_back(buildTree(str, pos));
    }

    if (pos < str.size() && str[pos] == '}') {
        ++pos;
    }

    return root;
}

/**
 * @brief cria e realiza os testes de TED para APTED
 * 
 * @param numNodes - quantidade de nós a serem gerados nas árvores
 * @param numTests - quantidade de testes a serem criados
 * @return double  - tempo de médio de execução
 */
double test_TreeEditDistance(int numNodes, int numTests) {
    Tree_generator gen;
    gen.generateTreeWithNodes(numNodes, numTests);

    ifstream testFile("tests/trees.json");
    json tests;
    testFile >> tests;

    double execTime = 0;
    long memoryUsage = 0;


    for (json test : tests) {
        int id = test["ID"];
        string t1 = test["t1"];
        string t2 = test["t2"];

        StringCostModel costModel;
        Apted<StringNodeData> algorithm(&costModel);
        BracketStringInputParser p1(t1);
        BracketStringInputParser p2(t2);
        Node<StringNodeData>* n1 = p1.getRoot();
        Node<StringNodeData>* n2 = p2.getRoot();

        auto startTime = std::chrono::high_resolution_clock::now();
        float TED = algorithm.computeEditDistance(n1, n2);
        auto endTime = std::chrono::high_resolution_clock::now();

        execTime += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        memoryUsage += algorithm.MAT.getCount();

        delete n1;
        delete n2;
    }

    cout << "Número de nós: " << numNodes << " - APTED:: Média de tempo gasto em " << numTests << " testes realizados: " << execTime / numTests << "ns" << endl;
    cout << "Número de nós: " << numNodes << " - APTED:: Uso de memória: " << memoryUsage << " KB" << endl;
    return execTime / numTests;
}

/**
 * @brief cria e realiza os testes de TED para zhang-Sasha
 * 
 * @param numNodes - quantidade de nós a serem gerados nas árvores
 * @param numTests - quantidade de testes a serem criados
 * @return double  - tempo de médio de execução
 */
double test_TreeEditDistanceZHSH(int numNodes, int numTests) {
    Tree_generator gen;
    gen.generateTreeWithNodes(numNodes, numTests);

    ifstream testFile("tests/trees.json");
    json tests;
    testFile >> tests;

    double execTime = 0;
    long memoryUsage = 0;

    for (json test : tests) {
        int id = test["ID"];
        string t1 = test["t1"];
        string t2 = test["t2"];

        size_t pos1 = 0;
        size_t pos2 = 0;

        NodeZHSH* tree1 = buildTree(t1, pos1);
        NodeZHSH* tree2 = buildTree(t2, pos2);

        ForestDist fd;

        auto startTime = std::chrono::high_resolution_clock::now();
        int dist = fd.treeDist(tree1, tree2);
        auto endTime = std::chrono::high_resolution_clock::now();

        execTime += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        memoryUsage += fd.MAT.getCount();

        delete tree1;
        delete tree2;
    }

    cout << "Número de nós: " << numNodes << " - ZHSH :: Média de tempo gasto em " << numTests << " testes realizados: " << execTime / numTests << "ns" << endl;
    cout << "Número de nós: " << numNodes << " - ZHSH :: Uso de memória: " << memoryUsage << " KB" << endl;
    return execTime / numTests;
}

// --- main --- //
int main(int argc, char const *argv[]) {
    std::vector<int> numNodesList = {10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100};
    std::vector<int> numTests = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

    for (size_t i = 0; i < numNodesList.size(); ++i) {
        int numNodes = numNodesList[i];
        int tests = numTests[i];
        test_TreeEditDistance(numNodes, tests);
        test_TreeEditDistanceZHSH(numNodes, tests);
    }
}
