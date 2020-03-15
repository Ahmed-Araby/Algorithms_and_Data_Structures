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

public:
	// methods
	AvlTree() 
	{
		root = NULL;
		count = 0;
		cout << "hey Iam AVL Tree " << endl;
		return;
	}

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
	void insert(int val){
		root = insert(val, root);
		return;
	}

	Node *del(int val , Node *root)
	{
		if (root == NULL)
			return NULL;

		if (root->val == val)
		{
			count--;
			// delete 
			if (root->left != NULL && root->right != NULL)
			{
				/*
				max in the left
				or
				min in the right
				*/

				int new_val = get_min(root->right);
				cout << "min value is " << new_val << endl;
				del(new_val); // will be leaf node or node with 1 child
				root->val = new_val;
			}

			else if (root->left == NULL)
				root = root->right;
			else if (root->right == NULL)
				root = root->left;
			/*
			// will not be executed ever 
			else // delete leaf node 
				root = NULL;
			*/

			/*
			 no update or balance need in this case 
			*/
			return root;
		}
		else if (val > root->val)
			root->right = del(val, root->right);  // make right point at the new modified subtree 
		else if (val < root->val)
			root->left = del(val, root->left);
		
		//////////////////////////////////////////////
		// next 2 lines are what make it balanced BST
		update(root);
		root = balance(root);
		/////////////////////////////////////////////

		/*
		in this case we don't need to return any pointers 
		but this is just for consecisty !! 
		*/
		return root;
	}

	void del(int val) {
		root = del(val, root);
		return;
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
		// ***** we need to update the bf and heights after the rotation *****

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
};

