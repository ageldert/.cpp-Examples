/*
Binary Tree
This example builds a binary tree of strings through user entry. 
The tree can also be searched for a matching string, case-insensitive.
Implements a basic pointer-based binary tree.

--- Created by Aaron Geldert at the University of Miami
--- ECE 318 (Algorithms)
--- Copyright 2019. All Rights Reserved.
*/


#include <string>
#include <iostream>

using namespace std;

struct stringnode
{	string data;
	stringnode *left, *right;
	stringnode(string s)
	{ data = s;
	  left = NULL;
	  right = NULL; }
};

void add_node(string s, stringnode *&x)
{	if (x == NULL)		// root case
	{	x = new stringnode(s);
		return; }
	stringnode * ptr = x, * prev = NULL;
	while (ptr != NULL)	// navigate until we can add a new node
	{ 	if (ptr->data > s)
		{	prev = ptr;
			ptr = ptr->left; }
		else if (ptr->data < s)
		{	prev = ptr;
			ptr = ptr->right; }
		else
		{	cout << "Duplicate ignored.\n";
			return; }
	}
	if (prev->data > s)
		prev->left = new stringnode(s);
	else 
		prev->right = new stringnode(s);
}

void search(string s, stringnode *x)
{	while(true)
	{	if (x == NULL)
		{  	cout << "NO - Could not find " << s << ".\n";
		   	break; }
		if (x->data > s) x = x->left;
		else if (x->data < s) x = x->right;
		else
		{ 	cout << "YES - Found " << s << ".\n";
			return; }
	}
}

string ignorecase(string s)
{	int offset = 'a' - 'A';
	for (int i = 0; i < s.length(); i++)
	{	if (s[i] >= 'A' && s[i] <= 'Z')
			 s[i] = s[i] + offset; }
	return s;
}

void instructions()
{	cout << "Welcome! This program will first allow you to enter strings into a binary tree.\n";
	cout << "String entry is case insensitive and should not contain any whitespace.\n";
	cout << "To stop building the binary tree, enter a number.\n";
	cout << "Then, you may enter any string to search for. Enter another number to end the program.\n";
}

int main()
{	stringnode * root = NULL;
	instructions();
	string input;
	while(true)
	{	cout << "Enter a string: ";
		cin >> input;
		input = ignorecase(input);
		if (input[0] >= '0' && input[0] <= '9') break;
		add_node(input, root);
	}
	cout << "Done entering.\n";
	while(true)
	{	cout << "Search for a string: ";
		cin >> input;
		input = ignorecase(input);
		if (input[0] >= '0' && input[0] <= '9') exit(0);
		search(input, root);
	}
}
