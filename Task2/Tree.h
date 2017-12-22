#ifndef TREE_H
#define TREE_H

#include <string>
#include <fstream>

using namespace std;

enum	Dir {
	tleft = 0,
	tright = 1
};

struct	TNode {
	int height;
	bool red;
	double data;
	TNode **child;
	TNode *parent;

	TNode();
	TNode(double x);
	TNode(double x, TNode *l, TNode *r);
};


class	Tree
{
	
	public:

		//enum			T_Param			{	SFML = 'SFML', 
			//								console = 'CMD'		};
		
		void			flink			(string filename);

		bool			finput			();

		bool			foutput			();

		TNode			*root;

		int				nodeNum;

		void			Print			();

		TNode			*Find			(TNode *t, double data);

		fstream			file;

	protected:

		string			fname;

		void			Write			(TNode * t);

		void			ErrorMessage	(int key);

		void			consoleOutput	(TNode *root, int level);	
};



void	Clear	(TNode *t);


#endif
