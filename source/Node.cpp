#pragma once

#include "../includes/Node.hpp"

// --- public methods ----

// --- constructors
template<class Data>
Node<Data>::Node(Data* data): data(data), parent(nullptr){}


template<class Data>
Node<Data>::~Node(){
    delete data;

    for(Node<Data>* child : children){
        delete child;
    }
}


// --- getters

template<class Data>
Data* Node<Data>::getData() const { 

    return data; 

}

template<class Data>
int Node<Data>::getNodecount() const {
    int sum = 1;
    for(Node<Data>* child : children){
        sum += child->getNodecount();
    }
    return sum;
}

template<class Data>
int Node<Data>::getNumChildren() const{ 
    
    return children.size(); 

}

template<class Data>
list<Node<Data>*> Node<Data>::getChildren() const{ 

    return children; 

}

template<class Data>
vector<Node<Data>*> Node<Data>::getChildrenAsVector() const{ 
    
    return vector<Node<Data>*>(children.begin(), children.end());

}

template<class Data>
Node<Data>* Node<Data>::getChild(int i) const{
    assert(i >=0);
    assert(i < (int)children.size());

    auto it = children.begin();
    while (i > 0){
        
        it++;
        i--;

    }
    return *it;
    
}

template<class Data>
Node<Data>* Node<Data>::getParent(){

    return parent;

}

// --- setters

template<class Data>
void Node<Data>::setParent(Node<Data>* parent){
    assert(this->parent == nullptr);
    this->parent = parent;
}

template<class Data>
void Node<Data>::addChild(Node<Data>* child){

    assert(child);
    assert(!child->parent);
    child->setParent(this);
    children.push_back(child);

}


template<class Data>
typename list<Node<Data>*>::iterator Node<Data>::insertChild(typename list<Node<Data>*>::iterator destIter, Node<Data>* child){
    
    assert(child);
    assert(!child->parent);

    child->setParent(this);
    return children.insert(destIter, child);

}

template<class Data>
typename list<Node<Data>*>::iterator Node<Data>::getMyIter() const{
    return find(parent->getChildren().begin(), parent->getChildren().end(), this);
}

// --- helping Funcions

/**
 * @brief clone all children of this node
 * @brief clona todos os filhos deste nó
 * 
 * @return Node<Data>* children cloned
 * @return Node<Data>* filhos clonados
 */

template<class Data>
Node<Data>* Node<Data>::clone(){
    Node<Data>* copy = new Node<Data>(cloneData(data));

    for(Node<Data>* child : children){
        copy->addChild(child->clone());
    }

    return copy;
}

/**
 * @brief dessociate all children from the parent of this node
 * @brief separa todos os filhos do pai do nó atual
 * 
 */

template<class Data>
void Node<Data>::dissociateFromParent(){
    bool madeChanges = false;
    list<Node<Data>*> siblings = parent->children;
    auto aux = siblings.begin();
    while (aux != siblings.end()){
        if (*aux == this)
        {
            assert(!madeChanges);
            aux = siblings.erase(aux);
            parent = nullptr;
            madeChanges = true;
        }else{
            aux++;
        }
        
    }
    
    assert(madeChanges);
}


/**
 * @brief replace the @param child node for the @param replacement node
 * @brief substitui o nó @param child  para o nó @param replacement
 * 
 * @param child - Node to be replaced
 * @param child - nó para ser substituido
 * @param replacement - Node to replace
 * @param replacement - nó para substituir
 */

template<class Data>
void Node<Data>::replaceChild(Node<Data>* child,Node<Data>* replacement){


    bool madeChanges = false;

    auto aux = children.begin();
    while(aux != children.end()){
        if(*aux == child){
            assert(!madeChanges);
            assert(!replacement->parent);
        
            *aux = replacement;
            replacement->parent = this;
            madeChanges = true;
        }
        aux++;
    }

    assert(madeChanges);
}


/**
 * @brief Performs a depth-first search (DFS) on the tree rooted at the current node.
 * @brief Executa uma busca em profundidade (DFS) na árvore raizado no nó atual.
 * 
 * @param callback - Function to be called for each node during the DFS.
 * @param callback - Função a ser chamada para cada nó durante a DFS.
 * @param depth - Current depth of the DFS. This value is incremented by 1 for each recursive call.
 * @param depth - Profundidade atual da DFS. Este valor é incrementado em 1 para cada chamada recursiva.
 * 
 * @return void
 */

template<class Data>
void Node<Data>::dfs(function<void(Node<Data>* currentNode, int depth)> callback, int depth){
    callback(this, depth);  // Call the callback function for the current node

    for(Node<Data>* child : children){  // Recursively call dfs on each child node
        child->dfs(callback, depth+1);
    }
}
