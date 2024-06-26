#ifndef FOREST_DIST_HPP
#define FOREST_DIST_HPP

/**
 * @file forest_dist.hpp
 * @author Bernardo Marques
 * @author Bruno Santiago
 * @author Fabio Freire
 * @author Marcos Antônio Lommez
 * @author Saulo de Moura
 * @brief Classe modelo para calcular a distância entre duas árvores utilizando o algoritmo Zhang-Shasha
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

#include <vector>
#include "NodeZHSH.hpp"
#include "../includes/MemoryAccessTracker.hpp"


class ForestDist {
public:

    static MemoryAccessTracker MAT;

    // Função que computa o nó mais à esquerda para um vetor de nós
    static std::vector<int> computeLeftmost(const std::vector<NodeZHSH*>& nodes);
    
    //Essa função percorre a árvore a partir da raiz, armazenando os nós em um vetor na ordem de travessia pós-ordem.
    static void preprocessNodes(NodeZHSH* root, std::vector<NodeZHSH*>& nodes);
    
    // Essa função calcula a distância de edição entre duas árvores, representadas por suas raízes.
    static int treeDist(NodeZHSH* root1, NodeZHSH* root2);
    
    // Essa função calcula a distância de edição entre duas florestas, representadas por vetores de nós.
    static int forestDist(const std::vector<NodeZHSH*>& forest1, const std::vector<NodeZHSH*>& forest2);
};

#endif // FOREST_DIST_HPP
