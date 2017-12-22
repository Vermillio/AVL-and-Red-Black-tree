#include "rbTree.h"
#include <iostream>

using namespace std;




void   RbTree::Insert			(double data)
{
	if (!root)
	{
		root = new TNode(data);
		nodeNum++;
		root->red = 0;
		return;
		//if (root == nullptr)
			//return 0;
		//else
			//return 1;
	}
	TNode *head = new TNode(0);
	TNode *q;
	bool dir = 0;
	q = head->child[1] = root;
	root->parent = head;
	head->red = 0;
	for (; ; )
	{
		dir = q->data < data;
		if (q->data == data)
			return; //0
		if (q->child[dir] == nullptr)
		{
			q->child[dir] = new TNode(data);
			q->child[dir]->parent = q;
			if (q->child[dir] == nullptr)
				return; //0
			nodeNum++;
			q = q->child[dir];
			break;
		}
		q = q->child[dir];
	}

	CheckInsert(q);
	
	root = head->child[1];
	root->parent = nullptr;
	delete head; //remove extra root

	if (root->red != 0)
		root->red = 0;
	
	return; //1

}

void   RbTree::Remove			(TNode *t)
{

	TNode *x, *y;

	if (!t) 
		return;

	if (t->child[tleft] && t->child[tright])
	{
		y = t->child[tleft];
		while (y->child[tright])
			y = y->child[tright];
		t->data = y->data;
		Remove(y);
		return;
	}
	else y = t;

	if (y->child[tleft] != nullptr)
		x = y->child[tleft];
	else
		x = y->child[tright];

	if (!y->parent)
		root = x;
	else {
		if (y->parent->child[tleft] && y == y->parent->child[tleft])
			y->parent->child[tleft] = x;
		else
			y->parent->child[tright] = x;
		if (x)
			x->parent = y->parent;
	}

	if (y != t)
		t->data = y->data;

	if (x && y->red == 0)
		CheckRemove(x);
	delete y;
	nodeNum--;

}

void   RbTree::CheckInsert		(TNode *t)
{
	if (!t)
		return;

//	bool changed;
	if (t->parent->red == 0)
		return;

	TNode *g = t->parent->parent;
	if (g)
	{
		if (g->child[0] && g->child[1] && g->child[0]->red && g->child[1]->red)
		{
			g->red = 1;
			g->child[0]->red = g->child[1]->red = 0;
			CheckInsert(g);
		}
		else
		{
			TNode *p = g->parent;
			bool dir2 = p->child[1] == g;
			bool dir = g->child[0] != t->parent;
			if (g->child[dir]->child[!dir] == t)
				p->child[dir2] = rotate_twice(g, !dir);
			else
				p->child[dir2] = rotate_once(g, !dir);
		}
	}
}

void   RbTree::CheckRemove		(TNode * t)
{
	while (t != root && t->red == 0)
	{
		bool dir = t == t->parent->child[1];
		{
			TNode *w = t->parent->child[!dir];
			if (t->red == true)
			{
				t->red = false;
				t->parent->red = true;
				rotate_once(t->parent, dir);
				w = t->parent->child[!dir];
			}
			if (w->child[0]->red == false && w->child[1]->red == false)
			{
				w->red = true;
				if (t->parent->red == false)
				{
					CheckRemove(t->parent);
					return;
				}
				else t->parent->red = false;
			}
			if (w->child[1]->red == false)
			{
				w->child[0]->red = false;
				w->red = false;
				rotate_once(w, 1);
				w = t->parent->child[1];
			}
			w->red = t->parent->red;
			t->parent->red = false;
			w->child[1]->red = false;
			rotate_once(t->parent, 0);
			t = root;
		}
	}
	t->red = 0;
}

TNode* RbTree::rotate_once		(TNode *t, bool dir)
{
	TNode *pivot = t->child[!dir];
	t->child[!dir] = t->child[dir];
	if (t->child[dir])
		pivot->child[dir]->parent = t;
	pivot->child[dir] = t;
	pivot->parent = t->parent;
	t->parent = pivot;

	t->red = 1;
	pivot->red = 0;
	return pivot;
}

TNode* RbTree::rotate_twice		(TNode *t, bool dir)
{
	t->child[!dir] = rotate_once(t->child[!dir], !dir);
	return rotate_once(t, dir);
}

void RbTree::demo()
{
	string f;
	int choise, choise2;
	int data;

	cout << "           < RED-BLACK TREE > " << endl;

	bool exit = false;
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
				Remove(Find(root, data));
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
	cout << "              < END > " << endl;
}
