#pragma once
#include <iostream>
#include <algorithm>
using namespace std;


class Node
{

public:
	// information
	int val, balance_factor, height;
	Node* left, * right;
	//Node *parent; //  ignore it for now 

	// methods 
	Node()
	{
		val = 0;
		balance_factor = 0;
		height = -1;
		
		left = NULL;
		right = NULL;
		//parent = NULL;

		cout << "hey Iam a node " << endl;
		return;
	}
};
class AvlTree
{
private:
	// information 
	int count;
	Node *root;

	// BST 
	Node* insert(int val, Node* root)
	{
		if (root == NULL)
		{
			root = new Node(); // point at a new location in memeory 
			root->val = val;
			count++;
		}
		else if (val > root->val)
			root->right = insert(val, root->right);
		else if (val < root->val)
			root->left = insert(val, root->left);
		
		//////////////////////////////////////////////
		// next 2 lines are what make it blanced BST
		update(root);
		root = balance(root);
		/////////////////////////////////////////////
		return root;
	}
	

	Node *remove(int val , Node *root)
	{
		// found the value 
		if (root->val == val) 
		{
			// delete 
			if (root->left != NULL && root->right != NULL)
			{
				/*
				max in the left
				or
				min in the right
				*/
				int lh = root->left->height, rh = root->right->height;
				if (rh >= lh)
				{
					int new_val = get_min(root->right);
					cout << "min value is " << new_val << endl;
					root->right = remove(new_val, root->right); // will be leaf node or node with 1 child
					root->val = new_val;
				}
				else
				{
					int new_val = get_max(root->left);
					cout << "max value is " << new_val << endl;
					// don't decrease the number of nodes **
					root->left = remove(new_val, root->left); 
					root->val = new_val;
				}
			}

			// will also take care of leaf node case
			else if (root->left == NULL) {
				Node *tmp = root->right;
				delete root; // **************** delete the space in memoery ******************
				root = tmp;
				
			}
			else if (root->right == NULL) {
				Node *tmp= root->left;
				delete root; // **************** delete the space in memoery ******************
				root = tmp;
			}
		}

		else if (val > root->val)
			root->right = remove(val, root->right);  // make right point at the new modified subtree 
		else if (val < root->val)
			root->left = remove(val, root->left);
		
		//////////////////////////////////////////////
		// next 2 lines are what make it balanced BST
		update(root);
		root = balance(root);
		// nodes envolved get updated again in the rotation methods 
		/////////////////////////////////////////////

		/*
		in this case we don't need to return any pointers 
		but this is just for consecisty !! 
		*/
		return root;
	}
public:
	AvlTree()
	{
		root = NULL;
		count = 0;
		cout << "hey Iam AVL Tree " << endl;
		return;
	}

	bool insert(int val) {
		if (!contain(val)) {
			root = insert(val, root);
			return true;
		}
		return false;
	}

	bool remove(int val) {
		if (contain(val)) {
			count--;
			root = remove(val, root);
			return true;
		}
		return false;;
	}

	bool contain(int val)
	{
		Node* ptr = root;
		while (true)
		{
			if (ptr == NULL)
				return false;
			if (val == ptr->val)
				return true;
			else if (val > ptr->val)
				ptr = ptr->right;
			else
				ptr = ptr->left;
		}
		return false;
	}

	int size()
	{
		return count;
	}

	int get_min(Node* ptr)
	{
		int min_val = ptr->val;
		while (true)
		{
			if (ptr == NULL)
				break;
			min_val = min(min_val, ptr->val);
			ptr = ptr->left;
		}
		return min_val;
	}

	int get_max(Node* ptr)
	{
		int max_val = ptr->val;
		while (true)
		{
			if (ptr == NULL)
				break;
			max_val = max(max_val, ptr->val);
			ptr = ptr->right;
		}
		return max_val;
	}

	void dfs(Node* ptr)
	{
		if (ptr == NULL) 
			return;
		cout << ptr->val << endl;
		if (ptr->left == NULL && ptr->right == NULL)
			cout << "LEAF" << endl;
		dfs(ptr->left);
		dfs(ptr->right);
		return;
	}
	void dfs(){
		dfs(root);
	}


private:
	// B-BST
	// rotations 
	
	/*
	rotations are very sensitive to the calculation of Balance_factor. 
	right rotation is CW direction. 
	left rotation is CCW direction. 
	__first__second__ 
	*/


	Node* balance(Node* root)
	{
		if (root == NULL)
			return NULL;

		int bf = root->balance_factor;
		if (bf == 2)
		{
			if (root->right->balance_factor >= 0)
				root = left_left_rotation(root);
			else
				root = right_left_rotation(root);
		}
		else if (bf == -2)
		{
			if (root->left->balance_factor <= 0)
				root = right_right_rotation(root);
			else
				root = left_right_rotation(root);
		}
		return root;
	}

	void update(Node* root)
	{
		if (root == NULL)
			return;

		int rh = -1, lh = -1;
		if (root->right != NULL)
			rh = root->right->height;
		if (root->left != NULL)
			lh = root->left->height;

		root->height = max(lh, rh) + 1;
		root->balance_factor = rh - lh;
		return;
	}

	Node *right_right_rotation(Node *cur_ptr)
	{
		Node* left = cur_ptr->left;
		cur_ptr->left = left->right;
		left->right = cur_ptr;

		// order matters (childs first)
		update(cur_ptr);
		update(left);
		return left;
	}

	Node *left_left_rotation(Node* cur_ptr)
	{
		Node *right = cur_ptr->right;
		cur_ptr->right = right->left;
		right->left = cur_ptr;

		// order matters (childs first)
		update(cur_ptr);
		update(right);
		return right;
	}

	Node *left_right_rotation(Node* cur_ptr)
	{
		Node* left = cur_ptr->left;

		// left left rotation to my left subtree 
		left = left_left_rotation(left);
		cur_ptr->left = left;

		// right right rotation to the tree rooted at cur_ptr
		return right_right_rotation(cur_ptr);
	}

	Node* right_left_rotation(Node* cur_ptr)
	{
		Node* right = cur_ptr->right;

		// right right rotation to my right subtree 
		right = right_right_rotation(right);
		cur_ptr->right = right;

		// left left rotation to the sub tree rooted at cur_ptr
		return left_left_rotation(cur_ptr);
	}

	bool validate()
	{
		/*
		  ****** to be implemented ******
		*/
		cout << "check the invarient of binary search tree" << endl;
		return true;
	}
};