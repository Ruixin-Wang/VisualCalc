#include "NodeforMatrix.h"

typedef enum {
	_add, _sub, _mul, _rdiv, _ldiv, _trans, _inv, _adj, _det, _tr, _Default
} opr;

std::map<QString, int> priorityforMatrix = {
	{"+", 1}, {"-", 1},
	{"*", 2}, {"/", 2}, {"\\", 2},

	{"trans", 3}, {"inv", 3},
	{"adj", 3}, {"det", 3},
	{"tr", 3}
};

std::map<QString, opr> oprtypeforMatrix = {
	{"+", _add}, {"-", _sub},
	{"*", _mul}, {"/", _rdiv}, {"\\", _ldiv},

	{"trans", _trans}, {"inv", _inv},
	{"adj", _adj}, {"det", _det},
	{"tr", _tr}
};


MATRIX VarNodeForMatrix::eval() 
{
	return *(variablesforMatrix[name]);//using dictionary
}

AddNodeForMatrix::~AddNodeForMatrix()
{
	delete left;
	delete right;
}

MATRIX AddNodeForMatrix::eval()
{
	return left->eval().add(right->eval());
}

SubNodeForMatrix::~SubNodeForMatrix()
{
	delete left;
	delete right;
}

MATRIX SubNodeForMatrix::eval()
{
	return left->eval().subtract(right->eval());
}

MutliplyNodeForMatrix::~MutliplyNodeForMatrix()
{
	delete left;
	delete right;
}

MATRIX MutliplyNodeForMatrix::eval()
{
	return left->eval().multiply(right->eval());
}

RightDivNodeForMatrix::~RightDivNodeForMatrix()
{
	delete left;
	delete right;
}

MATRIX RightDivNodeForMatrix::eval()
{
	return left->eval().rightDivide(right->eval());
}

LeftDivNodeForMatrix::~LeftDivNodeForMatrix()
{
	delete left;
	delete right;
}

MATRIX LeftDivNodeForMatrix::eval()
{
	return left->eval().leftDivide(right->eval());
}

TransNodeForMatrix::~TransNodeForMatrix()
{
	delete child;
}

MATRIX TransNodeForMatrix::eval()
{
	return child->eval().transpose();
}

InvNodeForMatrix::~InvNodeForMatrix()
{
	delete child;
}

MATRIX InvNodeForMatrix::eval()
{
	return child->eval().inverse();
}

AdjNodeForMatrix::~AdjNodeForMatrix()
{
	delete child;
}

MATRIX AdjNodeForMatrix::eval()
{
	return child->eval().adjoint();
}

DetNodeForMatrix::~DetNodeForMatrix()
{
	delete child;
}

MATRIX DetNodeForMatrix::eval()
{
	return child->eval().determinant();
}

TrNodeForMatrix::~TrNodeForMatrix()
{
	delete child;
}

MATRIX TrNodeForMatrix::eval()
{
	return child->eval().trace();
}


void ExprTreeForMatrix::enQueue(NodeForMatrix* N)
{
	Queue[sizeofQ++] = N;
}

NodeForMatrix* ExprTreeForMatrix::createInfix(int leftx, int rightx)
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
			std::map<QString, int>::iterator iter = priorityforMatrix.find(Queue[i]->retElement());
			if (iter != priorityforMatrix.end()) {
				pri = iter->second;
			}
			else {
				pri = 0;
			}

			if (pri == k) {
				// Done.TODO: complete, and what to compare?
				if (Queue[i]->retElement() == QString::fromStdString("+"))
				{
					NodeForMatrix* root = new AddNodeForMatrix(createInfix(left, i - 1), createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("-"))
				{
					NodeForMatrix* root = new SubNodeForMatrix(createInfix(left, i - 1), createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("*"))
				{
					NodeForMatrix* root = new MutliplyNodeForMatrix(createInfix(left, i - 1), createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("/"))
				{
					NodeForMatrix* root = new RightDivNodeForMatrix(createInfix(left, i - 1), createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("\\"))
				{
					NodeForMatrix* root = new LeftDivNodeForMatrix(createInfix(left, i - 1), createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("trans"))
				{
					NodeForMatrix* root = new TransNodeForMatrix(createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("inv"))
				{
					NodeForMatrix* root = new InvNodeForMatrix(createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("adj"))
				{
					NodeForMatrix* root = new AdjNodeForMatrix(createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("det"))
				{
					NodeForMatrix* root = new DetNodeForMatrix(createInfix(i + 1, right));
					return root;
				}
				else if (Queue[i]->retElement() == QString::fromStdString("tr"))
				{
					NodeForMatrix* root = new TrNodeForMatrix(createInfix(i + 1, right));
					return root;
				}
			}
			i++;
		}
	}
}

void ExprTreeForMatrix::buildTree()
{
	// Driving Function
	Tree = createInfix(0, sizeofQ - 1);
}

MATRIX ExprTreeForMatrix::eval(NodeForMatrix* N)
{
	return N->eval();
}

MATRIX ExprTreeForMatrix::evaluate()
{
	// Driving Function
	return eval(this->Tree);
}
