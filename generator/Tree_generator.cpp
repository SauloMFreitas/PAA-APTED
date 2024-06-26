/**
 * @file Tree_generator.cpp
 * @author Bernardo Marques
 * @author Bruno Santiago
 * @author Fabio Freire
 * @author Marcos Antônio Lommez
 * @author Saulo de Moura
 * @brief classe para gerar as árvores para os testes
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

#include "Tree_generator.hpp"

/**
 * @brief Construtor da classe Tree_generator que inicializa o gerador de números aleatórios
 */
Tree_generator::Tree_generator() {
    srand(time(nullptr));
}

/**
 * @brief Cria uma árvore com uma certa profundidade e um caractere inicial
 * 
 * @param depth - profundidade da árvore a ser criada
 * @param startChar - caractere inicial para o nó raiz
 * @return string - representação da árvore gerada
 */
string Tree_generator::createTree(int depth, char startChar) {
    if (depth == 0) {
        return "{}";
    }

    string tree = "{" + string(1, startChar);
    int numChildren = rand() % 3; // Número aleatório de filhos entre 0 e 2
    for (int i = 0; i < numChildren; ++i) {
        tree += createTree(depth - 1, startChar + 1);
    }
    tree += "}";
    return tree;
}

/**
 * @brief Cria uma árvore com um certo número de nós e um caractere inicial
 * 
 * @param numNodes - número de nós a serem gerados na árvore
 * @param startChar - caractere inicial para o nó raiz
 * @return string - representação da árvore gerada
 */
string Tree_generator::createTreeWithNodes(int numNodes, char startChar) {
    if (numNodes == 0) {
        return "{}";
    }

    string tree = "{" + string(1, startChar);
    --numNodes;

    while (numNodes > 0) {
        int children = rand() % numNodes + 1;
        tree += createTreeWithNodes(children, startChar + 1);
        numNodes -= children;
    }
    tree += "}";
    return tree;
}

/**
 * @brief Gera várias árvores com uma certa profundidade e grava em um arquivo JSON
 * 
 * @param depth - profundidade das árvores a serem geradas
 * @param numTests - quantidade de testes a serem criados
 */
void Tree_generator::generateTree(int depth, int numTests) {
    ofstream outFile("tests/trees.json");
    json j;

    for (int i = 0; i < numTests; ++i) {
        j.push_back({
            {"ID", i},
            {"t1", createTree(depth, 'A')},
            {"t2", createTree(depth, 'A')}
        });
    }

    outFile << j.dump(4);
    outFile.close();
}

/**
 * @brief Gera várias árvores com um certo número de nós e grava em um arquivo JSON
 * 
 * @param numNodes - número de nós a serem gerados nas árvores
 * @param numTests - quantidade de testes a serem criados
 */
void Tree_generator::generateTreeWithNodes(int numNodes, int numTests) {
    ofstream outFile("tests/trees.json");
    json j;

    for (int i = 0; i < numTests; ++i) {
        j.push_back({
            {"ID", i},
            {"t1", createTreeWithNodes(numNodes, 'A')},
            {"t2", createTreeWithNodes(numNodes, 'A')}
        });
    }

    outFile << j.dump(4);
    outFile.close();
}
