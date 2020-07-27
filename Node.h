#pragma once

#include <QtWidgets>
#include <iostream>
#include <string>
#include <cmath>
#include <map>

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