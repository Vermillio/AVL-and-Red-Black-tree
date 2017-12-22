#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "Tree.h"


class AvlTree : public Tree
{
public:
	
	//!!!!!!!!!!!!!!!!!
	void	Insert			(double data);

	//!!!!!!!!!!!!!
	void	Remove			(double data);


	void demo();

private:

	TNode   *avlInsert(TNode *t, double data);

	TNode *avlRemove(TNode *t, double data);

	int		delta_h			(TNode *t);

	TNode	*rotate_once	(TNode *t, bool dir);
	
	void	countheight		(TNode *t);

	int		height			(TNode *t);

	TNode	*balance			(TNode *t);

};
#endif