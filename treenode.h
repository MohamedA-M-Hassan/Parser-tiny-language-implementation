#ifndef TREENODE_H
#define TREENODE_H
#include <QString>
#include <QVector>

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
    TreeNode *getLeft();
    void setLineNo (int d);
    int getlineNo();
    void setRoot(TreeNode * r);
    TreeNode *getRoot();
    int getCountChildren();
    QVector <TreeNode*> getChildren();
    void addChildren(TreeNode *t);
private:
    QString data;
    TreeNode *left;
    TreeNode *right;
    //TreeNode *center;
    QVector <TreeNode*> children;
    int countChildren;
    int lineNo;
    TreeNode *root;
};

#endif // TREENODE_H
