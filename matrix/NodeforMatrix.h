#ifndef NODE_FOR_MATRIX_H
#define NODE_FOR_MATRIX_H

#include <QtWidgets>
#include <string>
#include <map>
#include <complex>
#include "Matrix.h"

#define MAXQ 100

class NodeForMatrix;

extern std::map<QString, int> priorityforMatrix;
extern std::map<std::string, MATRIX*> variablesforMatrix;


class NodeForMatrix
{
public:
	virtual ~NodeForMatrix() {}
	// evaluate the node, especially the whole expression tree
	virtual MATRIX eval() = 0;
	// return Element
	virtual QString retElement() = 0;
	// set Element
	virtual void setElement(QString newElement) = 0;

};

class VarNodeForMatrix : public NodeForMatrix
{
	// use dictionary to store variable
	std::string name;
	QString Element;
public:
	VarNodeForMatrix(std::string name) : name(name), Element(QString::fromStdString(name)) {}
	~VarNodeForMatrix() {}

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

class AddNodeForMatrix : public NodeForMatrix
{
	NodeForMatrix *left, *right;
	QString Element;
public:
	AddNodeForMatrix(NodeForMatrix *left, NodeForMatrix *right) : left(left), right(right), 
		Element(QString::fromStdString("+")) {}
	~AddNodeForMatrix();

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

class SubNodeForMatrix : public NodeForMatrix
{
	NodeForMatrix* left, * right;
	QString Element;
public:
	SubNodeForMatrix(NodeForMatrix* left, NodeForMatrix* right) : left(left), right(right),
		Element(QString::fromStdString("-")) {}
	~SubNodeForMatrix();

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

class MutliplyNodeForMatrix : public NodeForMatrix
{
	NodeForMatrix *left, *right;
	QString Element;
public:
	MutliplyNodeForMatrix(NodeForMatrix* left, NodeForMatrix* right) : left(left), right(right),
		Element(QString::fromStdString("*")) {}
	~MutliplyNodeForMatrix();

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

class RightDivNodeForMatrix : public NodeForMatrix
{
	NodeForMatrix* left, * right;
	QString Element;
public:
	RightDivNodeForMatrix(NodeForMatrix* left, NodeForMatrix* right) : left(left), right(right),
		Element(QString::fromStdString("/")) {}
	~RightDivNodeForMatrix();

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

class LeftDivNodeForMatrix : public NodeForMatrix
{
	NodeForMatrix* left, * right;
	QString Element;
public:
	LeftDivNodeForMatrix(NodeForMatrix* left, NodeForMatrix* right) : left(left), right(right),
		Element(QString::fromStdString("\\")) {}
	~LeftDivNodeForMatrix();

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

class TransNodeForMatrix : public NodeForMatrix
{
	NodeForMatrix *child;
	QString Element;
public:
	TransNodeForMatrix(NodeForMatrix* child) : child(child),
		Element(QString::fromStdString("trans")) {}
	~TransNodeForMatrix();

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

class InvNodeForMatrix : public NodeForMatrix
{
	NodeForMatrix *child;
	QString Element;
public:
	InvNodeForMatrix(NodeForMatrix* child) : child(child),
		Element(QString::fromStdString("inv")) {}
	~InvNodeForMatrix();

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

class AdjNodeForMatrix : public NodeForMatrix
{
	NodeForMatrix *child;
	QString Element;
public:
	AdjNodeForMatrix(NodeForMatrix* child) : child(child),
		Element(QString::fromStdString("adj")) {}
	~AdjNodeForMatrix();

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

class DetNodeForMatrix : public NodeForMatrix
{
	NodeForMatrix *child;
	QString Element;
public:
	DetNodeForMatrix(NodeForMatrix* child) : child(child),
		Element(QString::fromStdString("det")) {}
	~DetNodeForMatrix();

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

class TrNodeForMatrix : public NodeForMatrix
{
	NodeForMatrix *child;
	QString Element;
public:
	TrNodeForMatrix(NodeForMatrix* child) : child(child),
		Element(QString::fromStdString("tr")) {}
	~TrNodeForMatrix();

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

// to build ExprTreeForMatrix, with queue sorting NodeForMatrix
class ExprTreeForMatrix
{
public:

	ExprTreeForMatrix() {
		Tree = NULL;
		sizeofQ = 0;
		hasVar = false;
	}

	boolean evaluable() {
		return ~hasVar;
	}

	void enQueue(NodeForMatrix* N); 

	void buildTree();
	NodeForMatrix* createInfix(int leftx, int rightx);

	// for variable, define its value using map 'variables'
	MATRIX evaluate();
	MATRIX eval(NodeForMatrix* N);

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
	NodeForMatrix* Tree;
	NodeForMatrix* Queue[MAXQ];		// infix expression Queue
	int sizeofQ;
};

#endif