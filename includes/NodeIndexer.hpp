#pragma once

#include <vector>
#include <iostream>

#include "ArrayToString.hpp"

using namespace std;

template <class NodeData>
class Apted;

template<class Data>
class NodeIndexer {
private:
    typedef Node<Data> N;

    friend Apted<Data>;

    const CostModel<Data>* costModel;
    const int treeSize;

    // Structure indices
    std::vector<int> sizes;
    std::vector<int> parents;
    std::vector<std::vector<int>> children;

    std::vector<int> postL_to_lld;
    std::vector<int> postR_to_rld;
    std::vector<int> preL_to_ln;
    std::vector<int> preR_to_ln;

    std::vector<N*> preL_to_node;
    std::vector<bool> nodeType_L;
    std::vector<bool> nodeType_R;

    // Traversal translation indices
    std::vector<int> preL_to_preR;
    std::vector<int> preR_to_preL;
    std::vector<int> preL_to_postL;
    std::vector<int> preL_to_postR;
    std::vector<int> postL_to_preL;
    std::vector<int> postR_to_preL;

    // Cost indices
    std::vector<int> preL_to_kr_sum;
    std::vector<int> preL_to_rev_kr_sum;
    std::vector<int> preL_to_desc_sum;
    std::vector<float> preL_to_sumDelCost;
    std::vector<float> preL_to_sumInsCost;

    // Temp variables
    int currentNode;
    int lchl;
    int rchl;
    int sizeTmp;
    int descSizesTmp;
    int krSizesSumTmp;
    int revkrSizesSumTmp;
    int preorderTmp;

    int indexNodes(N* node, int postorder);

    void postTraversalIndexing();
public:
    NodeIndexer(N* inputTree, const CostModel<Data>* costModel);

    int getSize();

    int preL_to_lld(int preL);

    int preL_to_rld(int preL);

    Node<Data>* postL_to_node(int postL);

    Node<Data>* postR_to_node(int postR);

    bool isLeaf(int nodeId);

    int getCurrentNode() const;

    void setCurrentNode(int preorder);

};