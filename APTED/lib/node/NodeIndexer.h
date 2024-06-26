#pragma once

/**
 * @file NodeIndexer.h
 * @author Bernardo Marques
 * @author Bruno Santiago
 * @author Fabio Freire
 * @author Marcos Antônio Lommez
 * @author Saulo de Moura
 * @brief Indexa nós da árvore de entrada para o algoritmo que está em parse
 *        para a estrutura em árvore usando a classe @link Node.h. Armazena
 *        vários indices nos nós requeridos. adicionalmente armazena propriedades
 *        de valor único na árvore
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

#include <vector>
#include <iostream>
#include "../util/debug.h"
#include "../util/int.h"

namespace capted {

//------------------------------------------------------------------------------
// Node Indexer
//------------------------------------------------------------------------------

template <class NodeData>
class AllPossibleMappings;

template <class NodeData>
class Apted;

template<class Data>
class NodeIndexer {
private:
    typedef Node<Data> N;

    friend AllPossibleMappings<Data>;
    friend Apted<Data>;

    const CostModel<Data>* costModel; /**< Modelo de custo para operações de edição de árvore */
    const Integer treeSize; /**< Tamanho da árvore */

    // Índices de estrutura
    std::vector<Integer> sizes;
    std::vector<Integer> parents;
    std::vector<std::vector<Integer>> children;

    std::vector<Integer> postL_to_lld;
    std::vector<Integer> postR_to_rld;
    std::vector<Integer> preL_to_ln;
    std::vector<Integer> preR_to_ln;

    std::vector<N*> preL_to_node;
    std::vector<bool> nodeType_L;
    std::vector<bool> nodeType_R;

    // Índices de tradução de travessia
    std::vector<Integer> preL_to_preR;
    std::vector<Integer> preR_to_preL;
    std::vector<Integer> preL_to_postL;
    std::vector<Integer> preL_to_postR;
    std::vector<Integer> postL_to_preL;
    std::vector<Integer> postR_to_preL;

    // Índices de custo
    std::vector<Integer> preL_to_kr_sum;
    std::vector<Integer> preL_to_rev_kr_sum;
    std::vector<Integer> preL_to_desc_sum;
    std::vector<float> preL_to_sumDelCost;
    std::vector<float> preL_to_sumInsCost;

    // Variáveis temporárias
    Integer currentNode;
    Integer lchl;
    Integer rchl;
    Integer sizeTmp;
    Integer descSizesTmp;
    Integer krSizesSumTmp;
    Integer revkrSizesSumTmp;
    Integer preorderTmp;

    /**
     * @brief Indexa os nós da árvore em pré-ordem e pós-ordem
     * 
     * @param node Nó atual
     * @param postorder Índice em pós-ordem
     * @return Integer Novo índice em pós-ordem
     */
    Integer indexNodes(N* node, Integer postorder) {
        // Inicializa variáveis.
        Integer currentSize = 0;
        Integer childrenCount = 0;
        Integer descSizes = 0;
        Integer krSizesSum = 0;
        Integer revkrSizesSum = 0;
        Integer preorder = preorderTmp;
        Integer preorderR = 0;
        Integer currentPreorder = -1;

        // Armazena o ID de pré-ordem do nó atual para usar após a recursão.
        preorderTmp++;

        // Loop sobre os filhos de um nó.
        std::vector<N*> childNodes = node->getChildrenAsVector();
        for (size_t i = 0; i < childNodes.size(); i++) {
            childrenCount++;
            currentPreorder = preorderTmp;
            parents[currentPreorder] = preorder;

            // Executa o método recursivamente para o próximo filho.
            postorder = indexNodes(childNodes[i], postorder);
            children[preorder].push_back(currentPreorder);

            currentSize += 1 + sizeTmp;
            descSizes += descSizesTmp;

            if (childrenCount > 1) {
                krSizesSum += krSizesSumTmp + sizeTmp + 1;
            } else {
                krSizesSum += krSizesSumTmp;
                nodeType_L[currentPreorder] = true;
            }

            if (i < childNodes.size() - 1) {
                revkrSizesSum += revkrSizesSumTmp + sizeTmp + 1;
            } else {
                revkrSizesSum += revkrSizesSumTmp;
                nodeType_R[currentPreorder] = true;
            }
        }

        postorder++;

        Integer currentDescSizes = descSizes + currentSize + 1;

        Integer temp_mul = (currentSize + 1) * (currentSize + 1 + 3);
        if (__builtin_mul_overflow((currentSize + 1), (currentSize + 1 + 3), &temp_mul)) {
            printf("Overflow in %s::%d\n", __FILE__, __LINE__);
            exit(1);
        }

        preL_to_desc_sum[preorder] = (temp_mul) / 2 - currentDescSizes;
        preL_to_kr_sum[preorder] = krSizesSum + currentSize + 1;
        preL_to_rev_kr_sum[preorder] = revkrSizesSum + currentSize + 1;

        // Armazena o ponteiro para um objeto nó correspondente à pré-ordem.
        preL_to_node[preorder] = node;

        sizes[preorder] = currentSize + 1;
        preorderR = treeSize - 1 - postorder;
        preL_to_preR[preorder] = preorderR;
        preR_to_preL[preorderR] = preorder;

        descSizesTmp = currentDescSizes;
        sizeTmp = currentSize;
        krSizesSumTmp = krSizesSum;
        revkrSizesSumTmp = revkrSizesSum;

        postL_to_preL[postorder] = preorder;
        preL_to_postL[preorder] = postorder;
        preL_to_postR[preorder] = treeSize - 1 - preorder;
        postR_to_preL[treeSize - 1 - preorder] = preorder;

        return postorder;
    }

    /**
     * @brief Realiza a indexação pós-ordem na árvore
     */
    void postTraversalIndexing() {
        Integer currentLeaf = -1;
        Integer nodeForSum = -1;
        Integer parentForSum = -1;

        for (Integer i = 0; i < treeSize; i++) {
            preL_to_ln[i] = currentLeaf;
            if (isLeaf(i)) {
                currentLeaf = i;
            }

            // Armazena os descendentes folha mais à esquerda para cada nó indexado em pós-ordem.
            Integer postl = i; // Assume que o loop itera em pós-ordem.
            Integer preorder = postL_to_preL[i];
            if (sizes[preorder] == 1) {
                postL_to_lld[postl] = postl;
            } else {
                postL_to_lld[postl] = postL_to_lld[preL_to_postL[children[preorder][0]]];
            }
            // Armazena os descendentes folha mais à direita para cada nó indexado em pós-ordem reversa.
            Integer postr = i; // Assume que o loop itera em pós-ordem reversa.
            preorder = postR_to_preL[postr];
            if (sizes[preorder] == 1) {
                postR_to_rld[postr] = postr;
            } else {
                postR_to_rld[postr] = postR_to_rld[preL_to_postR[children[preorder][children[preorder].size() - 1]]];
            }
            // Conta lchl e rchl.
            if (sizes[i] == 1) {
                Integer parent = parents[i];
                if (parent > -1) {
                    if (parent + 1 == i) {
                        lchl++;
                    } else if (preL_to_preR[parent] + 1 == preL_to_preR[i]) {
                        rchl++;
                    }
                }
            }

            // Soma os custos de deletar e inserir subárvores inteiras.
            nodeForSum = treeSize - i - 1;
            parentForSum = parents[nodeForSum];
            // Atualiza o próprio nó.
            preL_to_sumDelCost[nodeForSum] += costModel->deleteCost(preL_to_node[nodeForSum]);
            preL_to_sumInsCost[nodeForSum] += costModel->insertCost(preL_to_node[nodeForSum]);
            if (parentForSum > -1) {
                // Atualiza o nó pai.
                preL_to_sumDelCost[parentForSum] += preL_to_sumDelCost[nodeForSum];
                preL_to_sumInsCost[parentForSum] += preL_to_sumInsCost[nodeForSum];
            }
        }

        currentLeaf = -1;
        // Itera sobre os nós novamente para completar as listas de folhas.
        for (Integer i = 0; i < sizes[0]; i++) {
            preR_to_ln[i] = currentLeaf;
            if (isLeaf(preR_to_preL[i])) {
                currentLeaf = i;
            }
        }
    }

