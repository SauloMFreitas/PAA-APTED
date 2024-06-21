#pragma once

#include"Node.hpp"

template<class Data>
class CostModel
{

    public:
        virtual float del(Node<Data>* n) const = 0;
        virtual float ins(Node<Data>* n) const = 0;
        virtual float ren(Node<Data>* n1, Node<Data>* n2) const = 0;
        

};
