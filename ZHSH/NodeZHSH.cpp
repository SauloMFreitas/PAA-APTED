// NodeZHSH.cpp
#include "NodeZHSH.hpp"

/**
 * @file Node_ZHSH.cpp
 * @author Bernardo Marques
 * @author Bruno Santiago
 * @author Fabio Freire
 * @author Marcos Antônio Lommez
 * @author Saulo de Moura
 * @brief Classe para representar um nó da árvore para o algoritmo Zhang-Shasha
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

/**
 * @brief Construtor padrão da classe NodeZHSH.
 */
NodeZHSH::NodeZHSH() : index(0), leftmost(nullptr) {}

/**
 * @brief Construtor que inicializa o rótulo do nó.
 * 
 * @param label Rótulo do nó.
 */
NodeZHSH::NodeZHSH(const std::string& label) : label(label), index(0), leftmost(nullptr) {}
