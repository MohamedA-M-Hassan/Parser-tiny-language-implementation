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
    void setData (QString d){data=d;}
    QString getDta()    {return data;}
    void setRight(TreeNode * r) {right=r;}
    TreeNode *getRight(){return right;}
    void setCenter(TreeNode * c) {center=c;}
    TreeNode *getCenter(){return center;}
    void setLeftt(TreeNode * l) {left=l;}
    TreeNode *getLeftt(){return left;}
private:
    QString data;
    TreeNode *left;
    TreeNode *right;
    TreeNode *center;


};

#endif // TREENODE_H
