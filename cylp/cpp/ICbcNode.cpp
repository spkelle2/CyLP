#include "ICbcNode.hpp"
#include "CbcNode.hpp"

bool ICbcNode::breakTie(ICbcNode* y){
    ICbcNode* x = this;
    assert (x);
    assert (y);
      return (x->nodeNumber()>y->nodeNumber());
}

// make a default constructor so we can create a custom one below
ICbcNode::ICbcNode():CbcNode(){
}

// make an ICbcNode from a copy of an existing CbcNode
ICbcNode::ICbcNode(CbcNode* n):CbcNode(*n){
}
