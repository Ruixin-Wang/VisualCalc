#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <map>

class Node;

extern std::map<std::string, int> variables;


class Node
{
public:
	// evaluate the node, especially the whole expression tree
	virtual double eval() = 0;
	// logic derivation, may return ConstNode(0)
	virtual Node* derivate(std::string x) = 0;
	// display expression tree using json-like format
	virtual void toString() = 0;
};


class ConstNode : public Node
{
	double value;
public:
	ConstNode(double value) : value(value) {}
	~ConstNode() {}

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override;
};

class VarNode : public Node
{
	// use dictionary to store variable
	std::string name;
public:
	VarNode(std::string name) : name(name) {}
	~VarNode() {}

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override;
};

class AddNode : public Node
{
	Node *left, *right;
public:
	AddNode(Node *left, Node *right) : left(left), right(right) {}
	~AddNode() {}

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override;
};

class MutliplyNode : public Node
{
	Node *left, *right;
public:
	MutliplyNode(Node* left, Node* right) : left(left), right(right) {}
	~MutliplyNode() {}

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override;
};

class SinNode : public Node
{
	Node *child;
public:
	SinNode(Node* child) : child(child) {}
	~SinNode() {}

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override;
};


class CosNode : public Node
{
	Node* child;
public:
	CosNode(Node *child) : child(child) {}
	~CosNode() {}

	virtual double eval() override;

	virtual Node* derivate(std::string x) override;

	virtual void toString() override;
};