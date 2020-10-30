#pragma once
#include<iostream>
using namespace std;

class node
{

public:
	int key;
	node* left;
	node* right;

	/*
	we can use the parent to avoid the need 
	to return the new root of the subtree to keep the tree connected.
	if parent is null make the this->root to point at me, as then I will be the root.
	*/

	node* parent;

	node();
	node(int key);
};


class BSTree
{

private:
	node* root;
	node* insert(node* root, int key, node* &insertedNode, node* parent);
	bool remove(node* root, int key);
	node* find(node* root, int key);
	void inOrderTraveral(node* root);

public:
	BSTree();
	node* insert(int key);
	bool remove(int key);
	node* find(int key);
	void display();
};
