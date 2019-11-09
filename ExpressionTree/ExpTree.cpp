//
//  ExpTree.h
//
//  Created by Navar,Eric on 9/3/19.
//

#include "ExpTree.h"

node::node(string data)
{
	this->data = data;
	right = nullptr;
	left = nullptr;
	isOp = !isalpha(data[0]);
}

node::node(int value)
{
	this->value = value;
	right = nullptr;
	left = nullptr;
	isOp = !isalpha(data[0]) && data != "";
}

ExpTree::ExpTree()
{
	root = nullptr;
}

ExpTree::ExpTree(vector<string> postFix)
{
	CreateTree(postFix);
}

ExpTree::~ExpTree()
{
	deleteChildren(root);
	delete root;
}

//destructor helper. Delete all the children of the node passed in 
void ExpTree::deleteChildren(node* n)
{
	//if it has a left, it also has a right
	if (n->left)
	{
		deleteChildren(n->left);
		delete n->left;
		n->left = nullptr;
		deleteChildren(n->right);
		delete n->right;
		n->right = nullptr;
	}
}

bool ExpTree::isOperator(string token)
{
	return !isalpha(token[0]);
}

//create an expression tree with the given postFix
void ExpTree::CreateTree(vector<string> postFix)
{
	stack<node*> tokens;
	node* temp;
	int size = postFix.size();
	for (int i = 0; i < size; i++)
	{
		temp = new node(postFix.at(i));
		if (isOperator(postFix.at(i)))
		{
			temp->right = tokens.top();
			tokens.pop();
			temp->left = tokens.top();
			tokens.pop();
		}
		tokens.push(temp);
	}

	root = tokens.top();
}

void ExpTree::inOrderTraversalandPrint(ostream &out)
{
	inOrderTraversalandPrintHelper(root, out);
}

//print all values recursively
void ExpTree::inOrderTraversalandPrintHelper(node* theNode, ostream &out)
{
	if (!theNode)
		return;
	inOrderTraversalandPrintHelper(theNode->left, out);
	out << theNode->data << " ";
	inOrderTraversalandPrintHelper(theNode->right, out);
}

void ExpTree::SetVariableValues(vector<int> values)
{
	int operands = countLeaves(root);
	if (values.size() != operands)
		throw invalid_argument("incorrect amount of values");
	SetVariableValuesHelper(root, values);
}

//recursively set the values of the operand nodes in a recursive
void ExpTree::SetVariableValuesHelper(node* theNode, vector<int> &values)
{
	if (theNode->isOp)
	{
		SetVariableValuesHelper(theNode->left, values);
		SetVariableValuesHelper(theNode->right, values);
	}
	else
	{
		theNode->value = values[0];
		values.erase(values.begin());
	}
}

node* ExpTree::getRoot()
{
	return root;
}

int ExpTree::EvaluateTree()
{
	return EvaluateTreeHelper(root);
}

//evaluate the tree recursively
//pass in reference to pointer because we want the tree
//  to be modified between recursive calls
int ExpTree::EvaluateTreeHelper(node *&theNode)
{
	if (theNode->right->isOp)
		EvaluateTreeHelper(theNode->right);
	if (theNode->left->isOp)
		EvaluateTreeHelper(theNode->left);
	calculate(theNode);
	return theNode->value;
}

//this method takes in a pointer to an operator with 2 operand children.
//The result of these 2 operands and operator is calculated and set equal 
//to the value of the operator.
void ExpTree::calculate(node* op)
{
	int left = op->left->value;
	op->left->isOp = isOperator(op->left->data);
	int right = op->right->value;
	op->right->isOp = isOperator(op->right->data);

	int result = 0;
	switch (op->data[0])
	{
	case '^':
		result = pow(left, right);
		break;
	case '*':
		result = left * right;
		break;
	case '/':
		result = left / right;
		break;
	case '+':
		result = left + right;
		break;
	case '-':
		result = left - right;
		break;
	}
	//the operator node now has a value
	op->value = result;
	//The operator node now shouldn't be treated as an operator
	//because it has a value. It will be set to an operator again
	//at the top of this function again in a later call. 
	//If the current node is the root, this later call will never
	//happen so don't set it to operand if it's the root
	op->isOp = (op == root);
}

int ExpTree::countLeaves(node * head)
{
    if (!head)
        return 0;
    else if (!head->right && !head->left)
        return 1;
    else
        return countLeaves(head->right) + countLeaves(head->left);
}