#include "ExprTree.h"
#include <map>

std::map<QString, int> priority = {
	{"+", 1}, {"-", 1}, 
	{"*", 2}, {"/", 2},
	
	{"lg", 3}, {"based log", 3},
	{"abs", 3}, {"arctan", 3},
	{"arccos", 3}, {"arcsin", 3},
	{"tan", 3}, {"cos", 3},
	{"sin", 3}, {"ln", 3},

	{"^", 4}, {"times root", 4}, {"sqrt", 4},
	{"^3", 4}, {"^2", 4}, {"!", 4},
};

void ExprTree::enQueue(Node* N)
{
	Queue[sizeofQ++] = N;
}

Node* ExprTree::createInfix(int leftx, int rightx)
{
	int left = leftx;
	int right = rightx;
	while (!Queue[left]->Element.compare("(") && !Queue[right]->Element.compare(")")) {
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
			if (!Queue[i]->Element.compare("("))
			{
				int j = 1;
				while (Queue[i]->Element.compare(")") || j)
				{	// brackets matching
					i++;
					if (!Queue[i]->Element.compare("(")) j++;
					if (!Queue[i]->Element.compare(")")) j--;
				}
			}
			int pri;
			std::map<QString, int>::iterator iter = priority.find(Queue[i]->Element);
			if (iter != priority.end()) {
				pri = iter->second;
			}
			else {
				pri = 0;
			}

			if (pri == k) {
				Queue[i]->LChild = createInfix(left, i - 1);
				Queue[i]->RChild = createInfix(i + 1, right);
				return Queue[i];
			}
			i++;
		}
	}
}

void ExprTree::buildTree()
{
	// TODO: Recursive implementation
	Tree = createInfix(0, sizeofQ - 1);
}

double ExprTree::evaluate()
{
	return 0;
}

double ExprTree::evaluate(double x)
{
	return 0;
}