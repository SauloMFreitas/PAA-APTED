#pragma once

/**
 * @file Capted.hpp
 * @author Bernardo Marques
 * @author Bruno Santiago
 * @author Fabio Freire
 * @author Marcos Antônio Lommez
 * @author Saulo de Moura
 * @brief Iincludes das principais classes do projeto
 * @date 2024-06-22
 * 
 * @copyright Copyright (c) 2024
 * 
 * Algoritmo original retirado de:
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
 * Algumas funções foram alteradas do algoritmo original ou tradizido para melhor compreenção do grupo.
 * 
 */

#include "node/Node.h"
#include "distance/Apted.h"

#include "CostModel.h"
#include "InputParser.h"
#include "StringNodeData.h"
