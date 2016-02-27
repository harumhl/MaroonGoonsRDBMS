#ifndef TREE_H_
#define TREE_H_

#include <iostream>
#include "TreeNode.h"
#include "Condition.h"
#include "Tuple.h"
#include "Attribute.h"
#include "Token.h"
#include "Parser.h"
using namespace std;

class Tree {
    public:
    Tree() {}
  
    TreeNode* buildTree(vector<Token> tokenVec, int& starting);
    TreeNode* condition(vector<Token> tokenVec, int& starting);
    TreeNode* conjunction(vector<Token> tokenVec, int& starting);
    TreeNode* comparison(vector<Token> tokenVec, int& starting);
    
    bool evalCond(Tuple* tuple, Condition* condition, vector<Attribute*> attributes);
    bool evalTree(Tuple* tuple, vector<Attribute*> atts, TreeNode* parent = NULL);
    
    string toUpper (string str);
    
    private:
    TreeNode* the_root;
};

#endif
