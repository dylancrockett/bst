#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <codecvt>
#include <time.h>
#include <fstream>
#include "BST.hpp"

using namespace std;

//function forward declarations
template <typename T>
void postorder_print_bst(Node<T> * node, bool show_null = false, wstring prefix = L"", bool is_left = false);

BST<int> bst_from_file(string filepath);

int get_int_input();

wstring get_string_input();

template<typename T>
void print_array(T * arr, int n);

std::wstring s2ws(const std::string& str);

int main(int argc, char **argv) {
	//force console to write utf16 text
	_setmode(_fileno(stdout), _O_U16TEXT);

	//init random seed
	srand(int(time(nullptr)));

	//create BST
	BST<int> tree;

	if (argc == 1) {
		//add random values to the bst if no file to read from was given
		for (int i = 0; i < 25; i++) {
			tree.insert(rand() % 100 + 1);
		}
	}
	else if (argc == 2) {
		//overwrite bst with one read from file
		try {
			tree = bst_from_file(argv[1]);
		}
		catch (...) {
			//catch the read file error
			system("pause");
			return 1;
		}
	}
	else {
		//if more than 1 arguments are given
		cout << "Too many arguments given!" << endl;
		system("pause");
		return 1;
	}


	wstring response = L"";

	//user interface loop
	do {
		wcout << L"The following is the current structure of the binary tree: " << endl << endl;
		wcout << L"null" << endl;
		postorder_print_bst(tree.root_ptr(), true);
		wcout << endl << L"<> Select an Action <>" << endl;
		wcout << L"[1] Search the tree for a value." << endl;
		wcout << L"[2] Insert a value into the tree." << endl;
		wcout << L"[3] Remove a value from the tree." << endl;
		wcout << L"[4] Get the minimum/maximum value of the tree." << endl;
		wcout << L"[5] Traverse the tree." << endl;
		wcout << L"[6] Exit Program" << endl;
		wcout << L"Enter your choice (1-5): "; wcin >> response;

		if (response == L"1") {
			system("cls");
		
			//ask the user for the value they would like to search for
			wcout << L"Enter the value you would like to search the BST for." << endl;
			int val = get_int_input();

			wcout << endl << L"Searching the BST for the value '" << val << "'..." << endl << endl;
			Node<int> * node_ptr = tree.search(val);

			//if the node is null the value did not exist 
			if (node_ptr == nullptr) {
				wcout << L"The value entered could not be found in the BST." << endl;
				system("pause");
			}
			else {
				wcout << L"Value found, below is the info of the node which stores the value '" << val << L"':" << endl;
				wcout << L"Self Address: " << node_ptr << endl;
				wcout << L"Parrent Address: " << node_ptr->parent << endl;
				wcout << L"Right Child Address: " << node_ptr->right << endl;
				wcout << L"Left Child Address: " << node_ptr->left << endl;
				wcout << L"Key: " << node_ptr->key << endl;
				wcout << L"Count: " << node_ptr->count << endl << endl;
				system("pause");
			}
		}
		else if (response == L"2") {
			system("cls");

			//ask the user for the value they would like to insert
			wcout << L"Enter the value you would like to insert into the BST." << endl;
			int val = get_int_input();

			wcout << endl << L"Inserting '" << val << "' into the BST..." << endl << endl;
			Node<int> * node_ptr = tree.insert(val);

			//node info output
			wcout << L"Value inserted, below is the info of the node which now stores the value '" << val << L"':" << endl;
			wcout << L"Self Address: " << node_ptr << endl;
			wcout << L"Parrent Address: " << node_ptr->parent << endl;
			wcout << L"Right Child Address: " << node_ptr->right << endl;
			wcout << L"Left Child Address: " << node_ptr->left << endl;
			wcout << L"Key: " << node_ptr->key << endl;
			wcout << L"Count: " << node_ptr->count << endl << endl;
			system("pause");

			system("cls");
		}
		else if (response == L"3") {
			system("cls");
			
			//ask the user for the value they would like to insert
			wcout << L"Enter the value you would like to remove from the BST." << endl;
			int val = get_int_input();

			wcout << endl << L"Removing '" << val << "' from the BST..." << endl << endl;
			bool success = tree.remove(val);

			//node info output
			if (success) {
				wcout << L"Value '" << val << "' has been removed from the BST." << endl;
				system("pause");
			}
			else {
				wcout << L"Value '" << val << "' did not exist in the BST, and therefore could not be removed." << endl;
				system("pause");
			}

			system("cls");
		}
		else if (response == L"4") {
			system("cls");
			
			wcout << "Please enter either 'min' or 'max' to search for the minimum or maximum value in the BST. (defaults to max if invalid response is given):" << endl;
			wstring str = get_string_input();

			if (tree.count_nodes() == 0) {
				//if there are no nodes in the tree
				wcout << L"The BST is empty and therefor cannot have a minimum or maximum value, please enter some values into the BST and try again!" << endl;
				system("pause");
			}
			else if (str == L"min") {
				//return the minimum of the BST
				wcout << L"The minimum value of the BST is '" << tree.min() << L"'." << endl;
				system("pause");
			}
			else {
				//return the maximum of the BST
				wcout << L"The maximum value of the BST is '" << tree.max() << L"'." << endl;
				system("pause");
			}

			system("cls");
		}
		else if (response == L"5") {
			system("cls");

			wcout << "Please enter either 'preorder', 'postorder', or 'inorder' to traverse the BST. (defaults to preorder if invalid response is given):" << endl;
			wstring str = get_string_input(); wcout << endl;

			if (str == L"postorder") {
				//return the array of values ordered by postorder transversal
				wcout << L"BST Values ordered by postorder trasversal:" << endl;
				print_array<int>(tree.traverse(TraversalTypes::postorder), tree.count_nodes());
				system("pause");
			}
			else if (str == L"inorder") {
				//return the array of values ordered by inorder transversal
				wcout << L"BST Values ordered by inorder trasversal:" << endl;
				print_array<int>(tree.traverse(TraversalTypes::inorder), tree.count_nodes());
				system("pause");
			}
			else {
				//return the array of values ordered by preorder transversal
				wcout << L"BST Values ordered by preorder trasversal:" << endl;
				print_array<int>(tree.traverse(TraversalTypes::preorder), tree.count_nodes());
				system("pause");
			}

			system("cls");
		}
		else if (response == L"6") {
			wcout << L"Exiting Program..." << endl;
			system("pause");
			//exit program
			return 0;
		}
		else {
			system("cls");
			wcout << L"Invalid selection entered, please enter a valid selection." << endl;
			system("pause");
		}

		response = L"";
	} while (true);
}

