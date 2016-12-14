#include "treenode.h"

Tree::Tree()
{
    root = NULL;
}

/*
 * Inserting Element into the Tree
*/
void Tree::insert(TreeNode *tree, TreeNode *newnode)
{
    if (root == NULL)
    {
        root = new TreeNode;
        root->data = newnode->data;
        root->left = NULL;
        root->right = NULL;
        //cout<<"Root Node is Added"<<endl;
        return;
    }
    if (tree->data == newnode->data)
    {
        //cout<<"Element already in the tree"<<endl;
        return;
    }
    if (tree->data > newnode->data)
    {
        if (tree->left != NULL)
        {
            insert(tree->left, newnode);
    }
    else
    {
            tree->left = newnode;
            (tree->left)->left = NULL;
            (tree->left)->right = NULL;
            //cout<<"Node Added To Left"<<endl;
            return;
        }
    }
    else
    {
        if (tree->right != NULL)
        {
            insert(tree->right, newnode);
        }
        else
        {
            tree->right = newnode;
            (tree->right)->left = NULL;
            (tree->right)->right = NULL;
            //cout<<"Node Added To Right"<<endl;
            return;
        }
    }
}

