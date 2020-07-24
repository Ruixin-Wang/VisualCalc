#pragma once
#include <QtWidgets>

#define MAXQ 100

enum {Const, Var, Operator};

struct Node {
	Node* LChild, * RChild;
	QString Element;
	int type;
};


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

	double evaluate();
	double evaluate(double x);




private:
	boolean hasVar;
	struct Node* Tree;
	struct Node* Queue[MAXQ];		// infix expression Queue
	int sizeofQ;


};