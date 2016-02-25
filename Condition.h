#ifndef CONDITION_H_
#define CONDITION_H_

#include "TreeNode.h"
#include <string>

/* Example
      vector<Condition> has three conditions, assuming this format: {preop, op1, op, op2}
      {"", "Years", ">", "3"}, {"||", "Party", "==", "Democrats"}, {"&&", "Town", "!=", "Houston"};
      (Years > 3) || (Party == "Democrats") && (Town != Houston)
      If we want nested, then we can have a vector of vectors of conditions
*/
    
class Condition: public TreeNode {
  public:
    Condition() {}
    Condition(string o1, string o, string o2): operand1(o1), operand2(o2) { TreeNode::setOp(o); }
    
    void setOp1 (string str) { operand1 = str; }
    //void setOp (string str) { op = str; }
    void setOp2 (string str) { operand2 = str; }
    
    string getOp1 () { return operand1; }
    //string getOp () { return op; }
    string getOp2 () { return operand2; }
    
  //private:
    string operand1;  // attribute names in conditions
    //string op;        // ==, !=, <, >, <=, >=
    string operand2;  // values in conditions
};
#endif