//prints a bst given the root node - useful for tree debugging and tree visualization
template <typename T>
void postorder_print_bst(Node<T> * node, bool show_null, wstring prefix, bool is_left) {
	if (node != nullptr) {
		//node prefix
		std::wcout << prefix;

		//branch based on left-right node
		std::wcout << (is_left ? L"├──" : L"└──");

		//print the value of the node
		std::wcout << node->key << L" (" << node->count << L") " << std::endl;

		//continue to the next level of the tree
		postorder_print_bst(node->left, show_null, prefix + (is_left ? L"│   " : L"    "), true);
		postorder_print_bst(node->right, show_null, prefix + (is_left ? L"│   " : L"    "), false);
	}
	else {
		//show null nodes if this is true
		if (show_null) {
			//node prefix
			std::wcout << prefix;

			//node branch
			std::wcout << (is_left ? L"├──" : L"└──");

			//null node
			std::wcout << L"null" << endl;
		}
	}
}

//returns a BST from the contents of a file (only accepts a file with a list of integers)
BST<int> bst_from_file(string filepath) {
	wcout << L"Creating BST from the contents of '" << s2ws(filepath) << L"'." << endl;

	//bst to be returned
	BST<int> bst;

	//line temp storage
	string line;

	//line counter
	int current_line = 1;

	//file
	ifstream bstfile;
	bstfile.open(filepath);

	//read until end of file
	while (!bstfile.eof())
	{
		//gets the next line of the file and stores it in string
		getline(bstfile, line); // Saves the line in STRING.

		try {
			//convert the line into an integer
			bst.insert(stoi(line));
		}
		//catch any conversion exceptions
		catch (...) {
			//error output
			wcout << L"Error Reading File '" << s2ws(filepath) << L"' on line " << current_line << L": Could not convert line to integer!" << endl;
			throw "Error Reading File";
		}

		//increase the line count
		current_line++;
	}

	//close the file
	bstfile.close();

	return bst;
}

//get an integer from the user
int get_int_input() {
	bool answered = false;
	wstring temp;
	int response = 0;

	while (!answered) {
		wcout << L"> "; wcin >> temp;
		try {
			response = stoi(temp);
			answered = true;
		}
		//catch stoi conversion exceptions
		catch (...) {
			wcout << endl << L"Invalid input given, please enter an integer!" << endl;
			continue;
		}
	}

	return response;
}

//get a wstring from the user
wstring get_string_input() {
	wstring response = L"";

	wcout << L"> "; wcin >> response;

	return response;
}

//print a dynamic array given the number of elements it contains
template<typename T>
void print_array(T * arr, int n) {
	wcout << L"[ ";

	for (int i = 0; i < n; i++) {
		if (i != n - 1) {
			wcout << arr[i] << ", ";
		}
		else {
			wcout << arr[i];
		}
	}

	wcout << L" ]" << endl;
}

//string converter functions from wstring to string, and string to wstring
wstring s2ws(const string& str) {
	using convert_typeX =  codecvt_utf8<wchar_t>;
	wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.from_bytes(str);
}