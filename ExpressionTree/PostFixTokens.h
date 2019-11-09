//
//  PostFixTokens.h
//  
//
//  Created by Navar, Eric on 8/22/19.
//

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
using namespace std;

class PostFixTokens {
public:
	PostFixTokens();
	PostFixTokens(vector<string> inFix);
	~PostFixTokens();

	vector<string> getInFixTokens();
	vector<string> getPostFixTokens();
	void setInFixTokens(vector<string> inFix);
	void printPostFix();
	void printInFix();
	void createPostFix();
private:
	bool valid;
	bool postFixMade;
	vector<string> inFixTokens;
	vector<string> postFixTokens;
	bool isValid(vector<string> infix);
	bool isOperator(char s);
	bool isPrecedenceHigher(char lhs, char rhs);
	void processOperator(stack<string> &operators, string op);
};
