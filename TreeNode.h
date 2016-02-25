#ifndef TREENODE_H_
#define TREENODE_H_

#include <vector>
#include <string>
using namespace std;

class TreeNode {
  public:
    TreeNode() {}
    TreeNode(string o, TreeNode* p = NULL): op(o), parent(p) {} // VARARG??
    
    TreeNode* getParent() { return parent; }
    vector<TreeNode*> getChildren() { return children; }
    TreeNode* getChild(int i) { return children.at(i); }
    string getOp() { return op; }
    
    void setParent(TreeNode* p) { parent = p; }
    void setChildren(vector<TreeNode*> c) { children = c; }
    void addChild (TreeNode* c) { children.push_back(c); }
    void setOp(string str) { op = str; }

  // private:
  TreeNode* parent;         // null if root
  vector<TreeNode*> children;
  string op;                // &&, ||
};
#endif
