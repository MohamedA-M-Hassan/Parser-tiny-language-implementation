#ifndef TREENODE_H
#define TREENODE_H
#include <QString>
#include <QVector>

class TreeNode
{
public:
    TreeNode();
    TreeNode(QString d);
    void setDataKey (QString d);
    QString getDataKey();
    void setDataValue (QString d);
    QString getDataValue();
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
    QString dataKey;
    QString dataValue;
    TreeNode *left;
    TreeNode *right;
    QVector <TreeNode*> children;
    int countChildren;
    int lineNo;
    TreeNode *root;
};

#endif // TREENODE_H
