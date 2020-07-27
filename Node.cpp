#include "Node.h"

typedef enum {
	_add, _sub, _mul, _div, _lg, _log, _ln, _abs, _atan, _acos, _asin, _tan, _cos,
	_sin, _pow, _yroot, _sqrt, _cube, _square, _frac, _Default
} opr;

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


double ConstNode::eval()
{
	return value;
}

Node* ConstNode::derivate(std::string x)
{
	Node* Zero = new ConstNode(0);
	return Zero;
}


double VarNode::eval()
{
	return variables[name];//using dictionary
}

Node* VarNode::derivate(std::string x)
{
	if (name == x)
	{
		Node* Hit = new ConstNode(1);
		return Hit;
	}
	else
	{
		Node* Zero = new ConstNode(0);
		return Zero;
	}
}


AddNode::~AddNode()
{
	delete left;
	delete right;
}

double AddNode::eval()
{
	return left->eval() + right->eval();
}

Node* AddNode::derivate(std::string x)
{
	Node* dlAdr = new AddNode(left->derivate(x), right->derivate(x));
	return dlAdr;
}


MutliplyNode::~MutliplyNode()
{
	delete left;
	delete right;
}

double MutliplyNode::eval()
{
	return left->eval() * right->eval();
}

Node* MutliplyNode::derivate(std::string x)
{
	Node* dlMr = new MutliplyNode(left->derivate(x), right);
	Node* lMdr = new MutliplyNode(left, right->derivate(x));
	Node* dlMrAlMdr = new AddNode(dlMr, lMdr);
	return dlMrAlMdr;
}


SinNode::~SinNode()
{
	delete child;
}

double SinNode::eval()
{
	return sin(child->eval());
}

Node* SinNode::derivate(std::string x)
{
	Node* dfg = new CosNode(child);
	Node* dfgMdg = new MutliplyNode(dfg, child->derivate(x));
	return dfgMdg;
}


CosNode::~CosNode()
{
	delete child;
}

double CosNode::eval()
{
	return cos(child->eval());
}

Node* CosNode::derivate(std::string x)
{
	Node* dfg = new SinNode(child);
	Node* dfgMdg = new MutliplyNode(dfg, child->derivate(x));
	return dfgMdg;
}



void ExprTree::enQueue(Node* N)
{
	Queue[sizeofQ++] = N;
}

Node* ExprTree::createInfix(int leftx, int rightx)
{
	int left = leftx;
	int right = rightx;
	while (!Queue[left]->retElement().compare("(") && !Queue[right]->retElement().compare(")")) {
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
			if (!Queue[i]->retElement().compare("("))
			{
				int j = 1;
				while (Queue[i]->retElement().compare(")") || j)
				{	// brackets matching
					i++;
					if (!Queue[i]->retElement().compare("(")) j++;
					if (!Queue[i]->retElement().compare(")")) j--;
				}
			}
			int pri;
			std::map<QString, int>::iterator iter = priority.find(Queue[i]->retElement());
			if (iter != priority.end()) {
				pri = iter->second;
			}
			else {
				pri = 0;
			}

			if (pri == k) {
				// TODO: complete, and what to compare?
				if (Queue[i]->retElement() == QString::fromStdString("+"))
				{
					Node* root = new AddNode(createInfix(left, i - 1), createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("*"))
				{
					Node* root = new MutliplyNode(createInfix(left, i - 1), createInfix(i + 1, right));
					return root;
				}
				// what to do for unary?
				else if (Queue[i]->retElement() == QString::fromStdString("sin"))
				{
					Node* root = new SinNode(createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("cos"))
				{
					Node* root = new CosNode(createInfix(i + 1, right));
					return root;
				}
				
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

double ExprTree::eval(Node* N)
{
	return N->eval();
}


double ExprTree::evaluate()
{
	// Driving Function
	return eval(this->Tree);
}

double ExprTree::evaluate(double xValue)
{
	variables["x"] = xValue;
	return eval(this->Tree);
}

double ExprTree::evaluate(std::string x, double xValue)
{
	variables[x] = xValue;
	return eval(this->Tree);
}
double ExprTree::evaluate(double xValue, double yValue)
{
	variables["x"] = xValue;
	variables["y"] = yValue;
	return eval(this->Tree);
}

double ExprTree::evaluate(std::string x, double xValue, std::string y, double yValue)
{
	variables[x] = xValue;
	variables[y] = yValue;
	return eval(this->Tree);
}