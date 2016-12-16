#ifndef TREENODE_H
#define TREENODE_H
#include <QString>

class TreeNode
{
public:
    TreeNode();
    TreeNode(QString d);
    void setData (QString d);
    QString getData();
    void setRight(TreeNode * r);
    TreeNode *getRight();
    void setCenter(TreeNode * c);
    TreeNode *getCenter();
    void setLeft(TreeNode * l);
    TreeNode *getLeftt();
    void setLineNo (int d);
    int getlineNo();
    void setRoot(TreeNode * r);
    TreeNode *getRoot();

    friend class Tree;
private:
    QString data;
    TreeNode *left;
    TreeNode *right;
    TreeNode *center;
    int lineNo;
    TreeNode *root;
};

#endif // TREENODE_H
