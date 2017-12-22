#ifndef RB_TREE_H
#define RB_TREE_H

#include "Tree.h"


class RbTree : public Tree
{
	public:

		void			Insert				(double data);

		void			Remove				(TNode *t);

		void			demo();

	private:

		void			CheckInsert			(TNode *t);

		void			CheckRemove			(TNode *t);

		TNode			*rotate_once		(TNode *t, bool dir);

		TNode			*rotate_twice		(TNode *t, bool dir);

};
#endif
