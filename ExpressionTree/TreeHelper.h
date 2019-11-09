#include "ExpTree.h"

struct TreeHelper
{
	void print2DUtil(node* root, int space, bool show_data);
	// Wrapper over print2DUtil()  
	void print2D(node * root, bool show_value);
	int maxDepth(node * n);
	int countLeaves(node * head);
	int countNodes(node * n);
};