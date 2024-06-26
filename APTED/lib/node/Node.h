#pragma once

/**
 * @file Node.h
 * @author Bernardo Marques
 * @author Bruno Santiago
 * @author Fabio Freire
 * @author Marcos Antônio Lommez
 * @author Saulo de Moura
 * @brief Classe modelo para TED (Tree Edit Distance) com métodos genéricos e variáveis comuns para TED
 * 
 * @brief Representação de uma árvore ordenada. Cada nó armazena
 *        os endereços de seus n filhos.
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
 * Algoritmo traduzido retirado de: https://github.com/Trinovantes/capted.git
 * 
 * Algumas funções foram alteradas do algoritmo original ou traduzido para melhor compreensão do grupo.
 * 
 */

#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <cassert>
#include "../util/int.h"

namespace capted {

//------------------------------------------------------------------------------
// Node
//------------------------------------------------------------------------------

template<class Data>
class Node {
private:
    Data* data; /**< Dados armazenados no nó */
    Node<Data>* parent; /**< Nó pai */
    std::list<Node<Data>*> children; /**< Lista de nós filhos */

public:
    /**
     * @brief Construtor da classe Node
     * 
     * @param data Dados a serem armazenados no nó
     */
    Node(Data* data) : data(data), parent(nullptr) {
        // nop
    }

    /**
     * @brief Destrutor da classe Node
     */
    virtual ~Node() {
        delete data;

        for (Node<Data>* c : children) {
            delete c;
        }
    }

    //-------------------------------------------------------------------------
    // Funções auxiliares de travessia
    //-------------------------------------------------------------------------

    /**
     * @brief Clona o nó atual e seus filhos
     * 
     * @return Node<Data>* Ponteiro para o nó clonado
     */
    Node<Data>* clone() {
        auto copy = new Node<Data>(cloneData(data));

        for (Node<Data>* child : children) {
            copy->addChild(child->clone());
        }

        return copy;
    }

    /**
     * @brief Desanexa o nó atual de seu pai
     */
    void detachFromParent() {
        bool madeChange = false;
        std::list<Node<Data>*> &siblings = parent->children;

        auto iter = siblings.begin();
        while (iter != siblings.end()) {
            if (*iter == this) {
                assert(!madeChange);
                iter = siblings.erase(iter);
                parent = nullptr;
                madeChange = true;
            } else {
                iter++;
            }
        }

        assert(madeChange);
    }

    /**
     * @brief Substitui um filho pelo nó de substituição
     * 
     * @param child Nó filho a ser substituído
     * @param replacement Nó de substituição
     */
    void replaceChild(Node<Data>* child, Node<Data>* replacement) {
        bool madeChange = false;

        auto iter = children.begin();
        while (iter != children.end()) {
            if (*iter == child) {
                assert(!madeChange);
                assert(!replacement->parent);
                *iter = replacement;
                replacement->parent = this;
                madeChange = true;
            }

            iter++;
        }

        assert(madeChange);
    }

    /**
     * @brief Realiza uma busca em profundidade na árvore
     * 
     * @param callback Função de callback a ser chamada em cada nó
     * @param depth Profundidade inicial
     */
    void dfs(std::function<void(Node<Data>* currentNode, Integer depth)> callback, Integer depth = 0) {
        callback(this, depth);

        for (Node<Data>* child : children) {
            child->dfs(callback, depth + 1);
        }
    }

    //-------------------------------------------------------------------------
    // Getters e setters
    //-------------------------------------------------------------------------

    /**
     * @brief Obtém os dados armazenados no nó
     * 
     * @return Data* Ponteiro para os dados armazenados no nó
     */
    Data* getData() const {
        return data;
    }

    /**
     * @brief Obtém a contagem total de nós na subárvore enraizada no nó atual
     * 
     * @return Integer Contagem total de nós
     */
    Integer getNodeCount() const {
        Integer sum = 1;

        for (Node<Data>* c : children) {
            sum += c->getNodeCount();
        }

        return sum;
    }

    /**
     * @brief Obtém o número de filhos do nó
     * 
     * @return Integer Número de filhos
     */
    Integer getNumChildren() const {
        return children.size();
    }

    /**
     * @brief Obtém a lista de filhos do nó
     * 
     * @return std::list<Node<Data>*>& Referência para a lista de filhos
     */
    std::list<Node<Data>*> &getChildren() {
        return children;
    }

    /**
     * @brief Obtém a lista de filhos do nó (versão constante)
     * 
     * @return std::list<Node<Data>*> Lista de filhos
     */
    std::list<Node<Data>*> getChildren() const {
        return children;
    }

    /**
     * @brief Obtém os filhos do nó como um vetor
     * 
     * @return std::vector<Node<Data>*> Vetor de filhos
     */
    std::vector<Node<Data>*> getChildrenAsVector() const {
        return std::vector<Node<Data>*>(children.begin(), children.end());
    }

    /**
     * @brief Obtém o i-ésimo filho do nó
     * 
     * @param i Índice do filho a ser obtido
     * @return Node<Data>* Ponteiro para o i-ésimo filho
     */
    Node<Data>* getIthChild(Integer i) const {
        assert(i >= 0);
        assert(i < (Integer)children.size());

        auto it = children.begin();
        while (i > 0) {
            it++;
            i--;
        }

        return *it;
    }

    /**
     * @brief Obtém o nó pai
     * 
     * @return Node<Data>* Ponteiro para o nó pai
     */
    Node<Data>* getParent() {
        return parent;
    }

    /**
     * @brief Define o nó pai
     * 
     * @param parent Ponteiro para o nó pai
     */
    void setParent(Node<Data>* parent) {
        assert(this->parent == nullptr);
        this->parent = parent;
    }

    /**
     * @brief Adiciona um filho ao nó
     * 
     * @param child Ponteiro para o nó filho a ser adicionado
     */
    void addChild(Node<Data>* child) {
        assert(child);
        assert(!child->parent);

        child->setParent(this);
        children.push_back(child);
    }

    /**
     * @brief Insere um filho na posição especificada
     * 
     * @param destIter Iterador para a posição onde o filho será inserido
     * @param child Ponteiro para o nó filho a ser inserido
     * @return typename std::list<Node<Data>*>::iterator Iterador para o nó inserido
     */
    typename std::list<Node<Data>*>::iterator insertChild(typename std::list<Node<Data>*>::iterator destIter, Node<Data>* child) {
        assert(child);
        assert(!child->parent);

        child->setParent(this);
        return children.insert(destIter, child);
    }

    /**
     * @brief Obtém o iterador para o nó atual na lista de filhos do pai
     * 
     * @return typename std::list<Node<Data>*>::iterator Iterador para o nó atual
     */
    typename std::list<Node<Data>*>::iterator getMyIter() const {
        return std::find(parent->getChildren().begin(), parent->getChildren().end(), this);
    }
};

} // namespace capted