public:
    /**
     * @brief Construtor da classe NodeIndexer
     * 
     * @param inputTree Árvore de entrada
     * @param costModel Modelo de custo
     */
    NodeIndexer(N* inputTree, const CostModel<Data>* costModel)
        : costModel(costModel), treeSize(inputTree->getNodeCount()) {
        // Inicializa variáveis temporárias
        currentNode = 0;
        lchl = 0;
        rchl = 0;
        sizeTmp = 0;
        descSizesTmp = 0;
        krSizesSumTmp = 0;
        revkrSizesSumTmp = 0;
        preorderTmp = 0;

        // Inicializa índices
        sizes.resize(treeSize, 0);
        children.resize(treeSize);
        parents.resize(treeSize, 0);
        parents[0] = -1; // Raiz não tem pai

        postL_to_lld.resize(treeSize, 0);
        postR_to_rld.resize(treeSize, 0);
        preL_to_ln.resize(treeSize, 0);
        preR_to_ln.resize(treeSize, 0);

        preL_to_node.resize(treeSize, nullptr);
        nodeType_L.resize(treeSize, false);
        nodeType_R.resize(treeSize, false);

        preL_to_preR.resize(treeSize, 0);
        preR_to_preL.resize(treeSize, 0);
        preL_to_postL.resize(treeSize, 0);
        preL_to_postR.resize(treeSize, 0);
        postL_to_preL.resize(treeSize, 0);
        postR_to_preL.resize(treeSize, 0);

        preL_to_kr_sum.resize(treeSize, 0);
        preL_to_rev_kr_sum.resize(treeSize, 0);
        preL_to_desc_sum.resize(treeSize, 0);
        preL_to_sumDelCost.resize(treeSize, 0.0f);
        preL_to_sumInsCost.resize(treeSize, 0.0f);

        // Indexa
        indexNodes(inputTree, -1);
        postTraversalIndexing();
    }

    /**
     * @brief Obtém o tamanho da árvore
     * @return Integer Tamanho da árvore
     */
    Integer getSize() {
        return treeSize;
    }

    /**
     * @brief Obtém o índice da folha mais à esquerda para um nó dado em pré-ordem
     * @param preL Índice em pré-ordem
     * @return Integer Índice da folha mais à esquerda
     */
    Integer preL_to_lld(Integer preL) {
        return postL_to_preL[postL_to_lld[preL_to_postL[preL]]];
    }

    /**
     * @brief Obtém o índice da folha mais à direita para um nó dado em pré-ordem
     * @param preL Índice em pré-ordem
     * @return Integer Índice da folha mais à direita
     */
    Integer preL_to_rld(Integer preL) {
        return postR_to_preL[postR_to_rld[preL_to_postR[preL]]];
    }

    /**
     * @brief Obtém o nó correspondente a um índice dado em pós-ordem
     * @param postL Índice em pós-ordem
     * @return Node<Data>* Ponteiro para o nó
     */
    Node<Data>* postL_to_node(Integer postL) {
        return preL_to_node[postL_to_preL[postL]];
    }

    /**
     * @brief Obtém o nó correspondente a um índice dado em pós-ordem reverso
     * @param postR Índice em pós-ordem reverso
     * @return Node<Data>* Ponteiro para o nó
     */
    Node<Data>* postR_to_node(Integer postR) {
        return preL_to_node[postR_to_preL[postR]];
    }

    /**
     * @brief Verifica se um nó é folha
     * @param nodeId ID do nó
     * @return true Se o nó é folha
     * @return false Se o nó não é folha
     */
    bool isLeaf(Integer nodeId) {
        return sizes[nodeId] == 1;
    }

    /**
     * @brief Obtém o nó atual
     * @return Integer ID do nó atual
     */
    Integer getCurrentNode() const {
        return currentNode;
    }

    /**
     * @brief Define o nó atual
     * @param preorder Índice em pré-ordem
     */
    void setCurrentNode(Integer preorder) {
        currentNode = preorder;
    }

    /**
     * @brief Exibe os índices e outras informações da árvore
     */
    void dump() {
        std::cerr << std::string(80, '-') << std::endl;
        std::cerr << "sizes: "              << arrayToString(sizes)              << std::endl;
        std::cerr << "preL_to_preR: "       << arrayToString(preL_to_preR)       << std::endl;
        std::cerr << "preR_to_preL: "       << arrayToString(preR_to_preL)       << std::endl;
        std::cerr << "preL_to_postL: "      << arrayToString(preL_to_postL)      << std::endl;
        std::cerr << "postL_to_preL: "      << arrayToString(postL_to_preL)      << std::endl;
        std::cerr << "preL_to_postR: "      << arrayToString(preL_to_postR)      << std::endl;
        std::cerr << "postR_to_preL: "      << arrayToString(postR_to_preL)      << std::endl;
        std::cerr << "postL_to_lld: "       << arrayToString(postL_to_lld)       << std::endl;
        std::cerr << "postR_to_rld: "       << arrayToString(postR_to_rld)       << std::endl;
        std::cerr << "preL_to_node: "       << arrayToString(preL_to_node)       << std::endl;
        std::cerr << "preL_to_ln: "         << arrayToString(preL_to_ln)         << std::endl;
        std::cerr << "preR_to_ln: "         << arrayToString(preR_to_ln)         << std::endl;
        std::cerr << "preL_to_kr_sum: "     << arrayToString(preL_to_kr_sum)     << std::endl;
        std::cerr << "preL_to_rev_kr_sum: " << arrayToString(preL_to_rev_kr_sum) << std::endl;
        std::cerr << "preL_to_desc_sum: "   << arrayToString(preL_to_desc_sum)   << std::endl;
        std::cerr << "preL_to_sumDelCost: " << arrayToString(preL_to_sumDelCost) << std::endl;
        std::cerr << "preL_to_sumInsCost: " << arrayToString(preL_to_sumInsCost) << std::endl;
        std::cerr << "children: "           << arrayToString(children)           << std::endl;
        std::cerr << "nodeType_L: "         << arrayToString(nodeType_L)         << std::endl;
        std::cerr << "nodeType_R: "         << arrayToString(nodeType_R)         << std::endl;
        std::cerr << "parents: "            << arrayToString(parents)            << std::endl;
        std::cerr << std::string(80, '-') << std::endl;
    }
};

}
