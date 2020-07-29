#include "Node.h"

//test
const double EPS = 0.001;
const double PI = 3.1415926;
const double EulerMascheroni = 0.57721566490153286060651209;
QString toStringExpression = "";

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

double Gamma(double c)
{
	std::vector<double> p = { 676.5203681218851,
								-1259.1392167224028,
								771.32342877765313,
								-176.61502916214059,
								12.507343278686905,
								-0.13857109526572012,
								9.9843695780195716e-6,
								1.5056327351493116e-7
	};
	std::complex<double> x, y, z(c, 0), t;
	if (z.real() < 0.5) //Reflection formula
	{
		y = PI / (sin(PI * z) * Gamma(1 - z.real()));
	}
	else
	{
		z -= 1;
		x = 0.99999999999980993;
		int i;
		for (i = 0; i < p.size(); i++)
		{
			x += p[i] / (z + (std::complex < double>)i + (std::complex < double>)1);
			t = z + (std::complex < double>)p.size() - (std::complex < double>)0.5;
			y = sqrt(2 * PI) * pow(t, (z + 0.5)) * exp(-t) * x;
		}

	}

	return y.real();
}


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

SubNode::~SubNode()
{
	delete left;
	delete right;
}

double SubNode::eval()
{
	return left->eval() - right->eval();
}

