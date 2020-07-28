#pragma once

#include <QtWidgets>
#include <string>
#include <map>
#include <complex>
#include "Matrix.h"

#define MAXQ 100

class Node;

extern std::map<QString, int> priority;
extern std::map<std::string, MATRIX> variables;


class Node
{
public:
	virtual ~Node() = 0;
	// evaluate the node, especially the whole expression tree
	virtual MATRIX eval() = 0;
	// return Element
	virtual QString retElement() = 0;
	// set Element
	virtual void setElement(QString newElement) = 0;

};

class VarNode : public Node
{
	// use dictionary to store variable
	std::string name;
	QString Element;
public:
	VarNode(std::string name) : name(name), Element(QString::fromStdString(name)) {}
	~VarNode() {}

	virtual MATRIX eval() override;

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

	virtual MATRIX eval() override;

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

	virtual MATRIX eval() override;

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

	virtual MATRIX eval() override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};

class RightDivNode : public Node
{
	Node* left, * right;
	QString Element;
public:
	RightDivNode(Node* left, Node* right) : left(left), right(right),
		Element(QString::fromStdString("/")) {}
	~RightDivNode();

	virtual MATRIX eval() override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};

class LeftDivNode : public Node
{
	Node* left, * right;
	QString Element;
public:
	LeftDivNode(Node* left, Node* right) : left(left), right(right),
		Element(QString::fromStdString("\\")) {}
	~LeftDivNode();

	virtual MATRIX eval() override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};

class TransNode : public Node
{
	Node *child;
	QString Element;
public:
	TransNode(Node* child) : child(child),
		Element(QString::fromStdString("trans")) {}
	~TransNode();

	virtual MATRIX eval() override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};

class InvNode : public Node
{
	Node *child;
	QString Element;
public:
	InvNode(Node* child) : child(child),
		Element(QString::fromStdString("inv")) {}
	~InvNode();

	virtual MATRIX eval() override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};

class AdjNode : public Node
{
	Node *child;
	QString Element;
public:
	AdjNode(Node* child) : child(child),
		Element(QString::fromStdString("adj")) {}
	~AdjNode();

	virtual MATRIX eval() override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};

class DetNode : public Node
{
	Node *child;
	QString Element;
public:
	DetNode(Node* child) : child(child),
		Element(QString::fromStdString("det")) {}
	~DetNode();

	virtual MATRIX eval() override;

	QString retElement()
	{
		return Element;
	}
	void setElement(QString newElement)
	{
		Element = newElement;
	}
};

class TrNode : public Node
{
	Node *child;
	QString Element;
public:
	TrNode(Node* child) : child(child),
		Element(QString::fromStdString("tr")) {}
	~TrNode();

	virtual MATRIX eval() override;

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
	MATRIX evaluate();
	MATRIX eval(Node* N);

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
