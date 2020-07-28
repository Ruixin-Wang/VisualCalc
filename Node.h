#pragma once

#include <QtWidgets>
#include <exception>
#include <string>
#include <cmath>
#include <map>
#include <complex>

#define MAXQ 100

class Node;

extern std::map<QString, int> priority;
extern std::map<std::string, int> variables;
extern QString toStringExpression;

struct ARITHMETIC_EXCEPTION : public std::exception
{
	const char* what() const throw () {
		return "Divisor cannot be zero, radicand must bigger than zero!";
	}
};

struct NUMBER_FORMAT_EXCEPTION : public std::exception
{
	const char* what() const throw () {
		return "Evaluate with unknown variables!";
	}
};

struct NULL_POINTER_EXCEPTION : public std::exception
{
	const char* what() const throw () {
		return "Illgeal expression!";
	}
};



class Node
{
	QString Element;
public:
	// evaluate the node, especially the whole expression tree
	virtual double eval() = 0;
	double eval(double xValue);
	double eval(std::string x, double xValue);
	double eval(double xValue, double yValue);
	double eval(std::string x, double xValue, std::string y, double yValue);
	// logic derivation, may return ConstNode(0)
	virtual Node* derivate(std::string x) = 0;
	// to expression string version
	virtual void toString() = 0;
	// return Element
	QString retElement()
	{
		return Element;
	}
	// set Element
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};


class ConstNode : public Node
{
	double value;
	QString Element;
public:
	ConstNode(double value) : value(value)
	{
		setElement(QString::number(value));
	}
	~ConstNode() {}

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override
	{
		toStringExpression.append(QString::number(value));
	}
};

class VarNode : public Node
{
	// use dictionary to store variable
	std::string name;
	QString Element;
public:
	VarNode(std::string name) : name(name)
	{
		setElement(QString::fromStdString(name));
	}
	~VarNode() {}

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override
	{
		toStringExpression.append(QString::fromStdString(name));
	}
};

class AddNode : public Node
{
	Node *left, *right;
	QString Element;
public:
	AddNode(Node *left, Node *right) : left(left), right(right)
	{
		setElement(QString::fromStdString("+"));
	}
	~AddNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override
	{
		toStringExpression.append(QString::fromStdString("("));
		left->toString();
		toStringExpression.append(QString::fromStdString(")"));
		toStringExpression.append(retElement());
		toStringExpression.append(QString::fromStdString("("));
		right->toString();
		toStringExpression.append(QString::fromStdString(")"));
	}
};

class SubNode : public Node
{
	Node* left, * right;
	QString Element;
public:
	SubNode(Node* left, Node* right) : left(left), right(right)
	{
		setElement(QString::fromStdString("-"));
	}
	~SubNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override
	{
		toStringExpression.append(QString::fromStdString("("));
		left->toString();
		toStringExpression.append(QString::fromStdString(")"));
		toStringExpression.append(retElement());
		toStringExpression.append(QString::fromStdString("("));
		right->toString();
		toStringExpression.append(QString::fromStdString(")"));
	}
};

class MutliplyNode : public Node
{
	Node *left, *right;
	QString Element;
public:
	MutliplyNode(Node* left, Node* right) : left(left), right(right)
	{
		setElement(QString::fromStdString("*"));
	}
	~MutliplyNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override
	{
		toStringExpression.append(QString::fromStdString("("));
		left->toString();
		toStringExpression.append(QString::fromStdString(")"));
		toStringExpression.append(retElement());
		toStringExpression.append(QString::fromStdString("("));
		right->toString();
		toStringExpression.append(QString::fromStdString(")"));
	}
};

class DivNode : public Node
{
	Node* left, * right;
	QString Element;
public:
	DivNode(Node* left, Node* right) : left(left), right(right)
	{
		setElement(QString::fromStdString("/"));
	}
	~DivNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override
	{
		toStringExpression.append(QString::fromStdString("("));
		left->toString();
		toStringExpression.append(QString::fromStdString(")"));
		toStringExpression.append(retElement());
		toStringExpression.append(QString::fromStdString("("));
		right->toString();
		toStringExpression.append(QString::fromStdString(")"));
	}
};

