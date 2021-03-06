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
    void setBehind(TreeNode * b);
    TreeNode *getBehind();
    TreeNode* getChildrenByIndex(QVector <TreeNode*> childs , int index);
    // constructor
    TreeNode(QString k,QString v);
    bool getStmt();
    void setStmt(bool s);
    int getPosition();
    void setPosition(int s);

private:
    QString dataKey;
    QString dataValue;
    //TreeNode *left;
    //TreeNode *right;
    QVector <TreeNode*> children;
    int countChildren;
    int lineNo;
    TreeNode *root;
    TreeNode *behind; // stmt behind stmt
    bool stmt;
    int positionFlag; // = 0 -> right ; 1 -> left ; 2-> center

};

#endif // TREENODE_H
