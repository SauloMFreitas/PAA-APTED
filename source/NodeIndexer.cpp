#pragma once

#include "../includes/NodeIndexer.hpp"

// --- private methods ---

template<class Data>
int NodeIndexer<Data>::indexNodes(N* node, int postorder) {
    // Initialise variables.
    int currentSize = 0;
    int childrenCount = 0;
    int descSizes = 0;
    int krSizesSum = 0;
    int revkrSizesSum = 0;
    int preorder = preorderTmp;
    int preorderR = 0;
    int currentPreorder = -1;

    preorderTmp++;

    std::vector<N*> childNodes = node->getChildrenAsVector();
    for (size_t i = 0; i < childNodes.size(); i++) {
        childrenCount++;
        currentPreorder = preorderTmp;
        parents[currentPreorder] = preorder;

        postorder = indexNodes(childNodes[i], postorder);
        children[preorder].push_back(currentPreorder);

        currentSize += 1 + sizeTmp;
        descSizes += descSizesTmp;

        if(childrenCount > 1) {
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

    int currentDescSizes = descSizes + currentSize + 1;

    int temp_mul = (currentSize + 1) * (currentSize + 1 + 3);
    if (__builtin_mul_overflow((currentSize + 1), (currentSize + 1 + 3), &temp_mul)) {
        printf("Overflow in %s::%d\n", __FILE__, __LINE__);
        exit(1);
    }

    preL_to_desc_sum[preorder] = (temp_mul) / 2 - currentDescSizes;
    preL_to_kr_sum[preorder] = krSizesSum + currentSize + 1;
    preL_to_rev_kr_sum[preorder] = revkrSizesSum + currentSize + 1;

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
    preL_to_postR[preorder] = treeSize-1-preorder;
    postR_to_preL[treeSize-1-preorder] = preorder;

    return postorder;
}

template<class Data>
void NodeIndexer<Data>::postTraversalIndexing() {
    int currentLeaf = -1;
    int nodeForSum = -1;
    int parentForSum = -1;

    for(int i = 0; i < treeSize; i++) {
        preL_to_ln[i] = currentLeaf;
        if(isLeaf(i)) {
            currentLeaf = i;
        }


        int postl = i; 
        int preorder = postL_to_preL[i];
        if (sizes[preorder] == 1) {
            postL_to_lld[postl] = postl;
        } else {
            postL_to_lld[postl] = postL_to_lld[preL_to_postL[children[preorder][0]]];
        }

        int postr = i;
        preorder = postR_to_preL[postr];
        if (sizes[preorder] == 1) {
            postR_to_rld[postr] = postr;
        } else {
            postR_to_rld[postr] = postR_to_rld[preL_to_postR[children[preorder][children[preorder].size() - 1]]];
        }

        if (sizes[i] == 1) {
            int parent = parents[i];
            if (parent > -1) {
                if (parent+1 == i) {
                    lchl++;
                } else if (preL_to_preR[parent]+1 == preL_to_preR[i]) {
                    rchl++;
                }
            }
        }

        nodeForSum = treeSize - i - 1;
        parentForSum = parents[nodeForSum];
        preL_to_sumDelCost[nodeForSum] += costModel->deleteCost(preL_to_node[nodeForSum]);
        preL_to_sumInsCost[nodeForSum] += costModel->insertCost(preL_to_node[nodeForSum]);
        if (parentForSum > -1) {
            preL_to_sumDelCost[parentForSum] += preL_to_sumDelCost[nodeForSum];
            preL_to_sumInsCost[parentForSum] += preL_to_sumInsCost[nodeForSum];
        }
    }

    currentLeaf = -1;
    for(int i = 0; i < sizes[0]; i++) {
        preR_to_ln[i] = currentLeaf;
        if(isLeaf(preR_to_preL[i])) {
            currentLeaf = i;
        }
    }
}


// --- public Methods ---

template<class Data>
NodeIndexer<Data>::NodeIndexer(N* inputTree, const CostModel<Data>* costModel) : costModel(costModel), treeSize(inputTree->getNodeCount()) {
    // Initialize tmp variables
    currentNode = 0;
    lchl = 0;
    rchl = 0;
    sizeTmp = 0;
    descSizesTmp = 0;
    krSizesSumTmp = 0;
    revkrSizesSumTmp = 0;
    preorderTmp = 0;

    // Initialize indices
    sizes.resize(treeSize, 0);
    children.resize(treeSize);
    parents.resize(treeSize, 0); parents[0] = -1; // Root has no parent

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

    // Index
    indexNodes(inputTree, -1);
    postTraversalIndexing();
}

template<class Data>
int NodeIndexer<Data>::getSize() {
    return treeSize;
}

template<class Data>
int NodeIndexer<Data>::preL_to_lld(int preL) {
    return postL_to_preL[postL_to_lld[preL_to_postL[preL]]];
}

template<class Data>
int NodeIndexer<Data>::preL_to_rld(int preL) {
    return postR_to_preL[postR_to_rld[preL_to_postR[preL]]];
}

template<class Data>
Node<Data>* NodeIndexer<Data>::postL_to_node(int postL) {
    return preL_to_node[postL_to_preL[postL]];
}

template<class Data>
Node<Data>* NodeIndexer<Data>::postR_to_node(int postR) {
    return preL_to_node[postR_to_preL[postR]];
}

template<class Data>
bool NodeIndexer<Data>::isLeaf(int nodeId) {
    return sizes[nodeId] == 1;
}

template<class Data>
int NodeIndexer<Data>::getCurrentNode() const {
    return currentNode;
}

template<class Data>
void NodeIndexer<Data>::setCurrentNode(int preorder) {
    currentNode = preorder;
}