#include "Node.h"


double ConstNode::eval()
{
	return value;
}

Node* ConstNode::derivate(std::string x)
{
	Node* Zero = new ConstNode(0);
	return Zero;
}

void ConstNode::toString()
{
	std::cout << "Const: " << value << std::endl;
}

double VarNode::eval()
{
	return variables[name];//using dictionary
}

Node* VarNode::derivate(std::string x)
{
	if (name == x)
	{
		Node* Hit = new ConstNode(1);
		return Hit;
	}
	else
	{
		Node* Zero = new ConstNode(0);
		return Zero;
	}
}

void VarNode::toString()
{
	std::cout << "Var: " << name << " = " << variables[name] << std::endl;
}

AddNode::~AddNode()
{
	delete left;
	delete right;
}

double AddNode::eval()
{
	return left->eval() + right->eval();
}

Node* AddNode::derivate(std::string x)
{
	Node* dlAdr = new AddNode(left->derivate(x), right->derivate(x));
	return dlAdr;
}

void AddNode::toString()
{
	std::cout << "AddNode: " << std::endl;
	std::cout << "LeftNode:" << std::endl;
	left->toString();
	std::cout << "EndOfLeftNode" << std::endl;
	std::cout << "RightNode:" << std::endl;
	right->toString();
	std::cout << "EndOfRightNode" << std::endl;
	std::cout << "EndOfAddNode" << std::endl;
}

MutliplyNode::~MutliplyNode()
{
	delete left;
	delete right;
}

double MutliplyNode::eval()
{
	return left->eval() * right->eval();
}

Node* MutliplyNode::derivate(std::string x)
{
	Node* dlMr = new MutliplyNode(left->derivate(x), right);
	Node* lMdr = new MutliplyNode(left, right->derivate(x));
	Node* dlMrAlMdr = new AddNode(dlMr, lMdr);
	return dlMrAlMdr;
}

void MutliplyNode::toString()
{
	std::cout << "MutliplyNode: " << std::endl;
	std::cout << "LeftNode:" << std::endl;
	left->toString();
	std::cout << "EndOfLeftNode" << std::endl;
	std::cout << "RightNode:" << std::endl;
	right->toString();
	std::cout << "EndOfRightNode" << std::endl;
	std::cout << "EndOfMutliplyNode" << std::endl;
}

SinNode::~SinNode()
{
	delete child;
}

double SinNode::eval()
{
	return sin(child->eval());
}

Node* SinNode::derivate(std::string x)
{
	Node* dfg = new CosNode(child);
	Node* dfgMdg = new MutliplyNode(dfg, child->derivate(x));
	return dfgMdg;
}


void SinNode::toString()
{
	std::cout << "SinNode: " << std::endl;
	std::cout << "ChildNode:" << std::endl;
	child->toString();
	std::cout << "EndOfChildNode" << std::endl;
	std::cout << "EndOfSinNode" << std::endl;
}

CosNode::~CosNode()
{
	delete child;
}

double CosNode::eval()
{
	return cos(child->eval());
}

Node* CosNode::derivate(std::string x)
{
	Node* dfg = new SinNode(child);
	Node* dfgMdg = new MutliplyNode(dfg, child->derivate(x));
	return dfgMdg;
}

void CosNode::toString()
{
	std::cout << "CosNode: " << std::endl;
	std::cout << "ChildNode:" << std::endl;
	child->toString();
	std::cout << "EndOfChildNode" << std::endl;
	std::cout << "EndOfCosNode" << std::endl;
}