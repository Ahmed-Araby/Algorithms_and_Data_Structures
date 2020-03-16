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
	t.remove(5);
	t.remove(4);
	t.remove(13);
	t.remove(11);
	t.remove(14);
	t.insert(13);
	t.insert(14);
	t.remove(13);
	t.remove(11);
	t.remove(14);
	t.remove(1);
	t.remove(9);
	t.insert(114);

	//t.insert(11);
	bool tell = t.remove(0);
	cout << tell << " " << "is the response for removing 0 which is not exist" << endl;
	cout << "contain response "<<t.contain(11) << " " << t.contain(0) << endl;

	cout << t.size() << endl;
	cout << endl;
	t.dfs();
	cout << endl;
	return 0;
}