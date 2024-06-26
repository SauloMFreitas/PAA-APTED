/**
 * @file forest_dist.cpp
 * @author Bernardo Marques
 * @author Bruno Santiago
 * @author Fabio Freire
 * @author Marcos Antônio Lommez
 * @author Saulo de Moura
 * @brief Classe para calcular a distância entre duas árvores utilizando o algoritmo Zhang-Shasha
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

#include "../includes/MemoryAccessTracker.hpp"
#include "forest_dist.hpp"
#include "NodeZHSH.hpp"
#include <vector>
#include <algorithm>


/**
 * @brief Função para calcular os índices dos nós mais à esquerda.
 * 
 * @param nodes Vetor de nós.
 * @return Vetor de inteiros representando os índices dos nós mais à esquerda.
 */
std::vector<int> ForestDist::computeLeftmost(const std::vector<NodeZHSH*>& nodes) {
    std::vector<int> leftmost(nodes.size());
    for (int i = nodes.size() - 1; i >= 0; --i) {
        if (nodes[i]->children.empty()) {
            leftmost[i] = i; // Se o nó não tiver filhos, ele é o mais à esquerda
        } else {
            leftmost[i] = leftmost[nodes[i]->children.front()->index]; // Caso contrário, é o índice do filho mais à esquerda
        }
    }
    return leftmost;
}

/**
 * @brief Função para pré-processar os nós da árvore.
 * 
 * @param root Raiz da árvore.
 * @param nodes Vetor para armazenar os nós na ordem de travessia pós-ordem.
 */
void ForestDist::preprocessNodes(NodeZHSH* root, std::vector<NodeZHSH*>& nodes) {
    if (root == nullptr) return; // Se a raiz for nula, não faz nada
    for (NodeZHSH* child : root->children) {
        preprocessNodes(child, nodes); // Chama recursivamente para cada filho
    }
    root->index = nodes.size(); // Define o índice do nó como o tamanho atual do vetor
    nodes.push_back(root); // Adiciona o nó ao vetor
}

/**
 * @brief Função para calcular a distância entre duas árvores utilizando programação dinâmica.
 * 
 * @param root1 Raiz da primeira árvore.
 * @param root2 Raiz da segunda árvore.
 * @return Distância de edição entre as duas árvores.
 */
int ForestDist::treeDist(NodeZHSH* root1, NodeZHSH* root2) {
    if (root1 == nullptr || root2 == nullptr) return 0; // Se alguma das raízes for nula, a distância é 0
    std::vector<NodeZHSH*> nodes1, nodes2;
    preprocessNodes(root1, nodes1); // Pré-processa os nós da primeira árvore
    preprocessNodes(root2, nodes2); // Pré-processa os nós da segunda árvore

    std::vector<int> leftmost1 = computeLeftmost(nodes1); // Calcula os nós mais à esquerda para a primeira árvore
    std::vector<int> leftmost2 = computeLeftmost(nodes2); // Calcula os nós mais à esquerda para a segunda árvore

    return forestDist(nodes1, nodes2); // Calcula e retorna a distância entre as duas árvores
}

/**
 * @brief Função para calcular a distância entre duas florestas utilizando programação dinâmica.
 * 
 * @param forest1 Vetor de nós representando a primeira floresta.
 * @param forest2 Vetor de nós representando a segunda floresta.
 * @return Distância de edição entre as duas florestas.
 */
int ForestDist::forestDist(const std::vector<NodeZHSH*>& forest1, const std::vector<NodeZHSH*>& forest2) {
    MAT.reset(); // Reseta o contador de acessos à memória
    int m = forest1.size();
    int n = forest2.size();
    std::vector<std::vector<int>> dist(m + 1, std::vector<int>(n + 1)); // Matriz para armazenar as distâncias
    for (int i = 1; i <= m; ++i) {
        MAT.increment();
        dist[i][0] = dist[i-1][0] + 1; // Custo de deletar nó
    }
    for (int j = 1; j <= n; ++j) {
        MAT.increment();
        dist[0][j] = dist[0][j-1] + 1; // Custo de inserir nó
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int cost = (forest1[i-1]->label == forest2[j-1]->label) ? 0 : 1; // Custo de substituição (0 se os rótulos forem iguais, 1 se forem diferentes)
            dist[i][j] = std::min({dist[i-1][j] + 1, dist[i][j-1] + 1, dist[i-1][j-1] + cost}); // Mínimo entre deletar, inserir ou substituir
            MAT.increment();
        }
    }
    return dist[m][n]; // Retorna a distância entre as duas florestas
}