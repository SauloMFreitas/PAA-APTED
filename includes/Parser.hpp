#pragma once

#include "Node.hpp"

template<class Data>
class Parser{
public:
    Parser(){}
    virtual Node<Data>* getRoot() = 0;
};