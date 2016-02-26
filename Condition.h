#ifndef CONDITION_H_
#define CONDITION_H_

#include "TreeNode.h"
#include <string>

/* Example
      Condition object has three ops, assuming this format: {op1, op, op2}
      {"Years", ">", "3"}, {"Party", "==", "Democrats"}, {"Town", "!=", "Houston"};
      (Years > 3) || (Party == "Democrats") && (Town != Houston)
        ->> || and && will be stored in tree nodes (vs Condition objects are leaves in a tree)
*/
    
class Condition: public TreeNode {
  public:
    Condition() {}
    Condition(string o1, string o, string o2): operand1(o1), operand2(o2) { TreeNode::setOp(o); }
    
    void setOp1 (string str) { operand1 = str; }
    void setOp2 (string str) { operand2 = str; }
    
    string getOp1 () { return operand1; }
    string getOp2 () { return operand2; }
    
  //private:
    string operand1;  // attribute names in conditions
    //string op;        // ==, !=, <, >, <=, >=  IT IS INHERITED FROM TREENODE CLASS
    string operand2;  // values in conditions
};
#endif
