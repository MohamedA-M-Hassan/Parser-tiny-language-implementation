#ifndef TREENODE_H
#define TREENODE_H
#include <QString>

struct TreeNode
{
    QString data;
    struct TreeNode *left;
    struct TreeNode *right;
    struct TreeNode *center;

};
class Tree
{
public:
    Tree();
    void find(QString, TreeNode **, TreeNode **);
    void insert(TreeNode *tree, TreeNode *newnode);
    void del(QString);
    void case_a(TreeNode *,TreeNode *);
    void case_b(TreeNode *,TreeNode *);
    void case_c(TreeNode *,TreeNode *);
    void preorder(TreeNode *);
    void inorder(TreeNode *);
    void postorder(TreeNode *);
    void display(TreeNode *, QString);



private:
    TreeNode * root;


};

#endif // TREENODE_H
