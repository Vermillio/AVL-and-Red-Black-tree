#include "Tree.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;



TNode::TNode()
{
	child = new TNode*[2];
	child[0] = nullptr;
	child[1] = nullptr;
	parent = nullptr;
}

TNode::TNode				(double x) : data(x),
child(new TNode*[2]),
parent(nullptr)
{
	red = true;
	height = 0;
	child[tleft] = nullptr;
	child[tright] = nullptr;
}

TNode::TNode				(double x, TNode * l, TNode * r) : data(x), child(new TNode*[2]), parent(nullptr), red(true), height(0)
{
	child[0] = l;
	child[1] = r;
};


void Tree::flink			(string filename)
{
	fname = filename;
}

bool Tree::finput			()
{
	file.open(fname, ios::in);
	if (!file.is_open())
	{
		ErrorMessage(0);
		return 0;
	}

	file.seekg(0);

	stack<TNode*> stck;
	TNode *node_l = nullptr, *node_r = nullptr, *node_p = nullptr;

	string token;
	while (!file.eof())
	{
		file >> token;
		if (token == "1")
		{
			file >> token;
			node_p = new TNode(stoi(token));
			stck.push(node_p);
		}
		else if (token == "0" && !file.eof()) {
			node_r = stck.top();
			stck.pop();
			node_l = stck.top();
			stck.pop();

			file >> token;
			node_p = new TNode(stoi(token), node_l, node_r);

			node_l->parent = node_p;
			node_r->parent = node_p;

			stck.push(node_p);
		}
		else {
			ErrorMessage(1);
			Clear(node_l);
			Clear(node_r);
			Clear(node_p);
			//clr stck
			return 0;
		}
	}
	root = stck.top();
	stck.pop();

	file.close();
	return 1;
}

void Tree::Write			(TNode *t)
{
	if (!t)
		return;
	if (!t->child[tleft] && !t->child[tright])
	{
		file << "1 " << to_string(t->data) << " ";
	}
	else {
		Write(t->child[tleft]);
		Write(t->child[tright]);
		file << "0 " << to_string(t->data) << " ";
	}
}

bool Tree::foutput			()
{
	file.open(fname, ios::out);
	if (!file.is_open())
	{
		ErrorMessage(0);
		return 0;
	}

	Write(root);

	file.close();
	return 1;
}

void Tree::Print			()
{
	//switch (param)
	//{
		//case (SFML):
		//{

		//}
		//case (console) :
		//{
			consoleOutput(root, 0);
			cout << endl;
		//}
	//}
}

TNode *Tree::Find			(TNode *t, double data)
{
	if (t)
	{
		if (t->data == data)
			return t;
		else if (t->data > data)
			return Find(t->child[0], data);
		else if (t->data < data)
			return Find(t->child[1], data);
	}
	else 
		return nullptr;
	return nullptr;
}


void Clear					(TNode *t)
{
	if (!t)
		return;
	Clear(t->child[0]);
	Clear(t->child[1]);
	delete[] t->child;
	delete t;
	t = nullptr;
}

void Tree::	ErrorMessage	(int key)
{
	switch (key)
	{
	case 0:
		cout << "Couldn't open file." << endl;
		break;
	case 1:
		cout << "Incorrect tree file." << endl;
		break;
	}
}

void Tree::consoleOutput	(TNode *p, int level)
{
	if (p)
	{
		consoleOutput(p->child[tright], level + 1);
		for (int i = 0; i < level; i++)
			cout << "     ";
		cout << "(" << p->data << ")" << endl;
		consoleOutput(p->child[tleft], level + 1);
	}
	return;
}

