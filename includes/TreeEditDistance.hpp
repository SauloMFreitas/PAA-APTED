#pragma once

#include "NodeIndexer.hpp"
#include "CostModel.hpp"

typedef pair<int, int> IntPair;

template<class Data>
class TreeEditDistace{
    protected:
        NodeIndexer<Data>* ind1;
        NodeIndexer<Data>* ind2;

        int size1;
        int size2;
        const CostModel<Data>* costModel;

        inline void init(Node<Data>* t1, Node<Data>* t2){
            ind1 = new NodeIndexer<Data>(t1, costModel);
            ind2 = new NodeIndexer<Data>(t2, costModel);

            size1 = ind1->getSize();
            size2 = ind2->getSize();
        }

    public: 
    
        inline TreeEditDistace(CostModel<Data>* costModel): costModel(costModel){
            ind1 = nullptr;
            ind2 = nullptr;
            size1 = -1;
            size2 = -1;
        }

        inline ~TreeEditDistace(){
            delete ind1;
            delete ind2;
        }

        virtual float computeEditDistance(Node<Data>* t1, Node<Data>* t2) = 0;
};
