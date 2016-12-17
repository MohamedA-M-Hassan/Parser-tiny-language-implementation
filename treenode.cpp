#include "treenode.h"

TreeNode::TreeNode(){root=NULL;/*left=NULL;right=NULL;*/countChildren=0;behind=NULL;}
TreeNode::TreeNode(QString d){this->dataKey=d;root=NULL;/*left=NULL;right=NULL;*/countChildren=0;behind=NULL;}
void TreeNode::setDataKey (QString d){dataKey=d;}
QString TreeNode::getDataKey(){return dataKey;}
void TreeNode::setDataValue (QString d){dataValue=d;}
QString TreeNode::getDataValue(){return dataValue;}
/*void TreeNode::setRight(TreeNode * r) {right=r;}
TreeNode *TreeNode::getRight(){return right;}
void TreeNode::setLeft(TreeNode * l) {left=l;}
TreeNode *TreeNode::getLeft(){return left;}*/
void TreeNode::setLineNo (int d){lineNo=d;}
int TreeNode::getlineNo()    {return lineNo;}
void TreeNode::setRoot(TreeNode * r){root =r;}
TreeNode *TreeNode::getRoot(){return root;}
int TreeNode::getCountChildren(){return countChildren;}
void TreeNode::addChildren(TreeNode *t){children.push_back(t); countChildren++;}
QVector <TreeNode*> TreeNode::getChildren(){return children;}
void TreeNode::setBehind(TreeNode * b){behind =b;}
TreeNode *TreeNode::getBehind(){return behind;}
