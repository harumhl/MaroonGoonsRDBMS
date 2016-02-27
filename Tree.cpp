#include "Tree.h"
#include "Condition.h"
#include "Token.h"
using namespace std;

TreeNode* Tree::buildTree(vector<Token> tokenVec, int& starting) {
    the_root = condition(tokenVec, starting);
    return the_root;
}

// If "||", then make a new node with it as a parent, make the current holding node as its left child, then call conjunction() for its right child
TreeNode* Tree::condition(vector<Token> tokenVec, int& starting) {
    
    TreeNode* left = conjunction(tokenVec, starting);
    
    if (tokenVec.size() <= starting) return left;
    Token t = tokenVec.at(starting++);
    
    while(true) {
        switch(t.getTokenType()) {
            case Token::BOR: // ||
            {
                TreeNode* parent = new TreeNode("||");
                parent->addChild(left);
                left->setParent(parent);
                
                TreeNode* right = conjunction(tokenVec, starting);
                parent->addChild(right);
                right->setParent(parent);

                left = parent;
                t = tokenVec.at(starting++);
                break; // it'll work like continue; b/c of switch stmt
            }
            default:
                starting--; // pushbackToken
                return left;
        }
    }
}
// If "&&", then make a new node with it as a parent, make the current holding node as its left child, then call comparison() for its right child
TreeNode* Tree::conjunction(vector<Token> tokenVec, int& starting) {
    
    TreeNode* left = comparison(tokenVec, starting);
    
    if (tokenVec.size() <= starting) return left;
    Token t = tokenVec.at(starting++);

    while(true) {
        switch(t.getTokenType()) {
            case Token::BAND:
            {
                TreeNode* parent = new TreeNode("&&");
                parent->addChild(left);
                left->setParent(parent);
                
                TreeNode* right = comparison(tokenVec, starting);
                parent->addChild(right);
                right->setParent(parent);
                
                left = parent;
                t = tokenVec.at(starting++);
                break; // it'll work like continue; b/c of switch stmt
            }
            default:
                starting--; // pushbackToken
                return left;
        }
    }
}
// If "(", then call condition() to get the expression inside parentheses and hope the following token is a right parenthesis.
// For other cases, get two more tokens and make a new node as a condition, then return it
TreeNode* Tree::comparison(vector<Token> tokenVec, int& starting) {
    Token t = tokenVec.at(starting++);

    while(true) {
        switch(t.getTokenType()) {
            case Token::LEFTPAREN:
            {
                TreeNode* newCond = condition(tokenVec, starting);
                t = tokenVec.at(starting++);
                
                if (t.getTokenType() != Token::RIGHTPAREN) {
                    cerr << "')' expected" << endl;
                }
                return newCond;
            }
            default:
                Token op = tokenVec.at(starting++);
                Token op2 = tokenVec.at(starting++);

                return new Condition (t.getValue(), op.getValue(), op2.getValue(), true);
        }
    }
}

bool Tree::evalCond(Tuple* tuple, Condition* condition, vector<Attribute*> attributes) {
    
    int att_index = -1;
    bool isInteger = false;
    
    // Finding the index to use for the tuple from attribute list/vector
    for (int i=0; i< attributes.size(); i++) {

        if (toUpper(attributes.at(i)->getName()) == toUpper(condition->getOp1())) {
            att_index = i;
            
            if (attributes.at(i)->getTypeStr() == "INTEGER")
                isInteger = true;
            
            break;
        }
        if (i == attributes.size()-1) {
            cerr << "Looking for wrong attribute name. No condition eval" << endl;
            return false;
        }
    }
    
    string given_content = tuple->getContents().at(att_index);
    string comparing_content = condition->getOp2();
    
    // String comparison (int comparison can be done as well)
    if      (condition->getOp() == "==") return given_content == comparing_content ;
    else if (condition->getOp() == "!=") return given_content != comparing_content ;
    
    if (isInteger) {
        int given_int = -1, comparing_int = -1;
        
        given_int = stoi (given_content); // stoi should work without a problem for both
        comparing_int = stoi (condition->getOp2());

        if      (condition->getOp() == "<")  return given_int < comparing_int ;
        else if (condition->getOp() == "<=") return given_int <= comparing_int ;
        else if (condition->getOp() == ">")  return given_int > comparing_int ;
        else if (condition->getOp() == ">=") return given_int >= comparing_int ;
    }
    else
        cerr << "Given operator is \"Comparable\" when strings are given" << endl;
    
    return false;
}

bool Tree::evalTree(Tuple* tuple, vector<Attribute*> atts, TreeNode* parent) {
    
    if (parent == NULL) parent = the_root;

    TreeNode* current;
    int index = 0; // index for children
    
    if (parent->getChildren().size() == 0) { // current is leaf
        current = parent;

        return evalCond(tuple, (Condition*)current, atts);
    }
    else {
        current = parent->getChild(index); // first child
        
        // leftmost leaf or Node
        bool returned = (current->getIsLeaf())?
            evalCond(tuple, (Condition*)current, atts): evalTree(tuple, atts, current);

        // Rest of the Nodes (which some or all of them can be leaves)
        while(true) {
            // If no more leaf left
            if (index >= parent->children.size()-1) break;
            
            // Check for special occasions: true || ... OR false && ...
            if      (returned==true  && parent->op=="||") return true;
            else if (returned==false && parent->op=="&&") return false;
            
            // evaluate next leaf
            current = parent->getChild(++index);

            bool temp = (current->getIsLeaf())?
                evalCond(tuple, (Condition*)current, atts): evalTree(tuple, atts, current);
            
            // save current condition evaluation result: returned || temp or returned && temp
            if      (parent->op=="||") returned |= temp;
            else if (parent->op=="&&") returned &= temp;
        }
        return returned;
    }
}
string Tree::toUpper (string str) {
    for(int i = 0; i < str.size(); i++) {
        str.at(i) = toupper(str.at(i));
    }
    return str;
}
