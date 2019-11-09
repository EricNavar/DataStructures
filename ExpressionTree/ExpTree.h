//
//  ExpTree.h
//
//  Created by Navar,Eric on 9/3/19.
// 

#ifndef ExpTree_h
#define ExpTree_h

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cmath>
using namespace std;

struct node
{
	string data;
	node* left, *right;
	int value;
	bool isOp;
	node(string data);
	node(int value);
};

class ExpTree {
public:
	ExpTree();
	ExpTree(vector<string> inFix);
	~ExpTree();

	node* getRoot();
	//create an expression tree with the given postFix
	void CreateTree(vector<string> postFix);
	//recursively set the values of the operand nodes
	void SetVariableValues(vector<int> values);
	//recursively traverse the tree and print in InOrder
	void inOrderTraversalandPrint(ostream &out);
	//evaluate the tree recursively
	int EvaluateTree();

private:
	node* root;
	bool isOperator(string token);
	//this method takes in a pointer to an operator with 2 operand children.
	//The result of these 2 operands and operator is calculated and set equal 
	//to the value of the operator. Its children are then deleted
	void calculate(node *ptr);
	//destructor helper. Delete all the children of the node passed in 
	void deleteChildren(node *n);
	void SetVariableValuesHelper(node* theNode, vector<int>& values);
	void inOrderTraversalandPrintHelper(node* theNode, ostream &out);
	int EvaluateTreeHelper(node *&theNode);
	int countLeaves(node * head);
};

#endif /* ExpTree_h */