#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct person
{	int ssn, bday, zip;
	string fn, ln;
	bool hasdog;
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
	if(p->hasdog) cout << "Dog owner" << endl;}

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
void FIND(node * root)
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
void ZIP(node * root)
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
void ALL(node * root)
{	string l;
	cout << "Enter last name: "; cin >> l;
	cout << "...searching for '" << l <<"'...\n";
	bool found = false;
	all(root, l, found);
	if(!found)	cout << "No matching persons found in database.\n";
}

void hasdog(node * n, string f, string l, bool &b)
{	if(n==NULL)	return;
	hasdog(n->left,f,l,b);
	if(n->data->fn == f && n->data->ln == l)
	{	b = true;
		n->data->hasdog=true;
		cout << "Recorded " << f << " " << l <<" is a dog owner.\n";}
	hasdog(n->right,f,l,b);}
void HASDOG(node * root)
{	string f, l;
	cout << "Enter first and last name: "; cin >> f;cin >> l;
	cout << "...searching for '" << f <<" "<< l <<"'...\n";
	bool found = false;
	hasdog(root, f, l, found);
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
void OLDEST(node * root)
{	person * old = oldest(root);
	if(old != NULL)	printOld(old);
	else cout << "\nDatabase is empty.\n";
}

int main()
{	node * root = NULL;
	ifstream fin("/home/218/database.txt");
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
		if(in[0]=='f'||in[0]=='F')	FIND(root);
		else if(in[0]=='z'||in[0]=='Z')	ZIP(root);
		else if(in[0]=='a'||in[0]=='A')	ALL(root);
		else if(in[0]=='h'||in[0]=='H')	HASDOG(root);
		else if(in[0]=='o'||in[0]=='O')	OLDEST(root);
		else if(in[0]=='e'||in[0]=='E')	exit(0);
		else cout << "Invalid input\n";
	}
}
