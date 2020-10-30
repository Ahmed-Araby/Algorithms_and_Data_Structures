#include "BSTree.h"

// node 
node::node()
{
	this->left = nullptr;
	this->right = nullptr;
	this->parent = nullptr;
}

node::node(int key)
{
	this->key = key;
	this->left = nullptr;
	this->right = nullptr;
	this->parent = nullptr;
}


// binary search tree
BSTree::BSTree()
{
	this->root = nullptr;
	cout << " binary search tree have been created" << endl;
}

// insertion 
node* BSTree::insert(node* root, int key,
					node* &insertedNode, node* parent=nullptr)
{
	if (root == nullptr) {
		insertedNode = root = new node(key);
		root->parent = parent;
	}
	else if (root->key == key)
		insertedNode = root;

	if (key > root->key)
		/* we reassign the pointer to keep the tree updated with
		the possible change in the tree structure.
		*/
		root->right = insert(root->right, key, insertedNode, root);

	else if(key < root->key)
		root->left = insert(root->left, key, insertedNode, root);

	return root;
}

node* BSTree::insert(int key)
{
	node* insertedNode = nullptr;
	this->root = insert(this->root, key, insertedNode);
	return insertedNode;
}

// find operation.
node* BSTree::find(node* root, int key)
{
	if (root == nullptr)
		return nullptr;
	else if (root->key == key)
		return root;
	else if (key > root->key)
		return find(root->right, key);
	else
		return find(root->left, key);
}

node* BSTree::find(int key)
{
	return find(this->root, key);
}


// removing operation 
int getMin(node* root)
{
	if (root->left == nullptr)
		return root->key;
	return getMin(root->left);
}

int getMax(node* root)
{
	if (root->right == nullptr)
		return root->key;
	return getMax(root->right);
}

bool BSTree::remove(node* root, int key)
{
	/*
	here I will use the parent 
	pointer to keep the structure of the tree updated

	we will decide on the direction of the node to be deleted using 
	address comparisson.
	*/

	if (root == nullptr)
		return false;

	else if (root->key == key)
	{
		if (root->left == nullptr && root->right == nullptr)
		{// case 1 , leef node 
			node* parent = root->parent;
			if (parent != nullptr) {
				if (parent->left == root)
					parent->left = nullptr;
				else
					parent->right = nullptr;
			}
			else
				this->root = nullptr;

			delete root;
		}

		else if (root->left != nullptr && root->right != nullptr)
		{ // case2 delete node with 2 subtrees
			int minRight = getMin(root->right);
			remove(this->root, minRight);
			root->key = minRight;
		}

		else if (root->left != nullptr)
		{
			node* parent = root->parent;
			if (parent != nullptr) {
				if (parent->left == root)
					parent->left = root->left;
				else
					parent->right = root->left;

				root->left->parent = parent;
			}
			else {
				this->root = root->left;
				root->left->parent = nullptr;
			}
			delete root;
		}
		else
		{
			node* parent = root->parent;
			if (parent != nullptr) {
				if (parent->left == root)
					parent->left = root->right;
				else
					parent->right = root->right;

				root->right->parent = parent;
			}
			else {
				this->root = root->right;
				root->right->parent = nullptr;
			}
			delete root;
		}
		return true;
	}

	// comlete traversing
	if (key > root->key)
		return remove(root->right, key);
	else
		return remove(root->left, key);
	return true;
}
bool BSTree::remove(int key)
{
	return remove(this->root, key);
}

// display the tree for testing purpose
void BSTree::inOrderTraveral(node* root)
{
	if (root == nullptr)
		return;
	inOrderTraveral(root->left);
	cout << root->key << endl;
	inOrderTraveral(root->right);
	return;
}

void BSTree::display()
{
	inOrderTraveral(this->root);
}


