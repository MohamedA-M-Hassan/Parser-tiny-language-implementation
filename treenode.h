#ifndef TREENODE_H
#define TREENODE_H
#include <QString>

class TreeNode
{
public:
    TreeNode();
    /*void find(QString, TreeNode **, TreeNode **);
    void insert(TreeNode *tree, TreeNode *newnode);
    void del(QString);
    void case_a(TreeNode *,TreeNode *);
    void case_b(TreeNode *,TreeNode *);
    void case_c(TreeNode *,TreeNode *);
    void preorder(TreeNode *);
    void inorder(TreeNode *);
    void postorder(TreeNode *);
    void display(TreeNode *, QString);
    */
    void setData (QString d);
    QString getData();
    void setRight(TreeNode * r);
    TreeNode *getRight();
    void setCenter(TreeNode * c);
    TreeNode *getCenter();
    void setLeftt(TreeNode * l);
    TreeNode *getLeftt();
    void setLineNo (int d);
    int getlineNo();

    friend class Tree;
private:
    QString data;
    TreeNode *left;
    TreeNode *right;
    TreeNode *center;
    int lineNo;
};

#endif // TREENODE_H
