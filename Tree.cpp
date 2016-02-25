#include "Token.h"
#include "Condition.h"

#include "Tree.h"
using namespace std;
Token* getNextToken() { return new Token(); }
void pushBackToken(Token* t) {}

bool Tree::isNodeLeaf(TreeNode* node) {
    Condition* c = (Condition*) node; // Forceful casting
    
    // using Condition's function. a Condition object should not have Op1 empty
    if (c->getOp1() == "") return false;
    
    return true;
}
bool Tree::evalCond(Tuple* tuple, Condition* condition, vector<Attribute*> attributes) {
    // 3rd arg: vector<Attribute*> attributes OR Relation* the_relation
    
    int att_index = -1;
    bool isInteger = false;
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
    //cerr<< "GIVEN: " << given_content << "\tCOMPARING: " << comparing_content << endl;
    
    if      (condition->getOp() == "==") return given_content == comparing_content ;
    else if (condition->getOp() == "!=") return given_content != comparing_content ;
    
    if (isInteger) {
        int given_int = -1, comparing_int = -1;
        
        given_int = stoi (given_content);
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


/*
condition   ::= conjunction { || conjunction }
conjunction ::= comparison  { && comparison }
comparison  ::= operand op operand | ( condition )
 */
// BUILD TREE

TreeNode* Tree::buildTree(vector<Token> tokenVec, int& starting) {
    the_root = condition(tokenVec, starting);
    return the_root;
}

TreeNode* Tree::condition(vector<Token> tokenVec, int& starting) {
    // It may not be a function but it may have to be build manually, recursively
    
    TreeNode* left = conjunction(tokenVec, starting);

    if (tokenVec.size() <= starting) {cerr<<"just return"; return left;}
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

                //left |= conjunction(++index); // left || conjunction return value
                t = tokenVec.at(starting++);
                break; // it'll work like continue; b/c of switch stmt
            }
            default:
                starting--; // pushbackToken
                return left;
        }
    }
}
TreeNode* Tree::conjunction(vector<Token> tokenVec, int& starting) {
    
    TreeNode* left = comparison(tokenVec, starting);

    if (tokenVec.size() <= starting) {cerr<<"just return"; return left;}
    Token t = tokenVec.at(starting++); // in token stream class? - the first token is gotten rid from the vector

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
                
                //left |= conjunction(++index); // left || conjunction return value
                t = tokenVec.at(starting++);
                break; // it'll work like continue; b/c of switch stmt
            }
            default:
                starting--; // pushbackToken
                return left;
        }
    }
}
TreeNode* Tree::comparison(vector<Token> tokenVec, int& starting) {
    Token t = tokenVec.at(starting++); // in token stream class? - the first token is gotten rid from the vector

    while(true) {
        switch(t.getTokenType()) {
            case Token::LEFTPAREN:
            {
                TreeNode* newCond = condition(tokenVec, starting);
                t = tokenVec.at(starting++);
                
                if (t.getTokenType() != ')') cerr << "')' expected" << endl;
                return newCond;
            }
/*            case 'o': // operand
            {
                Token* op = getNextToken();
                Token* op2 = getNextToken();
                return new Condition (t.getValue()(), op->getValue(), op2->getValue());
            }*/
            default:
                Token op = tokenVec.at(starting++);
                Token op2 = tokenVec.at(starting++);

                return new Condition (t.getValue(), op.getValue(), op2.getValue());
                /*
                cerr << "Primary expected" << endl;
                return NULL;*/
        }
    }
    
}

bool Tree::evalTree(Tuple* tuple, vector<Attribute*> atts, TreeNode* parent) {
    
    if (parent == NULL) parent = the_root;
    cerr << "ET: " << parent->getOp() << "_" << parent->getChildren().size() << endl;
    TreeNode* current;
    int index = 0; // index for children
    bool isLeaf = false;
    if (parent->getChildren().size() == 0) {
        current = parent;
        isLeaf = true;
        Condition* currCond = (Condition*)current;
        bool returned = (isLeaf)? evalCond(tuple, currCond, atts): evalTree(tuple, atts, current);
        return returned;
    }
    else {
        current = parent->getChild(index); // first child
        isLeaf = isNodeLeaf(current); // True if the child is a leaf
        
        // leftmost leaf or Node
        Condition* currCond = (Condition*)current;
        bool returned = (isLeaf)? evalCond(tuple, currCond, atts): evalTree(tuple, atts, current);

        // Rest of the Nodes (which some or all of them can be leaves)
        while(true) {
            // If no more leaf left
            if (index >= parent->children.size()-1) break;
            
            // Check for special occasions: true || ... OR false && ...
            if      (returned==true  && parent->op=="||") return true;
            else if (returned==false && parent->op=="&&") return false;
            
            // evaluate next leaf
            current = parent->getChild(++index);

            isLeaf = isNodeLeaf(current); // True if the child is a leaf
            Condition* currCond = (Condition*)current;
            bool temp = (isLeaf)? evalCond(tuple, currCond, atts): evalTree(tuple, atts, current);
            
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
