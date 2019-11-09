#include "TreeHelper.h"

void TreeHelper::print2DUtil(node* root, int space, bool show_value)
{
    // Base case  
    if (root == NULL)
        return;

    // Increase distance between levels  
    space += 10;

    // Process right child first  
    print2DUtil(root->right, space, show_value);

    // Print current node after space  
    // count  
    cout << endl;
    for (int i = 10; i < space; i++)
        cout << " ";
    if (!show_value || root->isOp)
        cout << root->data << "\n";
    else
        cout << root->value << "\n";

    // Process left child  
    print2DUtil(root->left, space, show_value);
}

// Wrapper over print2DUtil()  
void TreeHelper::print2D(node * root, bool show_value)
{
    // Pass initial space count as 0 
    print2DUtil(root, 0, show_value);
}

int TreeHelper::maxDepth(node * n)
{
    if (!n)
        return 0;
    int left = 1 + maxDepth(n->left);
    int right = 1 + maxDepth(n->right);
    return (left > right) ? left : right;
}

int TreeHelper::countLeaves(node * head)
{
    if (!head)
        return 0;
    else if (!head->right && !head->left)
        return 1;
    else
        return countLeaves(head->right) + countLeaves(head->left);
}

int TreeHelper::countNodes(node * n)
{
    if (n)
        return 1 + countLeaves(n->right) + countLeaves(n->left);
    else
        return 0;
}