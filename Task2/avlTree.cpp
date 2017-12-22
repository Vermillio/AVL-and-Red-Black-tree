#include "avlTree.h"

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;



void  AvlTree::countheight		(TNode *t)
{
	if (!t)
		return;
	countheight(t->child[tleft]);
	countheight(t->child[tright]);
	t->height = max(height(t->child[tleft]), height(t->child[tright])) + 1;
}

int	  AvlTree::height			(TNode *t)
{
	return t ? t->height : 0;
}

TNode  *AvlTree::balance			(TNode *t)
{
	countheight(t);
	if (delta_h(t) >= 2)
	{
		if (delta_h(t->child[tleft]) < 0)
			t->child[tleft] = rotate_once(t->child[tleft], tleft);
		t = rotate_once(t, tright);
	}
	else if (delta_h(t) <= -2)
	{
		if (delta_h(t->child[tright]) > 0)
			t->child[tright] = rotate_once(t->child[tright], tright);
		t = rotate_once(t, tleft);
	}
	//countheight(t);
	return t;
}

void  AvlTree::Insert			(double data)
{
	root = avlInsert(root, data);
}

TNode* AvlTree::avlInsert(TNode* t, double data)
{
	if (!t)
	{
		TNode *p = new TNode(data);
		p->parent = t;
		return p;
	}
	if (data < t->data)
		t->child[tleft] = avlInsert(t->child[tleft], data);
	else
		t->child[tright] = avlInsert(t->child[tright], data);
	return balance(t);
}

void  AvlTree::Remove			(double data)
{
	root = avlRemove(root, data);
}


TNode* AvlTree::avlRemove(TNode* t, double data) // k key deletion from p tree
{
	if (!t) return nullptr;
	if (data < t->data)
		t->child[tleft] = avlRemove(t->child[tleft], data);
	else if (data > t->data)
		t->child[tright] = avlRemove(t->child[tright], data);
	else
	{
		TNode* q = t->child[tleft];
		TNode* r = t->child[tright];

		if (q && r)
		{
			while (q->child[tright])
			{
				q = q->child[tright];
			}
			t->data = q->data;
			q = avlRemove(q, data);
			return q;
		}

		TNode *x;

		if (q)
			x = q;
		else
			x = r;

		if (!t->parent)
			root = x;
		else {
			if (t->parent->child[tleft] && t == t->parent->child[tleft])
				t->parent->child[tleft] = x;
			else
				t->parent->child[tright] = x;
			if (x)
				x->parent = t->parent;
		}
		return balance(x);
	}
}

TNode *AvlTree::rotate_once		(TNode * t, bool dir)
{
	TNode *pivot = t->child[!dir];
	t->child[!dir] = pivot->child[dir];
	if (t->child[!dir])
		pivot->child[dir]->parent = t;
	pivot->child[dir] = t;
	pivot->parent = t->parent;
	t->parent = pivot;

	balance(t);
	balance(pivot);
	
	return pivot;
}

int	  AvlTree::delta_h			(TNode *t)
{
	if (!t)
		return 0;
	return height(t->child[tleft]) - height(t->child[tright]);
}

void AvlTree::demo()
{
	string f;
	int choise, choise2;
	int data;

	bool exit = false;
	cout << "                 < AVL-TREE > " << endl;
	while (exit == false)
	{
		cout << " 0 - read file, 1 - write file, 2 - insert, 3 - remove, 4 - search, 5 - enter filename, any other symbol - exit" << endl;

		cin >> choise;
		cin.ignore(cin.rdbuf()->in_avail());
		switch (choise)
		{
		case 0:
			if (fname == "")
			{
				cout << "Enter filename : ";
				getline(cin, fname);
			}
			if (finput())
				Print();
			break;
		case 1:
			if (fname == "")
			{
				cout << "Enter filename : ";
				cin >> fname;
			}
			foutput();
			break;
		case 2:
			cout << "Enter data. To stop enter any symbol." << endl;
			while (cin >> data)
			{
				Insert(data);
				Print();
			}
			break;
		case 3:
			cout << "Enter data. To stop enter any symbol." << endl;
			while (cin >> data)
			{
				Remove(data);
				Print();
			}
			break;
		case 4:
			cin >> data;
			if (Find(root, data))
				cout << "Found." << endl;
			else cout << "Not found." << endl;
			break;
		case 5:
			cin >> fname;
			break;
		default:
			return;
			break;
		}
		cin.clear();
		fflush(stdin);
		cin.ignore(cin.rdbuf()->in_avail());
	}
	Clear(root);
	cout << "               < END > " << endl;
}

