#pragma once

#include <iostream>

template <typename Node_T>
class Node
{
public:
	//number of repeats of the same value, defaults to 1 since the minimum number of values required to have a node is 1
	int count = 1;

	//value the node represents
	Node_T key;

	//pointers to left, right, and parrent node
	Node * left = nullptr;
	Node * parent = nullptr;
	Node * right = nullptr;
	
	//get the key and pointer to parrent node using constructor
	Node(Node_T key, Node * parent) {
		this->key = key;
		this->parent = parent;
	}

	//node deconstructor, delete the child nodes causing a tree to delete itself if the root value is removed
	//
};

//types of traversals that can be called on the traverse function
enum TraversalTypes
{
	inorder = 1,
	preorder = 2,
	postorder = 3
};


template <typename BST_T>
class BST
{
private:
	Node<BST_T> * root_node = nullptr;

	//finds the minimum node of a branch given the top node of that branch
	Node<BST_T> * minimum_of_branch(Node<BST_T> * node) {
		Node<BST_T> * current_node = node;

		//traverses down a branch until the next left node is null
		while (current_node->left != nullptr) {
			current_node = current_node->left;
		}

		return current_node;
	}

	//finds the maximum node of a branch given the top node of that branch
	Node<BST_T> * maximum_of_branch(Node<BST_T> * node) {
		Node<BST_T> * current_node = node;

		//traverses down a branch until the next right node is null
		while (current_node->right != nullptr) {
			current_node = current_node->right;
		}

		return current_node;
	}

public:
	//constructor
	BST() {}

	//deconstructor
	~BST() {}

	//returns the pointer to the root node
	Node<BST_T> * root_ptr() {
		return this->root_node;
	}

	//insert function for the tree, returns the pointer to the node inserted
	Node<BST_T> * insert(BST_T value) {
		//if no root node exists then create it
		if (this->root_node == nullptr) {
			this->root_node = new Node<BST_T>(value, nullptr);
			return this->root_node;
		}

		Node<BST_T> * current_node = this->root_node;
		
		//keep going down the tree finding a spot to put the new value
		while (true) {
			//if the current node's value and the value to be inserted are the same then increment the count of the node to signify multiple of the same value
			if (current_node->key == value) {
				current_node->count++;
				return current_node;
			}
			else if (current_node->key < value) {
				//to to the right node
				if (current_node->right == nullptr) {
					//create a new node using the value under the right side of the current node
					current_node->right = new Node<BST_T>(value, current_node);
					return current_node->right;
				}
				else {
					//set the new current node to the right node
					current_node = current_node->right;
				}
			}
			else {
				//go to the left node
				if (current_node->left == nullptr) {
					//create a new node using the value under the right side of the current node
					current_node->left = new Node<BST_T>(value, current_node);
					return current_node->left;
				}
				else {
					//set the new current node to the right node
					current_node = current_node->left;
				}
			}
		}
	}

	//returns the node that contains the key value passed, or null if none was found
	Node<BST_T> * search(BST_T value) {
		//start searching from root node
		Node<BST_T> * current_node = this->root_node;

		//keep searching the tree while the current node is not null
		while (current_node != nullptr) {
			//if the current node's value matches the one we are looking for then return the current node's pointer
			if (current_node->key == value) {
				return current_node;
			}
			//if the current node's value is less than the one we are looking for go to the right node
			else if (current_node->key < value) {
				current_node = current_node->right;
			}
			//if the current node's value is more than the one we are looking for go to the left node
			else {
				current_node = current_node->left;
			}
		}

		//if no matching node was found then return a null value.
		return nullptr;
	}

	//returns true if the value was removed, false if the value was not (because it could not be found)
	bool remove(BST_T value) {
		//the node we want to remove
		Node<BST_T> * node = this->search(value);

		//if no node was found then return false 
		if (node == nullptr) {
			return false;
		} 
		
		//use the remove(node) overalod to remove based on the node pointer
		return remove(node);
	}

