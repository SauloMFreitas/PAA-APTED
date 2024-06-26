#ifndef NodeZHSH_HPP
#define NodeZHSH_HPP

/**
 * @file forest_dist.hpp
 * @author Bernardo Marques
 * @author Bruno Santiago
 * @author Fabio Freire
 * @author Marcos Antônio Lommez
 * @author Saulo de Moura
 * @brief Classe modelo para representar um nó da árvore para o algoritmo Zhang-Shasha
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

#include <string>
#include <vector>

class NodeZHSH {
public:
    std::string label; // Rótulo do nó, representado por uma string
    int index; // Índice do nó, representado por um inteiro
    std::vector<NodeZHSH*> children; // Vetor de ponteiros para os nós filhos
    NodeZHSH* leftmost; // Ponteiro para o nó filho mais à esquerda

    // Construtor padrão
    NodeZHSH();
    
    // Construtor que inicializa o rótulo do nó
    NodeZHSH(const std::string& label);
};

#endif 
