#include "NodeforMatrix.h"

typedef enum {
	_add, _sub, _mul, _rdiv, _ldiv, _trans, _inv, _adj, _det, _tr, _Default
} opr;

std::map<QString, int> priority = {
	{"+", 1}, {"-", 1},
	{"*", 2}, {"/", 2}, {"\\", 2},

	{"trans", 3}, {"inv", 3},
	{"adj", 3}, {"det", 3},
	{"tr", 3}
};

std::map<QString, opr> oprtype = {
	{"+", _add}, {"-", _sub},
	{"*", _mul}, {"/", _rdiv}, {"\\", _ldiv},

	{"trans", _trans}, {"inv", _inv},
	{"adj", _adj}, {"det", _det},
	{"tr", _tr}
};


MATRIX VarNode::eval()
{
	return variables[name];//using dictionary
}

AddNode::~AddNode()
{
	delete left;
	delete right;
}

MATRIX AddNode::eval()
{
	return left->eval().add(right->eval());
}

SubNode::~SubNode()
{
	delete left;
	delete right;
}

MATRIX SubNode::eval()
{
	return left->eval().subtract(right->eval());
}

MutliplyNode::~MutliplyNode()
{
	delete left;
	delete right;
}

MATRIX MutliplyNode::eval()
{
	return left->eval().multiply(right->eval());
}

RightDivNode::~RightDivNode()
{
	delete left;
	delete right;
}

MATRIX RightDivNode::eval()
{
	return left->eval().rightDivide(right->eval());
}

LeftDivNode::~LeftDivNode()
{
	delete left;
	delete right;
}

MATRIX LeftDivNode::eval()
{
	return left->eval().leftDivide(right->eval());
}

TransNode::~TransNode()
{
	delete child;
}

MATRIX TransNode::eval()
{
	return child->eval().transpose();
}

InvNode::~InvNode()
{
	delete child;
}

MATRIX InvNode::eval()
{
	return child->eval().inverse();
}

AdjNode::~AdjNode()
{
	delete child;
}

MATRIX AdjNode::eval()
{
	return child->eval().adjoint();
}

DetNode::~DetNode()
{
	delete child;
}

MATRIX DetNode::eval()
{
	return child->eval().determinant();
}

TrNode::~TrNode()
{
	delete child;
}

MATRIX TrNode::eval()
{
	return child->eval().trace();
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
					Node* root = new RightDivNode(createInfix(left, i - 1), createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("\\"))
				{
					Node* root = new LeftDivNode(createInfix(left, i - 1), createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("trans"))
				{
					Node* root = new TransNode(createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("inv"))
				{
					Node* root = new InvNode(createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("adj"))
				{
					Node* root = new AdjNode(createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("det"))
				{
					Node* root = new DetNode(createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("tr"))
				{
					Node* root = new TrNode(createInfix(i + 1, right));
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

MATRIX ExprTree::eval(Node* N)
{
	return N->eval();
}

MATRIX ExprTree::evaluate()
{
	// Driving Function
	return eval(this->Tree);
}
