#pragma once

/**
 * @file Tree_generator.hpp
 * @author Bernardo Marques
 * @author Bruno Santiago
 * @author Fabio Freire
 * @author Marcos Antônio Lommez
 * @author Saulo de Moura
 * @brief Classe modelo para gerar as árvores para os testes
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

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "../includes/json.hpp"

using json = nlohmann::json;
using namespace std;

class Tree_generator
{
private:
    string createTree(int depth, char startChar);
    string createTreeWithNodes(int numNodes, char startChar);

public:
    Tree_generator();
    void generateTree(int depth, int numTests);
    void generateTreeWithNodes(int numNodes, int numTests);
};
