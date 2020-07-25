#pragma once

#include <QtWidgets>

#define MAXQ 100

enum {Const, Var, Operator};

struct Node {
	Node* LChild, * RChild;
	QString Element;
	int type;
};

extern std::map<QString, int> priority;

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

	double evaluate();
	double evaluate(double x);

	inline int getSizeofQ()
	{
		return sizeofQ;
	}

	inline QString renewExpr()
	{
		QString Expr = "";
		for (int i = 0; i < sizeofQ; i++) Expr += (Queue[i]->Element + " ");
		return Expr;
	}




private:
	boolean hasVar;
	struct Node* Tree;
	struct Node* Queue[MAXQ];		// infix expression Queue
	int sizeofQ;


};