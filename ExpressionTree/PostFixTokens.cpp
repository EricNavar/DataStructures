#include "PostFixTokens.h"

PostFixTokens::PostFixTokens()
{
	postFixMade = false;
	valid = false;
}

PostFixTokens::PostFixTokens(vector<string> inFix)
{
	postFixMade = false;
	inFixTokens = inFix;
	valid = isValid(inFix);
}

PostFixTokens::~PostFixTokens()
{ }

vector<string> PostFixTokens::getPostFixTokens()
{
	if (!valid)
		throw invalid_argument("invalid inFix");
	return postFixTokens;
}

vector<string> PostFixTokens::getInFixTokens()
{
	return inFixTokens;
}

void PostFixTokens::setInFixTokens(vector<string> inFix)
{
	inFixTokens = inFix;
	valid = isValid(inFix);
}

//The infix has to be valid. Meaning that ignoring the parentheses,
//the infix should start at an operand and alternate between operand
//and operator. The final token should be an operand.
//Also there must be as many opening parentheses as there are closing
//parentheses and the first paretheses can't be closing and the last
//one can't be opening.
bool PostFixTokens::isValid(vector<string> infix)
{
	bool lookingForOperand = true, is_operator;
	//openingPar is true iff there has been an opening parentheses iterated over
	//lastParClose is true iff the last parentheses to be iterated over was closed
	bool openingPar = false, lastParClose = false;
	int openPar = 0, closePar = 0;
	for (string s : infix)
	{
		is_operator = isOperator(s[0]);
		if (s == "(")
		{
			lastParClose = false;
			openingPar = true;
			openPar++;
		}
		else if (s == ")")
		{
			if (!openingPar)
				return false;
			lastParClose = true;
			closePar++;
		}
		else if (lookingForOperand)
		{
			if (is_operator)
				return false;
			lookingForOperand = false;
		}
		else//looking for Operator
		{
			if (!is_operator)
				return false;
			lookingForOperand = true;
		}
	}

	return !lookingForOperand && openPar == closePar && (!openPar > 0 || lastParClose);
}

void PostFixTokens::printPostFix()
{
	if (!valid)
		throw invalid_argument("invalid inFix");
	for (string s : postFixTokens)
		cout << s << " ";
}

void PostFixTokens::printInFix()
{
	for (string s : inFixTokens)
		cout << s << " ";
}

void PostFixTokens::createPostFix()
{
	if (!valid)
		throw invalid_argument("invalid inFix");
	if (postFixMade)
		cout << "PostFix already created" << endl;
	stack<string> operators;
	int size = inFixTokens.size();
	string currentToken;

	for (int i = 0; i < size; i++)
	{
		currentToken = inFixTokens.at(i);

		if (isOperator(currentToken[0]))
			processOperator(operators, currentToken);
		else if (currentToken == "(")
			operators.push(currentToken);
		else if (currentToken == ")")
		{
			while (operators.top() != "(")
			{
				postFixTokens.push_back(operators.top());
				operators.pop();
			}
			operators.pop();
		}
		else //if token is operand
			postFixTokens.push_back(currentToken);
	}

	while (!operators.empty())
	{
		postFixTokens.push_back(operators.top());
		operators.pop();
	}
	postFixMade = true;
}

//helper function for createPostFix()
void PostFixTokens::processOperator(stack<string> & operators, string op)
{
	string topOp;
	if (operators.empty())
	{
		operators.push(op);
		return;
	}
	else
	{
		topOp = operators.top();
	}

	if (op == topOp && op == "^")
		operators.push(op);
	else if (isPrecedenceHigher(op[0], topOp[0]))
		operators.push(op);
	else
	{
		while (!(operators.empty() || isPrecedenceHigher(op[0], topOp[0]) || op == "^" && topOp == "^"))
		{
			topOp = operators.top();
			postFixTokens.push_back(topOp);
			operators.pop();
		}
		operators.push(op);
	}
}

//parentheses are not operators even though they are literally the first item in PEMDAS
bool PostFixTokens::isOperator(char c)
{
	return c == '^' || c == '*' || c == '/' || c == '+' || c == '-';
}

bool PostFixTokens::isPrecedenceHigher(char lhs, char rhs)
{
	//cute little map
	map<char, int> order = {
				{ '^', 3 },
				{ '*', 2 },
				{ '/', 2 },
				{ '+', 1 },
				{ '-', 1 },
				{ '(', 0 },
				{ ')', 0 } };
	return order.at(lhs) > order.at(rhs);
}
