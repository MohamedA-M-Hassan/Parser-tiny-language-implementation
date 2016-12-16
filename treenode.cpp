#include "treenode.h"

TreeNode::TreeNode(){root=NULL;left=NULL;right=NULL;countChildren=0;}//center=NULL;}
TreeNode::TreeNode(QString d){root->data=d;left=NULL;right=NULL;countChildren=0;}//center=NULL;}
void TreeNode::setData (QString d){data=d;}
QString TreeNode::getData()    {return data;}
void TreeNode::setRight(TreeNode * r) {right=r;}
TreeNode *TreeNode::getRight(){return right;}
//void TreeNode::setCenter(TreeNode * c) {center=c;}
//TreeNode *TreeNode::getCenter(){return center;}
void TreeNode::setLeft(TreeNode * l) {left=l;}
TreeNode *TreeNode::getLeft(){return left;}
void TreeNode::setLineNo (int d){lineNo=d;}
int TreeNode::getlineNo()    {return lineNo;}
void TreeNode::setRoot(TreeNode * r){root =r;}
TreeNode *TreeNode::getRoot(){return root;}
int TreeNode::getCountChildren(){return countChildren;}
void TreeNode::addChildren(TreeNode *t){children.push_back(t); countChildren++;}
QVector <TreeNode*> TreeNode::getChildren(){return children;}