class SinNode : public Node
{
	Node *child;
	QString Element;
public:
	SinNode(Node* child) : child(child)
	{
		setElement(QString::fromStdString("sin"));
	}
	~SinNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override
	{
		toStringExpression.append(retElement());
		toStringExpression.append(QString::fromStdString("("));
		child->toString();
		toStringExpression.append(QString::fromStdString(")"));
	}
};


class CosNode : public Node
{
	Node* child;
	QString Element;
public:
	CosNode(Node *child) : child(child)
	{
		setElement(QString::fromStdString("cos"));
	}
	~CosNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override
	{
		toStringExpression.append(retElement());
		toStringExpression.append(QString::fromStdString("("));
		child->toString();
		toStringExpression.append(QString::fromStdString(")"));
	}
};


class TanNode : public Node
{
	Node* child;
	QString Element;
public:
	TanNode(Node* child) : child(child)
	{
		setElement(QString::fromStdString("tan"));
	}
	~TanNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override
	{
		toStringExpression.append(retElement());
		toStringExpression.append(QString::fromStdString("("));
		child->toString();
		toStringExpression.append(QString::fromStdString(")"));
	}
};


class ArcSinNode : public Node
{
	Node* child;
	QString Element;
public:
	ArcSinNode(Node* child) : child(child)
	{
		setElement(QString::fromStdString("arcsin"));
	}
	~ArcSinNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override
	{
		toStringExpression.append(retElement());
		toStringExpression.append(QString::fromStdString("("));
		child->toString();
		toStringExpression.append(QString::fromStdString(")"));
	}
};


class ArcCosNode : public Node
{
	Node* child;
	QString Element;
public:
	ArcCosNode(Node* child) : child(child)
	{
		setElement(QString::fromStdString("arccos"));
	}
	~ArcCosNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override
	{
		toStringExpression.append(retElement());
		toStringExpression.append(QString::fromStdString("("));
		child->toString();
		toStringExpression.append(QString::fromStdString(")"));
	}
};



class ArcTanNode : public Node
{
	Node* child;
	QString Element;
public:
	ArcTanNode(Node* child) : child(child)
	{
		setElement(QString::fromStdString("arctan"));
	}
	~ArcTanNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override
	{
		toStringExpression.append(retElement());
		toStringExpression.append(QString::fromStdString("("));
		child->toString();
		toStringExpression.append(QString::fromStdString(")"));
	}
};


class LgNode : public Node
{
	Node* child;
	QString Element;
public:
	LgNode(Node* child) : child(child)
	{
		setElement(QString::fromStdString("lg"));
	}
	~LgNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override
	{
		toStringExpression.append(retElement());
		toStringExpression.append(QString::fromStdString("("));
		child->toString();
		toStringExpression.append(QString::fromStdString(")"));
	}
};

class LnNode : public Node
{
	Node* child;
	QString Element;
public:
	LnNode(Node* child) : child(child)
	{
		setElement(QString::fromStdString("ln"));
	}
	~LnNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override
	{
		toStringExpression.append(retElement());
		toStringExpression.append(QString::fromStdString("("));
		child->toString();
		toStringExpression.append(QString::fromStdString(")"));
	}
};

class LogNode : public Node
{
	Node* left, *right;
	QString Element;
public:
	LogNode(Node* left, Node* right) : left(left), right(right)
	{
		setElement(QString::fromStdString("based log"));
	}
	~LogNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override
	{
		toStringExpression.append(QString::fromStdString("("));
		left->toString();
		toStringExpression.append(QString::fromStdString(")"));
		toStringExpression.append(retElement());
		toStringExpression.append(QString::fromStdString("("));
		right->toString();
		toStringExpression.append(QString::fromStdString(")"));
	}
};


class PowerNode : public Node
{
	Node* left, * right;
	QString Element;
public:
	PowerNode(Node* left, Node* right) : left(left), right(right)
	{
		setElement(QString::fromStdString("^"));
	}
	~PowerNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override
	{
		toStringExpression.append(QString::fromStdString("("));
		left->toString();
		toStringExpression.append(QString::fromStdString(")"));
		toStringExpression.append(retElement());
		toStringExpression.append(QString::fromStdString("("));
		right->toString();
		toStringExpression.append(QString::fromStdString(")"));
	}
};

