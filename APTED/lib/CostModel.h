#pragma once

/**
 * @file CostModel.h
 * @author Bernardo Marques
 * @author Bruno Santiago
 * @author Fabio Freire
 * @author Marcos Antônio Lommez
 * @author Saulo de Moura
 * @brief classe modelo para implementar o custo de edição
 *        Os métodos presentes representam os custos para 
 *        as operações de edição (delete, Insert, Rename)
 * @date 2024-06-22
 * 
 * @copyright Copyright (c) 2024
 * 
 * Algoritmo original retirado de:
 * <p>See the source code para mais comentários relacionados ao algoritmo.
 *
 * <p>Referências:
 * <ul>
 * <li>[1] M. Pawlik and N. Augsten. Efficient Computation of the Tree Edit
 *      Distance. ACM Transactions on Database Systems (TODS) 40(1). 2015.
 * <li>[2] M. Pawlik and N. Augsten. Tree edit distance: Robust and memory-
 *      efficient. Information Systems 56. 2016.
 * </ul>
 * 
 * Algoritmo Original retirado de: https://github.com/DatabaseGroup/apted.git
 * Algoritmo traduzido retirado de: https://github.com/Trinovantes/capted.git
 * 
 * Algumas funções foram alteradas do algoritmo original ou traduzido para melhor compreensão do grupo.
 * 
 */

#include "node/Node.h"

namespace capted {

//------------------------------------------------------------------------------
// Cost Model
//------------------------------------------------------------------------------

/**
 * @brief Classe abstrata para o modelo de custo
 * 
 * @tparam Data Tipo dos dados armazenados nos nós
 */
template<class Data>
class CostModel {
public:
    /**
     * @brief Calcula o custo de deletar um nó
     * 
     * @param n Ponteiro para o nó a ser deletado
     * @return float Custo de deletar o nó
     */
    virtual float deleteCost(Node<Data>* n) const = 0;

    /**
     * @brief Calcula o custo de inserir um nó
     * 
     * @param n Ponteiro para o nó a ser inserido
     * @return float Custo de inserir o nó
     */
    virtual float insertCost(Node<Data>* n) const = 0;

    /**
     * @brief Calcula o custo de renomear um nó para outro
     * 
     * @param n1 Ponteiro para o primeiro nó
     * @param n2 Ponteiro para o segundo nó
     * @return float Custo de renomear o nó
     */
    virtual float renameCost(Node<Data>* n1, Node<Data>* n2) const = 0;
};

} // namespace capted
