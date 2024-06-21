#pragma once

#include <list>
#include <vector>
#include <cassert>
#include <algorithm>
#include <functional>

using namespace std;


template<class Data>
class Node
{
private:

// --- private atributes ----
Data* data;
Node<Data>* parent;
list<Node<Data>*> children;
    
public:

// --- public methods ----

    // --- constructors
    Node(Data* data);

    ~Node();

    // --- getters

    Data* getData() const ;

    int getNodecount() const;

    int getNumChildren() const;

    list<Node<Data>*> getChildren() const;
    
    vector<Node<Data>*> getChildrenAsVector() const;

    Node<Data>* getChild(int i) const;

    Node<Data>* getParent();

    // --- setters

    void setParent(Node<Data>* parent);

    void addChild(Node<Data>* child);

    typename list<Node<Data>*>::iterator insertChild(typename list<Node<Data>*>::iterator destIter, Node<Data>* child);

    typename list<Node<Data>*>::iterator getMyIter() const;

    Node<Data>* clone();
    
    void dissociateFromParent();
    
    void replaceChild(Node<Data>* child,Node<Data>* replacement);
    
    void dfs(function<void(Node<Data>* currentNode, int depth)> callback, int depth = 0);

}; 