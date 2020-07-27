#pragma once

#include <QtWidgets>
#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <complex>

#define MAXQ 100

class Node;

extern std::map<QString, int> priority;
extern std::map<std::string, int> variables;


class Node
{
public:
	// evaluate the node, especially the whole expression tree
	virtual double eval() = 0;
	// logic derivation, may return ConstNode(0)
	virtual Node* derivate(std::string x) = 0;
	// return Element
	virtual QString retElement() = 0;
	// set Element
	virtual void setElement(QString newElement) = 0;

};


class ConstNode : public Node
{
	double value;
	QString Element;
public:
	ConstNode(double value) : value(value), Element(QString::number(value)) {}
	~ConstNode() {}

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};

class VarNode : public Node
{
	// use dictionary to store variable
	std::string name;
	QString Element;
public:
	VarNode(std::string name) : name(name), Element(QString::fromStdString(name)) {}
	~VarNode() {}

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};

class AddNode : public Node
{
	Node *left, *right;
	QString Element;
public:
	AddNode(Node *left, Node *right) : left(left), right(right), 
		Element(QString::fromStdString("+")) {}
	~AddNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};

class SubNode : public Node
{
	Node* left, * right;
	QString Element;
public:
	SubNode(Node* left, Node* right) : left(left), right(right),
		Element(QString::fromStdString("-")) {}
	~SubNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};

class MutliplyNode : public Node
{
	Node *left, *right;
	QString Element;
public:
	MutliplyNode(Node* left, Node* right) : left(left), right(right),
		Element(QString::fromStdString("*")) {}
	~MutliplyNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};

class DivNode : public Node
{
	Node* left, * right;
	QString Element;
public:
	DivNode(Node* left, Node* right) : left(left), right(right),
		Element(QString::fromStdString("/")) {}
	~DivNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};

class SinNode : public Node
{
	Node *child;
	QString Element;
public:
	SinNode(Node* child) : child(child),
		Element(QString::fromStdString("sin")) {}
	~SinNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};


class CosNode : public Node
{
	Node* child;
	QString Element;
public:
	CosNode(Node *child) : child(child),
		Element(QString::fromStdString("cos")) {}
	~CosNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};


class TanNode : public Node
{
	Node* child;
	QString Element;
public:
	TanNode(Node* child) : child(child),
		Element(QString::fromStdString("tan")) {}
	~TanNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};


class ArcSinNode : public Node
{
	Node* child;
	QString Element;
public:
	ArcSinNode(Node* child) : child(child),
		Element(QString::fromStdString("arcsin")) {}
	~ArcSinNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};


class ArcCosNode : public Node
{
	Node* child;
	QString Element;
public:
	ArcCosNode(Node* child) : child(child),
		Element(QString::fromStdString("arccos")) {}
	~ArcCosNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};



class ArcTanNode : public Node
{
	Node* child;
	QString Element;
public:
	ArcTanNode(Node* child) : child(child),
		Element(QString::fromStdString("arctan")) {}
	~ArcTanNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};


class LgNode : public Node
{
	Node* child;
	QString Element;
public:
	LgNode(Node* child) : child(child),
		Element(QString::fromStdString("lg")) {}
	~LgNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};

class LnNode : public Node
{
	Node* child;
	QString Element;
public:
	LnNode(Node* child) : child(child),
		Element(QString::fromStdString("ln")) {}
	~LnNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};

class LogNode : public Node
{
	Node* left, *right;
	QString Element;
public:
	LogNode(Node* left, Node* right) : left(left), right(right),
		Element(QString::fromStdString("based log")) {}
	~LogNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};


class PowerNode : public Node
{
	Node* left, * right;
	QString Element;
public:
	PowerNode(Node* left, Node* right) : left(left), right(right),
		Element(QString::fromStdString("^")) {}
	~PowerNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};

class TimesRootNode : public Node
{
	Node* left, * right;
	QString Element;
public:
	TimesRootNode(Node* left, Node* right) : left(left), right(right),
		Element(QString::fromStdString("times root")) {}
	~TimesRootNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};

class SqrtNode : public Node
{
	Node* child;
	QString Element;
public:
	SqrtNode(Node* child) : child(child),
		Element(QString::fromStdString("sqrt")) {}
	~SqrtNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};

class SquareNode : public Node
{
	Node* child;
	QString Element;
public:
	SquareNode(Node* child) : child(child),
		Element(QString::fromStdString("^2")) {}
	~SquareNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};

class CubeNode : public Node
{
	Node* child;
	QString Element;
public:
	CubeNode(Node* child) : child(child),
		Element(QString::fromStdString("^3")) {}
	~CubeNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};

class FactNode : public Node
{
	Node* child;
	QString Element;
public:
	FactNode(Node* child) : child(child),
		Element(QString::fromStdString("!")) {}
	~FactNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};

class AbsNode : public Node
{
	Node* child;
	QString Element;
public:
	AbsNode(Node* child) : child(child),
		Element(QString::fromStdString("abs")) {}
	~AbsNode();

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
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