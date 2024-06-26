#pragma once

/**
 * @file InputParser.h
 * @author Bernardo Marques
 * @author Bruno Santiago
 * @author Fabio Freire
 * @author Marcos Antônio Lommez
 * @author Saulo de Moura
 * @brief classe modelo para parse entre o string da árvore para a estrutura
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
// Parser
//------------------------------------------------------------------------------

/**
 * @brief Classe abstrata para o parser de entrada
 * 
 * @tparam Data Tipo dos dados armazenados nos nós
 */
template<class Data>
class InputParser {
public:
    /**
     * @brief Construtor da classe InputParser
     */
    InputParser() { }

    /**
     * @brief Obtém a raiz da árvore parseada
     * 
     * @return Node<Data>* Ponteiro para a raiz da árvore
     */
    virtual Node<Data>* getRoot() = 0;
};

} // namespace capted