class TimesRootNode : public Node
{
	Node* left, * right;
	QString Element;
public:
	TimesRootNode(Node* left, Node* right) : left(left), right(right)
	{
		setElement(QString::fromStdString("times root"));
	}
	~TimesRootNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override
	{
		toStringExpression.append(QString::fromStdString("("));
		left->toString();
		toStringExpression.append(QString::fromStdString(")"));
		toStringExpression.append(retElement());
		toStringExpression.append(QString::fromStdString("("));
		right->toString();
		toStringExpression.append(QString::fromStdString(")"));
	}
};

class SqrtNode : public Node
{
	Node* child;
	QString Element;
public:
	SqrtNode(Node* child) : child(child)
	{
		setElement(QString::fromStdString("sqrt"));
	}
	~SqrtNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override
	{
		toStringExpression.append(retElement());
		toStringExpression.append(QString::fromStdString("("));
		child->toString();
		toStringExpression.append(QString::fromStdString(")"));
	}
};

class SquareNode : public Node
{
	Node* child;
	QString Element;
public:
	SquareNode(Node* child) : child(child)
	{
		setElement(QString::fromStdString("^2"));
	}
	~SquareNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override
	{
		toStringExpression.append(retElement());
		toStringExpression.append(QString::fromStdString("("));
		child->toString();
		toStringExpression.append(QString::fromStdString(")"));
	}
};

class CubeNode : public Node
{
	Node* child;
	QString Element;
public:
	CubeNode(Node* child) : child(child)
	{
		setElement(QString::fromStdString("^3"));
	}
	~CubeNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override
	{
		toStringExpression.append(retElement());
		toStringExpression.append(QString::fromStdString("("));
		child->toString();
		toStringExpression.append(QString::fromStdString(")"));
	}
};

class FactNode : public Node
{
	Node* child;
	QString Element;
public:
	FactNode(Node* child) : child(child)
	{
		setElement(QString::fromStdString("!"));
	}
	~FactNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override
	{
		toStringExpression.append(retElement());
		toStringExpression.append(QString::fromStdString("("));
		child->toString();
		toStringExpression.append(QString::fromStdString(")"));
	}
};

class AbsNode : public Node
{
	Node* child;
	QString Element;
public:
	AbsNode(Node* child) : child(child)
	{
		setElement(QString::fromStdString("abs"));
	}
	~AbsNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override
	{
		toStringExpression.append(retElement());
		toStringExpression.append(QString::fromStdString("("));
		child->toString();
		toStringExpression.append(QString::fromStdString(")"));
	}
};






// to build ExprTree, with queue sorting Node
class ExprTree
{
public:

	ExprTree() {
		Tree = NULL;
		sizeofQ = 0;
		hasVar = false;
	}

	boolean evaluable() {
		return ~hasVar;
	}

	void enQueue(Node* N);

	void buildTree();
	Node* createInfix(int leftx, int rightx);

	// for variable, define its value using map 'variables'
	double evaluate();
	double evaluate(double xValue);
	double evaluate(std::string x, double xValue);
	double evaluate(double xValue, double yValue);
	double evaluate(std::string x, double xValue, std::string y, double yValue);
	double eval(Node* N);

	Node* derivate(std::string x)
	{
		return Tree->derivate(x);
	}

	inline int getSizeofQ()
	{
		return sizeofQ;
	}

	inline void clear()
	{
		sizeofQ = 0;
		Queue[0]->setElement("");
	}

	inline void del()
	{
		sizeofQ--;
	}

	inline QString renewExpr()
	{
		QString Expr = "";
		for (int i = 0; i < sizeofQ; i++) Expr += (Queue[i]->retElement() + " ");
		return Expr;
	}




private:
	boolean hasVar;
	Node* Tree;
	Node* Queue[MAXQ];		// infix expression Queue
	int sizeofQ;
};