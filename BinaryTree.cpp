/*
Binary Tree Database
This example builds a binary tree of persons and their data.
Makes use of recursive methods to navigate the binary tree.
Database is read in from exampleDatabase.txt, available in the .cpp-Examples repo.

--- Created by Aaron Geldert at the University of Miami
--- ECE 218 (Data Structures)
--- Copyright 2018. All Rights Reserved.
*/

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct person
{	int ssn, bday, zip;
	string fn, ln;
	bool hasDog;
	person(int s, int b, string f, string l, int z)
	{	ssn=s; bday=b; fn=f; ln=l; zip=z, hasdog=false;}
	int get_yr()
	{	return bday/10000;}
	int get_mon()
	{	return bday/100%100;}
	int get_day()
	{	return bday%100;}
	bool isOlderThan(person *&x)			//ref isnt always for changing values, just reduce copying of data
	{	if(get_yr() < x->get_yr())
			return true;
		else if(get_yr() > x->get_yr())
			return false;
		else
		{	if(get_mon() < x->get_mon())
				return true;
			else if(get_mon() > x->get_mon())
				return false;
			else
			{	if(get_day() < x->get_day())
					return true;
				else return false;
			}
		}
	}
	};

struct node
{	person * data;
	node * left, * right;
	node(person*p)
	{	data = p;
		left=NULL; right=NULL;}};

void printAll(person * p)
{	cout << endl << p->fn <<" "<< p->ln;
	cout << "\nDOB: " << p->get_mon() <<" "<< p->get_day() <<" "<< p->get_yr() << endl;
	cout << "SSN: " << p->ssn << "\tZip: " << p->zip << endl;
	if(p->hasDog) cout << "Dog owner" << endl;}

void printName(person * p)
{	cout << endl << p->fn <<" "<< p->ln <<"\n";}

void printOld(person * p)
{	cout << "\nOldest person in database:\n" << p->fn <<" "<< p->ln;
	cout <<"\nZip: " << p->zip << endl;
	cout << endl;}

bool in_order(person *&first, person *&second)	//checks if first person belongs first alphabetically
{	if(first->ln == second->ln)
		if(first->fn <= second->ln)
			return true;
	else if(first->ln < second->ln)
		return true;
	else return false;}

void insert_person(node *&n, person *&p)
{	if(n==NULL)
	{	n = new node(p);
		return;}
	node * ptr = n; node * prev = NULL;
	while(ptr!=NULL)
	{	prev=ptr;
		if(in_order(p,ptr->data))
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}
	if(in_order(p,prev->data))
		prev->left = new node(p);
	else
		prev->right = new node(p);
}

void make_tree(node *&root, ifstream &fin)
{	int s, b, z;
	string f, l;
	person * p;
	while(!fin.fail() && !fin.eof())
	{	fin >> s >> b >> f >> l >> z;
		p = new person(s,b,f,l,z);
		insert_person(root, p);}
	cout << "Database loaded.\n";
}

void find(node * n, string f, string l, bool &b)
{	if(n==NULL)	return;
	find(n->left,f,l,b);
	if(n->data->fn == f && n->data->ln == l)
	{	b = true;
		printAll(n->data);}
	find(n->right,f,l,b);}
void findName(node * root)
{	string f, l;
	cout << "Enter first and last name: "; cin >> f;cin >> l;
	cout << "...searching for '" << f <<" "<< l <<"'...\n";
	bool found = false;
	find(root, f, l, found);
	if(!found)	cout << "No matching persons found in database.\n";
}

void zip(node * n, int z, bool &b)
{	if(n==NULL)	return;
	zip(n->left,z,b);
	if(n->data->zip==z)
	{	b = true;
		printName(n->data);}
	zip(n->right,z,b);}
void findZip(node * root)
{	int z;
	cout << "Zip code: "; cin >> z;
	cout << "...searching for residents in " << z <<"...\n";
	bool found = false;
	zip(root, z, found);
	if(!found)	cout << "No residents in given zip code.\n";
}

void all(node * n, string l, bool &b)
{	if(n==NULL)	return;
	all(n->left,l,b);
	if(n->data->ln == l)
	{	b = true;
		printAll(n->data);}
	all(n->right,l,b);}
void findAll(node * root)
{	string l;
	cout << "Enter last name: "; cin >> l;
	cout << "...searching for '" << l <<"'...\n";
	bool found = false;
	all(root, l, found);
	if(!found)	cout << "No matching persons found in database.\n";
}

void hasDog(node * n, string f, string l, bool &b)
{	if(n==NULL)	return;
	hasDog(n->left,f,l,b);
	if(n->data->fn == f && n->data->ln == l)
	{	b = true;
		n->data->hasDog=true;
		cout << "Recorded " << f << " " << l <<" is a dog owner.\n";}
	hasDog(n->right,f,l,b);}
void setHasDog(node * root)
{	string f, l;
	cout << "Enter first and last name: "; cin >> f;cin >> l;
	cout << "...searching for '" << f <<" "<< l <<"'...\n";
	bool found = false;
	hasDog(root, f, l, found);
	if(!found)	cout << "No matching persons found in database.\n";
}

person *oldest(node * n)
{	if(n==NULL)	return NULL;
	person * result = n->data;
	person * oldl = oldest(n->left);
	if(oldl != NULL && oldl->isOlderThan(result))
		result = oldl; 
	person * oldr = oldest(n->right);
	if(oldr != NULL && oldr->isOlderThan(result))
		result = oldr; 
	return result;
}
void findOldest(node * root)
{	person * old = oldest(root);
	if(old != NULL)	printOld(old);
	else cout << "\nDatabase is empty.\n";
}

int main()
{	node * root = NULL;
	ifstream fin("exampleDatabase.txt");		// data file for the database
	if(fin.fail())
	{	cout << "File could not be opened.";
		exit(0);}	
	make_tree(root, fin);
	string in;
	if(root==NULL) cout << "Database is empty.\n";
	cout<<"Search/filter data with the following commands:\n\t-Find (searches for a name)\n\t-Zip (filters by zip code)\n\t-All (finds all with a lastname)\n\t-Hasdog (records a dog owner)\n\t-Oldest (finds the oldest)\n\t-Exit (exit program)\n";
	while(true)
	{	cout << "Command: ";
		cin >> in;
		if(in[0]=='f'||in[0]=='F')	findName(root);
		else if(in[0]=='z'||in[0]=='Z')	findZip(root);
		else if(in[0]=='a'||in[0]=='A')	findAll(root);
		else if(in[0]=='h'||in[0]=='H')	setHasDog(root);
		else if(in[0]=='o'||in[0]=='O')	findOldest(root);
		else if(in[0]=='e'||in[0]=='E')	exit(0);
		else cout << "Invalid input\n";
	}
}
