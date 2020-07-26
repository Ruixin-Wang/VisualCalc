#include "ExprTree.h"
#include <map>
#include <math.h>

typedef enum {_add, _sub, _mul, _div, _lg, _log, _ln, _abs, _atan, _acos, _asin, _tan, _cos, 
			  _sin, _pow, _yroot, _sqrt, _cube, _square, _frac, _Default} opr;

std::map<QString, int> priority = {
	{"+", 1}, {"-", 1}, 
	{"*", 2}, {"/", 2},
	
	{"lg", 3}, {"based log", 3},
	{"abs", 3}, {"arctan", 3},
	{"arccos", 3}, {"arcsin", 3},
	{"tan", 3}, {"cos", 3},
	{"sin", 3}, {"ln", 3},

	{"^", 4,}, {"times root", 4}, {"sqrt", 4},
	{"^3", 4}, {"^2", 4}, {"!", 4},
};

std::map<QString, opr> oprtype = {
	{"+", _add}, {"-", _sub},
	{"*", _mul}, {"/", _div},

	{"lg", _lg}, {"based log", _log},
	{"abs", _abs}, {"arctan", _atan},
	{"arccos", _acos}, {"arcsin", _asin},
	{"tan", _tan}, {"cos", _cos},
	{"sin", _sin}, {"ln", _ln},

	{"^", _pow}, {"times root", _yroot}, {"sqrt", _sqrt},
	{"^3", _cube}, {"^2", _square}, {"!", _frac},
};

void ExprTree::enQueue(Node* N)
{
	Queue[sizeofQ++] = N;
}

Node* ExprTree::createInfix(int leftx, int rightx)
{
	int left = leftx;
	int right = rightx;
	while (!Queue[left]->Element.compare("(") && !Queue[right]->Element.compare(")")) {
		left++;
		right--;
	}


	if (left == right)
	{
		return Queue[left];
	}
	if (left > right)
	{
		return NULL;
	}
	

	for (int k = 1; k <= 4; k++) {

		int i = left;
		while (i <= right) {
			if (!Queue[i]->Element.compare("("))
			{
				int j = 1;
				while (Queue[i]->Element.compare(")") || j)
				{	// brackets matching
					i++;
					if (!Queue[i]->Element.compare("(")) j++;
					if (!Queue[i]->Element.compare(")")) j--;
				}
			}
			int pri;
			std::map<QString, int>::iterator iter = priority.find(Queue[i]->Element);
			if (iter != priority.end()) {
				pri = iter->second;
			}
			else {
				pri = 0;
			}

			if (pri == k) {
				Queue[i]->LChild = createInfix(left, i - 1);
				Queue[i]->RChild = createInfix(i + 1, right);
				return Queue[i];
			}
			i++;
		}
	}
}

void ExprTree::buildTree()
{
	// Driving Function
	Tree = createInfix(0, sizeofQ - 1);
}

double ExprTree::eval(Node* N, double x)
{
	if (N->type == Const) return (N->Element.toDouble());
	if (N->type == Var) return x;


	opr opr_type;
	std::map<QString, opr>::iterator iter = oprtype.find(N->Element);
	if (iter != oprtype.end()) {
		opr_type = iter->second;
	}
	else {
		opr_type = _Default;
	}

	switch (opr_type) {
	case _add: {
		return eval(N->LChild, x) + eval(N->RChild, x);
		break;
	}
	case _sub: {
		return eval(N->LChild, x) - eval(N->RChild, x);
		break;
	}
	case _mul: {
		return eval(N->LChild, x) * eval(N->RChild, x);
		break;
	}
	case _div: {
		return eval(N->LChild, x) / eval(N->RChild, x);
		break;
	}
	case _lg: {
		return log10(eval(N->RChild, x));
		break;
	}
	case _log: {
		return log(eval(N->RChild, x)) / log(eval(N->LChild, x));
		break;
	}
	case _ln: {
		return log(eval(N->RChild, x));
		break;
	}
	case _abs: {
		return abs(eval(N->RChild, x));
		break;
	}
	case _atan: {
		return atan(eval(N->RChild, x));
		break;
	}
	case _acos: {
		return acos(eval(N->RChild, x));
		break;
	}
	case _asin: {
		return asin(eval(N->RChild, x));
		break;
	}
	case _tan: {
		return tan(eval(N->RChild, x));
		break;
	}
	case _cos: {
		return cos(eval(N->RChild, x));
		break;
	}
	case _sin: {
		return sin(eval(N->RChild, x));
		break;
	}
	case _pow: {
		return pow((eval(N->LChild, x)), (eval(N->RChild, x)));
		break;
	}
	case _yroot: {
		return pow((eval(N->LChild, x)), 1.0 / (eval(N->RChild, x)));
		break;
	}
	case _sqrt: {
		return sqrt(eval(N->RChild, x));
		break;
	}
	case _cube: {
		return pow((eval(N->LChild, x)), 3.0);
		break;
	}
	case _square: {
		return pow((eval(N->LChild, x)), 2.0);
		break;
	}
	case _frac: {

	}

	}

}


double ExprTree::evaluate(double x)
{
	// Driving Function
	return eval(this->Tree, x);
}