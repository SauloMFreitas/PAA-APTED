#pragma once

#include <vector>
#include <stack>
#include "TreeEditDistance.hpp"
#include "ArrayToString.hpp"

using namespace std;

template<class Data>
class Apted : public TreeEditDistace<Data>{
private:
    static const int LEFT = 0;
    static const int RIGHT = 1;
    static const int INNER = 2;

    vector<vector<float>> delta;

    vector<float> q;
    vector<int> fn;
    vector<int> ft;
    long counter = 0;

    void updateFnArray(int lnForNode, int node, int currentSubtreePreL);

    void updateFtArray(int lnForNode, int node);

    int getStrategyPathType(int pathIDWithPathIDOffset, int pathIDOffset, NodeIndexer<Data>* it, int currentRootNodePreL, int currentSubtreeSize);

    //--------------------------------------------------------------------------

    float spfA(NodeIndexer<Data>* it1, NodeIndexer<Data>* it2, int pathID, int pathType, bool treesSwapped);
    //--------------------------------------------------------------------------

    float spfL(NodeIndexer<Data>* it1, NodeIndexer<Data>* it2, bool treesSwapped);
    
    int computeKeyRoots(NodeIndexer<Data>* it2, int subtreeRootNode, int pathID, vector<int> &keyRoots, int index);

    void treeEditDist(NodeIndexer<Data>* it1, NodeIndexer<Data>* it2, int it1subtree, int it2subtree, vector<vector<float>> &forestdist, bool treesSwapped);
    //--------------------------------------------------------------------------

    float spfR(NodeIndexer<Data>* it1, NodeIndexer<Data>* it2, bool treesSwapped);
    
    int computeRevKeyRoots(NodeIndexer<Data>* it2, int subtreeRootNode, int pathID, vector<int> &revKeyRoots, int index);

    void revTreeEditDist(NodeIndexer<Data>* it1, NodeIndexer<Data>* it2, int it1subtree, int it2subtree, vector<vector<float>> &forestdist, bool treesSwapped);

    //--------------------------------------------------------------------------

    float spf1 (NodeIndexer<Data>* ni1, int subtreeRootNode1, NodeIndexer<Data>* ni2, int subtreeRootNode2);
    //--------------------------------------------------------------------------

    void computeOptStrategy_postL();

    void computeOptStrategy_postR();
    void tedInit();

    //--------------------------------------------------------------------------

    float gted(NodeIndexer<Data>* it1, NodeIndexer<Data>* it2);

public:
    Apted(CostModel<Data>* costModel);

    float computeEditDistance(Node<Data>* t1, Node<Data>* t2);
};