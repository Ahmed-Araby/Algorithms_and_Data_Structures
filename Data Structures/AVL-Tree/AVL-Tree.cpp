// AVL-Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include "AvlTree.h"

using namespace std;
int main()
{
	cout << "we are implementating a self blanced binary search tree" << endl;
	AvlTree t;
	int l[] = {1 , 2 , 3 , 4 , 5 , 6, 7 , 8 , 9 , 10 , 11 , 2 , 13 , 14};
	for (int i = 0; i <14; i++)
	{
		t.insert(l[i]);
	}
	t.del(5);
	t.del(8);
	cout << t.size() << endl;
	cout << endl;
	t.dfs();
	cout << endl;
	return 0;
}