Node* SubNode::derivate(std::string x)
{
	Node* dlSdr = new SubNode(left->derivate(x), right->derivate(x));
	return dlSdr;
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

DivNode::~DivNode()
{
	delete left;
	delete right;
}

double DivNode::eval()
{
	double r = right->eval();
	if (r == 0)
	{
		throw ARITHMETIC_EXCEPTION();
	}
	else
	{
		return left->eval() / r;
	}
	
}

Node* DivNode::derivate(std::string x)
{
	Node* dlMr = new MutliplyNode(left->derivate(x), right);
	Node* lMdr = new MutliplyNode(left, right->derivate(x));
	Node* dlMrSlMdr = new SubNode(dlMr, lMdr);
	Node* l2 = new MutliplyNode(left, left);
	Node* dDl2 = new DivNode(dlMrSlMdr, l2);
	return dDl2;
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
	Node* mo = new ConstNode(-1);
	Node* mdfg = new SinNode(child);
	Node* dfg = new MutliplyNode(mo, mdfg);
	Node* dfgMdg = new MutliplyNode(dfg, child->derivate(x));
	return dfgMdg;
}


TanNode::~TanNode()
{
	delete child;
}

double TanNode::eval()
{
	return tan(child->eval());
}

Node* TanNode::derivate(std::string x)
{
	Node* c = new CosNode(child);
	Node* c2 = new MutliplyNode(c, c);
	Node* o = new ConstNode(1);
	Node* dfg = new DivNode(o, c);
	Node* dfgMdg = new MutliplyNode(dfg, child->derivate(x));
	return dfgMdg;
}

// arc-
ArcSinNode::~ArcSinNode()
{
	delete child;
}

double ArcSinNode::eval()
{
	return asin(child->eval());
}

Node* ArcSinNode::derivate(std::string x)
{
	Node* x2 = new MutliplyNode(child, child);
	Node* o = new ConstNode(1);
	Node* x21 = new SubNode(o, x2);
	Node* sx21 = new SqrtNode(x21);
	Node* dfg = new DivNode(o, sx21);
	Node* dfgMdg = new MutliplyNode(dfg, child->derivate(x));
	return dfgMdg;
}


ArcCosNode::~ArcCosNode()
{
	delete child;
}

double ArcCosNode::eval()
{
	return acos(child->eval());
}

Node* ArcCosNode::derivate(std::string x)
{
	Node* x2 = new MutliplyNode(child, child);
	Node* o = new ConstNode(1);
	Node* x21 = new SubNode(o, x2);
	Node* sx21 = new SqrtNode(x21);
	Node* mo = new ConstNode(-1);
	Node* dfg = new DivNode(mo, sx21);
	Node* dfgMdg = new MutliplyNode(dfg, child->derivate(x));
	return dfgMdg;
}

ArcTanNode::~ArcTanNode()
{
	delete child;
}

double ArcTanNode::eval()
{
	return atan(child->eval());
}

Node* ArcTanNode::derivate(std::string x)
{
	Node *x2 = new MutliplyNode(child, child);
	Node* o = new ConstNode(1);
	Node* x21 = new AddNode(o, x2);
	Node* dfg = new DivNode(o, x21);
	Node* dfgMdg = new MutliplyNode(dfg, child->derivate(x));
	return dfgMdg;
}


// log
LgNode::~LgNode()
{
	delete child;
}

double LgNode::eval()
{
	double c = child->eval();
	if (c <= 0)
	{
		throw ARITHMETIC_EXCEPTION();
	}
	return log10(c);
}


Node* LgNode::derivate(std::string x)
{
	Node* o = new ConstNode(1 / log(10));
	Node* dfg = new DivNode(o, child);
	Node* dfgMdg = new MutliplyNode(dfg, child->derivate(x));
	return dfgMdg;
}



LnNode::~LnNode()
{
	delete child;
}

double LnNode::eval()
{
	double c = child->eval();
	if (c <= 0)
	{
		throw ARITHMETIC_EXCEPTION();
	}
	return log(c);
}

Node* LnNode::derivate(std::string x)
{
	Node* o = new ConstNode(1 / log(2.718281828));
	Node* dfg = new DivNode(o, child);
	Node* dfgMdg = new MutliplyNode(dfg, child->derivate(x));
	return dfgMdg;
}

LogNode::~LogNode()
{
	delete left;
	delete right;
}

double LogNode::eval()
{
	double r = right->eval(), l = left->eval();
	if (r <= 0 || l <= 0 || l == 1)
	{
		throw ARITHMETIC_EXCEPTION();
	}
	else
	{
		return log(r) / log(l);
	}
}

Node* LogNode::derivate(std::string x)
{
	Node* ll = new LnNode(left);
	Node* lr = new LnNode(right);
	Node* f = new DivNode(ll, lr);
	Node* df = f->derivate(x);
	return df;
}


// power
PowerNode::~PowerNode()
{
	delete left;
	delete right;
}

double PowerNode::eval()
{
	return pow(left->eval(),right->eval());
}

Node* PowerNode::derivate(std::string x)
{
	Node* ll = new LnNode(left);
	Node* llMdr = new MutliplyNode(ll, right->derivate(x));
	Node* rDl = new DivNode(right, left);
	Node* rDlMdl = new MutliplyNode(rDl, left->derivate(x));
	Node* rDlMdlAllMdr = new AddNode(llMdr, rDlMdl);
	Node* df = new MutliplyNode(this, rDlMdlAllMdr);
	return df;
}

TimesRootNode::~TimesRootNode()
{
	delete left;
	delete right;
}

double TimesRootNode::eval()
{
	return pow(1/right->eval(), left->eval());
}

Node* TimesRootNode::derivate(std::string x)
{
	Node* o = new ConstNode(1);
	Node* l1 = new DivNode(o, right);
	Node* l = new LnNode(l1);
	Node* r = left;
	Node* pow = new PowerNode(l, r);//change to power format
	Node* df = pow->derivate(x);
	return df;
}

SqrtNode::~SqrtNode()
{
	delete child;
}

double SqrtNode::eval()
{
	double c = child->eval();
	if (c <= 0)
	{
		throw ARITHMETIC_EXCEPTION();
	}
	return sqrt(c);
}

Node* SqrtNode::derivate(std::string x)
{
	Node* mo = new ConstNode(-1/2);
	Node* dfg = new DivNode(mo, child);
	Node* dfgMdg = new MutliplyNode(dfg, child->derivate(x));
	return dfgMdg;
}

CubeNode::~CubeNode()
{
	delete child;
}

double CubeNode::eval()
{
	return pow(child->eval(), 3);
}

Node* CubeNode::derivate(std::string x)
{
	Node* x2 = new MutliplyNode(child, child);
	Node* o = new ConstNode(3);
	Node* dfg = new MutliplyNode(o, x2);
	Node* dfgMdg = new MutliplyNode(dfg, child->derivate(x));
	return dfgMdg;
}


SquareNode::~SquareNode()
{
	delete child;
}

double SquareNode::eval()
{
	return pow(child->eval(), 2);
}

Node* SquareNode::derivate(std::string x)
{
	Node* o = new ConstNode(2);
	Node* dfg = new MutliplyNode(o, child);
	Node* dfgMdg = new MutliplyNode(dfg, child->derivate(x));
	return dfgMdg;
}


FactNode::~FactNode()
{
	delete child;
}

double FactNode::eval()
{
	double c = child->eval();
	if (c - floor(c) < EPS)
	{
		long long res = 1;
		for (int i = 1; i <= c; i++)
		{
			res *= i;
		}
		return res;
	}
	// Lanczos approximation
	else
	{
		return Gamma(c);
	}
}

Node* FactNode::derivate(std::string x)
{
	// only for positive integer
	double c = child->eval();
	double ik = -EulerMascheroni;
	for (int i = 1; i < c - 1; i++)
	{
		ik += 1 / i;
	}
	Node* df = new ConstNode(Gamma(floor(c)) * ik);
	return df;
}



AbsNode::~AbsNode()
{
	delete child;
}

double AbsNode::eval()
{
	return abs(child->eval());
}

Node* AbsNode::derivate(std::string x)
{
	Node* dfg = new DivNode(this, child);
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
				// Done.TODO: complete, and what to compare?
				if (Queue[i]->retElement() == QString::fromStdString("+"))
				{
					Node* root = new AddNode(createInfix(left, i - 1), createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("-"))
				{
					Node* root = new SubNode(createInfix(left, i - 1), createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("*"))
				{
					Node* root = new MutliplyNode(createInfix(left, i - 1), createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("/"))
				{
					Node* root = new DivNode(createInfix(left, i - 1), createInfix(i + 1, right));
					return root;
				}
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
				else if (Queue[i]->retElement() == QString::fromStdString("tan"))
				{
					Node* root = new TanNode(createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("arcsin"))
				{
					Node* root = new ArcSinNode(createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("arccos"))
				{
					Node* root = new ArcCosNode(createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("arctan"))
				{
					Node* root = new ArcTanNode(createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("lg"))
				{
					Node* root = new LgNode(createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("ln"))
				{
					Node* root = new LnNode(createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("log"))
				{
					Node* root = new LogNode(createInfix(left, i - 1), createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("abs"))
				{
					Node* root = new AbsNode(createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("!"))
				{
					Node* root = new FactNode(createInfix(left, i - 1));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("^"))
				{
					Node* root = new PowerNode(createInfix(left, i - 1), createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("times root"))
				{
					Node* root = new TimesRootNode(createInfix(left, i - 1), createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("sqrt"))
				{
					Node* root = new SqrtNode(createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("^2"))
				{
					Node* root = new SquareNode(createInfix(left, i - 1));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("^3"))
				{
					Node* root = new CubeNode(createInfix(left, i - 1));
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



double Node::eval(double xValue)
{
	variables["x"] = xValue;
	return eval();
}

double Node::eval(std::string x, double xValue)
{
	variables[x] = xValue;
	return eval();
}

double Node::eval(double xValue, double yValue)
{
	variables["x"] = xValue;
	variables["y"] = yValue;
	return eval();
}

double Node::eval(std::string x, double xValue, std::string y, double yValue)
{
	variables[x] = xValue;
	variables[y] = yValue;
	return eval();
}
