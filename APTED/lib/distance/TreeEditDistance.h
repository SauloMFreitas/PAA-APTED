#pragma once

/**
 * @file TreeEditDistance.hpp
 * @author Bernardo Marques
 * @author Bruno Santiago
 * @author Fabio Freire
 * @author Marcos Antônio Lommez
 * @author Saulo de Moura
 * @brief Classe modelo para TED (Tree Edit Distance) com métodos genéricos e variáveis comuns para TED
 * @date 2024-06-22
 * 
 * @copyright Copyright (c) 2024
 * 
 * ALgoritmo original retirado de:
 * <p>See the source code for more algorithm-related comments.
 *
 * <p>References:
 * <ul>
 * <li>[1] M. Pawlik and N. Augsten. Efficient Computation of the Tree Edit
 *      Distance. ACM Transactions on Database Systems (TODS) 40(1). 2015.
 * <li>[2] M. Pawlik and N. Augsten. Tree edit distance: Robust and memory-
 *      efficient. Information Systems 56. 2016.
 * </ul>
 * 
 * Algoritmo Original retirado de: https://github.com/DatabaseGroup/apted.git
 * algoritmo traduzido retirado de: https://github.com/Trinovantes/capted.git
 * 
 * Algumas funções foram alteradas do algoritmo original ou traduzido para melhor compreensão do grupo.
 * 
 */

#include "../CostModel.h"
#include "../node/NodeIndexer.h"
#include "../util/int.h"

namespace capted {

//------------------------------------------------------------------------------
// Distance Algorithm
//------------------------------------------------------------------------------

typedef std::pair<Integer, Integer> IntPair;

template<class Data>
class TreeEditDistance {
protected:
    NodeIndexer<Data>* it1; /**< Iterador de nós da árvore 1 */
    NodeIndexer<Data>* it2; /**< Iterador de nós da árvore 2 */
    Integer size1;          /**< Tamanho da árvore 1 */
    Integer size2;          /**< Tamanho da árvore 2 */
    const CostModel<Data>* costModel; /**< Modelo de custo para operações de edição de árvore */

    /**
     * @brief Inicializa os indexadores de nós e os tamanhos das árvores
     * 
     * @param t1 Raiz da árvore 1
     * @param t2 Raiz da árvore 2
     */
    void init(Node<Data>* t1, Node<Data>* t2) {
        it1 = new NodeIndexer<Data>(t1, costModel);
        it2 = new NodeIndexer<Data>(t2, costModel);
        size1 = it1->getSize();
        size2 = it2->getSize();
    }

public:
    /**
     * @brief Construtor da classe TreeEditDistance
     * 
     * @param costModel Modelo de custo para operações de edição de árvore
     */
    TreeEditDistance(CostModel<Data>* costModel) : costModel(costModel) {
        it1 = nullptr;
        it2 = nullptr;
        size1 = -1;
        size2 = -1;
    }

    /**
     * @brief Destrutor da classe TreeEditDistance
     */
    ~TreeEditDistance() {
        delete it1;
        delete it2;
    }

    /**
     * @brief Calcula a distância de edição entre duas árvores
     * 
     * @param t1 Raiz da árvore 1
     * @param t2 Raiz da árvore 2
     * @return float Distância de edição entre as árvores
     */
    virtual float computeEditDistance(Node<Data>* t1, Node<Data>* t2) = 0;
};

} // namespace capted