	//function overload for node pointer input
	bool remove(Node<BST_T> * node) {
		//remove the value from the tree if it was found

		//if the node containts a count higher than one of a spesific value then just decrement that count
		if (node->count > 1) {
			node->count--;
			return true;
		}

		//if the node has no children then it can be safeley removed
		else if (node->right == nullptr && node->left == nullptr) {
			//in case if the node to be removed is a bare root noode
			if (node == this->root_node) {
				//delete the node and set root_node to nullptr 014C6838
				root_node = nullptr;
				delete node;
				return true;
			}
			//if the node is the right node of the parrent
			else if (node->parent->right == node) {
				node->parent->right = nullptr;
				delete node;
				return true;
			}
			//if the node is the right node of the parrent
			else if (node->parent->left == node) {
				node->parent->left = nullptr;
				delete node;
				return true;
			}

			//if somehow the node wasnt deleted return false
			return false;
		}
		//if the node has a single child and it is the right child
		else if (node->right != nullptr && node->left == nullptr) {
			//in case if the node to be removed and it has a single child
			if (node == this->root_node) {
				//delete the node and set root_node to the child
				root_node = node->right;
				delete node;
				return true;
			}
			//if the node is the right node of the parrent
			else if (node->parent->right == node) {
				//set the current node's parrent's right child to the current node's right child
				node->parent->right = node->right;

				//set the right node's new parrent to the current node's parrent (if it is not null)
				if (node->right != nullptr) {
					node->right->parent = node->parent;
				}
				delete node;
				return true;
			}
			//if the node is the right node of the parrent
			else if (node->parent->left == node) {
				//set the current node's parrent's left child to the current node's right child
				node->parent->left = node->right;

				//set the right node's new parrent to the current node's parrent (if it is not null)
				if (node->right != nullptr) {
					node->right->parent = node->parent;
				}
				delete node;
				return true;
			}
			//if somehow the node wasnt deleted return false
			return false;
		}
		//if the node has a single child and it is the left child
		else if (node->right == nullptr && node->left != nullptr) {
			//in case if the node to be removed and it has a single child
			if (node == this->root_node) {
				//delete the node and set root_node to the child
				root_node = node->left;
				delete node;
				return true;
			}
			//if the node is the right node of the parrent
			else if (node->parent->right == node) {
				//set the current node's parrent's right child to the current node's left child
				node->parent->right = node->left;

				//set the left node's new parrent to the current node's parrent (if it is not null)
				if (node->left != nullptr) {
					node->left->parent = node->parent;
				}
				delete node;
				return true;
			}
			//if the node is the right node of the parrent
			else if (node->parent->left == node) {
				//set the current node's parrent's left child to the current node's left child
				node->parent->left = node->left;

				//set the left node's new parrent to the current node's parrent (if it is not null)
				if (node->left != nullptr) {
					node->left->parent = node->parent;
				}
				delete node;
				return true;
			}
			//if somehow the node wasnt deleted return false
			return false;
		}
		//if the node has 2 children
		else if (node->right != nullptr && node->left != nullptr) {
			//find the lowest node value of the right node tree
			Node<BST_T> * right_lowest_node = this->minimum_of_branch(node->right);

			//overwrite the current node with the right_lowest_node's data
			node->key = right_lowest_node->key;
			node->count = right_lowest_node->count;

			//remove the right lowest node now
			return this->remove(right_lowest_node);
		}
		else {
			return false;
		}
	}

	//get the minimum value of the BST
	BST_T min() {
		Node<BST_T> * node = this->minimum_of_branch(this->root_node);

		return node->key;
	}

	//get the maximum value of the BST
	BST_T max() {
		Node<BST_T> * node = this->maximum_of_branch(this->root_node);

		return node->key;
	}

	//returns the number of nodes in the tree
	int count_nodes() {
		return count_nodes(this->root_node);
	}

	//function overload for node pointer input
	int count_nodes(Node<BST_T> * node) {
		if (node == nullptr) {
			return 0;
		}

		return 1 + count_nodes(node->right) + count_nodes(node->left);
	}

	//traverses the node and returns a pointer to an array of the values ordered by how the BST was traversed
	BST_T * traverse(TraversalTypes type) {
		//new array which can store the same # of values as there are nodes
		BST_T * values = new BST_T[this->count_nodes()];

		//current index of the array that should be filled
		int current_index = 0;

		if (type == preorder) {
			//traverse using preorder
			traverse(this->root_node, values, current_index, type);
		}
		else if (type == postorder) {
			//traverse using preorder
			traverse(this->root_node, values, current_index, type);
		}
		else if (type == inorder) {
			//traverse using preorder
			traverse(this->root_node, values, current_index, type);
		}

		return values;
	}

	//overide for traverse
	void traverse(Node<BST_T> * node, BST_T * values, int & index, TraversalTypes & type) {
		//preorder order is root-> left -> right
		if (type == preorder) {
			if (node == nullptr) {
				return;
			}

			//add the value to the array
			values[index] = node->key;

			//increment the index
			index++;

			//traverse down the left subtree
			traverse(node->left, values, index, type);

			//traverse down the right subtree
			traverse(node->right, values, index, type);
			return;
		} 
		//postorder order is left -> right -> root
		else if (type == postorder) {
			if (node == nullptr) {
				return;
			}

			//traverse down the left subtree
			traverse(node->left, values, index, type);

			//traverse down the right subtree
			traverse(node->right, values, index, type);

			//add the value to the array
			values[index] = node->key;

			//increment the index
			index++;

			return;
		}
		//inorder order is left -> root -> right
		else if (type == inorder) {
			if (node == nullptr) {
				return;
			}

			//traverse down the left subtree
			traverse(node->left, values, index, type);

			//add the value to the array
			values[index] = node->key;

			//increment the index
			index++;

			//traverse down the right subtree
			traverse(node->right, values, index, type);
			return;
		}
	}
};