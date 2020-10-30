// BST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "BSTree.h"
int main()
{
	// for testing perpouse
	BSTree tree;
	node* in;
	int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
	for (int i = 0; i < 7; i++)
	{
		in = tree.insert(arr[i]);
		cout << arr[i] << " " << in->key << endl;
	}

	cout << endl << endl;
	tree.display();

	cout <<"remove "<< endl<< endl;
 
	tree.remove(0);
	for (int i = 0; i < 7; i++)
	{
		 in = tree.find(arr[i]);
		 cout << (in == nullptr || in->parent == nullptr ? -99999 : in->parent->key) << " " << arr[i] << endl;
	} 
}