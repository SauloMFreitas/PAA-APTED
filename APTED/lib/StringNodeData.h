#pragma once

/**
 * @file StringNodeData.h
 * @author Bernardo Marques
 * @author Bruno Santiago
 * @author Fabio Freire
 * @author Marcos Antônio Lommez
 * @author Saulo de Moura
 * @brief Classe modelo para dados de nós do tipo string e seu parser
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

#include <cassert>
#include <iostream>
#include <sstream>
#include "InputParser.h"
#include "CostModel.h"
#include "util/int.h"

namespace capted {

//------------------------------------------------------------------------------
// String Node Data
//------------------------------------------------------------------------------

/**
 * @brief Classe que representa os dados de um nó como string.
 */
class StringNodeData {
private:
    std::string label;

public:
    friend std::ostream &operator<<(std::ostream &os, StringNodeData const &stringNode);

    /**
     * @brief Construtor da classe StringNodeData.
     * @param label Rótulo do nó.
     */
    StringNodeData(std::string label) : label(label) { }

    /**
     * @brief Obtém o rótulo do nó.
     * @return Rótulo do nó.
     */
    std::string getLabel() const { return label; }
};

/**
 * @brief Sobrecarga do operador de inserção em stream para StringNodeData.
 * @param os Stream de saída.
 * @param stringNode Dados do nó como string.
 * @return Stream de saída.
 */
inline std::ostream &operator<<(std::ostream &os, StringNodeData const &stringNode) {
    os << stringNode.getLabel();
    return os;
}

/**
 * @brief Sobrecarga do operador de inserção em stream para Node<StringNodeData>.
 * @param os Stream de saída.
 * @param node Nó a ser inserido na stream.
 * @return Stream de saída.
 */
inline std::ostream &operator<<(std::ostream &os, Node<StringNodeData> const &node) {
    os << "{";
    os << *node.getData();
    for (Node<StringNodeData>* child : node.getChildren()) {
        os << *child;
    }
    os << "}";
    return os;
}

//------------------------------------------------------------------------------
// String Node Data Parser
//------------------------------------------------------------------------------

/**
 * @brief Classe para analisar e criar uma árvore a partir de uma string de entrada.
 */
class BracketStringInputParser : public InputParser<StringNodeData> {
private:
    const std::string inputString;

    /**
     * @brief Obtém o rótulo da raiz a partir da string de entrada.
     * @param s String de entrada.
     * @return Rótulo da raiz.
     */
    static std::string getRootLabel(std::string s) {
        // Encontra onde os filhos começam, após a própria chave de abertura
        std::size_t start = 1;
        std::size_t end = s.find_first_of('{', 1);

        // Se não houver filhos, o rótulo termina na própria chave de fechamento
        if (end == std::string::npos) {
            end = s.find_first_of('}', 1);
            assert(end != std::string::npos);
        }

        // -2 para excluir a chave de abertura/fechamento
        // +1 por causa da contagem baseada em 0
        return s.substr(start, (end - 2 + 1));
    }

    /**
     * @brief Obtém as strings dos filhos a partir da string de entrada.
     * @param s String de entrada.
     * @return Vetor de strings dos filhos.
     */
    static std::vector<std::string> getChildrenString(std::string s) {
        std::vector<std::string> children;

        // Verifica se há filhos
        std::size_t childrenStart = s.find_first_of('{', 1);
        if (childrenStart == std::string::npos) {
            return children;
        }

        Integer depth = 0;
        std::stringstream currentChild;
        for (size_t i = childrenStart; i < s.size(); i++) {
            switch (s[i]) {
                case '{': depth++; break;
                case '}': depth--; break;
            }

            if (depth == -1) {
                break;
            }

            currentChild << s[i];

            if (depth == 0) {
                children.push_back(currentChild.str());
                currentChild.str(std::string());
            }            
        }

        return children;
    }

public:
    /**
     * @brief Construtor da classe BracketStringInputParser.
     * @param inputString String de entrada.
     */
    BracketStringInputParser(std::string inputString) : inputString(inputString) {
        // nop
    }

    /**
     * @brief Obtém a raiz da árvore a partir da string de entrada.
     * @return Ponteiro para a raiz da árvore.
     */
    virtual Node<StringNodeData>* getRoot() override {
        std::string rootLabel = getRootLabel(inputString);
        std::vector<std::string> childrenString = getChildrenString(inputString);

        Node<StringNodeData>* node = new Node<StringNodeData>(new StringNodeData(rootLabel));
        for (std::string childString : childrenString) {
            BracketStringInputParser parser(childString);
            node->addChild(parser.getRoot());
        }

        return node;
    }
};

//------------------------------------------------------------------------------
// String Node Data Cost Model
//------------------------------------------------------------------------------

/**
 * @brief Classe que representa o modelo de custo para operações em nós de string.
 */
class StringCostModel : public CostModel<StringNodeData> {
public:
    /**
     * @brief Calcula o custo para deletar um nó.
     * @param n Nó a ser deletado.
     * @return Custo da operação de deleção.
     */
    virtual float deleteCost(Node<StringNodeData>* n) const override {
        return 1.0f;
    }

    /**
     * @brief Calcula o custo para inserir um nó.
     * @param n Nó a ser inserido.
     * @return Custo da operação de inserção.
     */
    virtual float insertCost(Node<StringNodeData>* n) const override {
        return 1.0f;
    }

    /**
     * @brief Calcula o custo para renomear um nó.
     * @param n1 Nó de origem.
     * @param n2 Nó de destino.
     * @return Custo da operação de renomeação.
     */
    virtual float renameCost(Node<StringNodeData>* n1, Node<StringNodeData>* n2) const override {
        return (n1->getData()->getLabel() == n2->getData()->getLabel()) ? 0.0f : 1.0f;
    }
};

} // namespace capted
