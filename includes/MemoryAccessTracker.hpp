#pragma once

/**
 * @file MemoryAccessTracker.hpp
 * @author Bernardo Marques
 * @author Bruno Santiago
 * @author Fabio Freire
 * @author Marcos Antônio Lommez
 * @author Saulo de Moura
 * @brief Classe modelo gravar a quantidade de acessos na memória
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
 * @brief Classe para rastrear o acesso à memória
 */
class MemoryAccessTracker {
public:
    static long accessCount; ///< Contador de acessos à memória

    /**
     * @brief Incrementa o contador de acessos
     */
    static void increment() {
        ++accessCount;
    }

    /**
     * @brief Reseta o contador de acessos
     */
    static void reset() {
        accessCount = 0;
    }

    /**
     * @brief Retorna o valor atual do contador de acessos
     * 
     * @return long - quantidade de acessos
     */
    static long getCount() {
        return accessCount;
    }
};
