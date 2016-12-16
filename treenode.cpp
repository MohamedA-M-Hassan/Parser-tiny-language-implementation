#include "treenode.h"

TreeNode::TreeNode(){root=NULL;left=NULL;right=NULL;center=NULL;}
TreeNode::TreeNode(QString d){root->data=d;left=NULL;right=NULL;center=NULL;}
void TreeNode::setData (QString d){data=d;}
QString TreeNode::getData()    {return data;}
void TreeNode::setRight(TreeNode * r) {right=r;}
TreeNode *TreeNode::getRight(){return right;}
void TreeNode::setCenter(TreeNode * c) {center=c;}
TreeNode *TreeNode::getCenter(){return center;}
void TreeNode::setLeftt(TreeNode * l) {left=l;}
TreeNode *TreeNode::getLeftt(){return left;}
void TreeNode::setLineNo (int d){lineNo=d;}
int TreeNode::getlineNo()    {return line;}
void TreeNode::setRoot(TreeNode * r){root =r;}
TreeNode *TreeNode::getRoot(){return root;}
