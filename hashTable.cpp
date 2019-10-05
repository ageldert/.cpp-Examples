



#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

struct Place
{	Place * next;
	int code, pop, road;
	string state, name;
	double area, lat, lon, dist;
	Place(int c, string s, string n, int p, double a, double la, double lo, int r, double d)
	{	next = NULL;
		code = c; pop = p; road = r;
		state = s; name = n;
		area = a; lat = la; lon = lo, dist = d;
	}
	
	void display()
	{	cout << "----------------------------\n";
		cout << name << ", " << state << endl;
		cout << setw(14) << "Location ID: " << code << "\tRoad ID: " << road << endl;
		cout << setw(14) << "Population: " << pop << endl;
		cout << setw(14) << "Area: " << area << " square miles" << endl; 
		cout << setw(14) << "Latitude: " << lat << " N" << endl;
		cout << setw(13) << "Longitude:" << lon << " E" << endl;
		cout << setw(14) << "Distance: " << dist << " miles" << endl;
		cout << "----------------------------\n";
	}
};

int hash(string n)
{	int h = 2999;
  	for (int i = 0; i < n.length(); i++)
    	h = h * 797 + n[i];
  	if (h < 0) h = -h;
  	return h;
}

string trimSpaces(string s)
{	int i = s.length()-1;
	while (s[i] == ' ') i--;	
	return s.substr(0,i+1);
}

class Hashtable
{  protected:
	int size;
	Place * * table;

   public:
	Hashtable(int s)
	{	size = s;
		table = new Place * [size];
		for (int i=0; i<size; i++)
			table[i] = NULL;
	}

	void addPlace(Place * x)
	{	string key = x->state;
		key += x->name;
		int pos = hash(key) % size;
		x->next = table[pos];
		table[pos] = x;
//		cout << "Added " << x->state << " " << x->name << " at " << pos << endl;
	}

	void stats()
	{	cout << "\n\n------ HASH TABLE STATISTICS ------\n";
		const int longest = 15;		// estimate max # entries per hash value
		int counts[longest+1];
		for (int i=0; i<= longest; i++)
			counts[i] = 0;		// initialize our length counts to 0
		for (int j=0; j<size; j++)
		{	Place * temp = table[j];
			int len = 0;
			while (temp != NULL)
			{	len++;
				temp = temp->next;
			}
			if(len>longest) len = longest;
			counts[len]++;		// we found 1 more linked list of that length
		}
		for (int y=0; y<=longest; y++)
		{	cout << setw(3) << y << ": "
				<< setw(9) << counts[y] << endl;
		}
		cout << "------\n";
	}

	void search(string s, string n)
	{	int pos = hash(s+n) % size;
		bool found = false;
		Place * p = table[pos];
		while(p != NULL && !found)
		{	if(p->state == s)
			{	if(p->name == n)
				{	cout << "Matching location found:\n";
					p->display();
					found = true;
				}
			}
			p = p->next;
		}
		if(!found) cout << "No matching location found.\n";
	}

	~Hashtable()
	{	for (int i=0; i<size; i++)	//for each entry in the hash table
		{	Place * x = table[i];
			while (x != NULL)	//store the next (could be NULL), delete, then move the next
			{	Place * n = x->next;
				delete x;
				x = n;
			}	
		}
		delete [] table;
	}
};

void processLine(string line, Hashtable &data)
{
	int c, p, r;
	string s, n;
	double a, la, lo, d;
	
	c = atoi(line.substr(0,8).c_str());
	s = line.substr(8,2);
	n = trimSpaces(line.substr(10,49));
	p = atoi(line.substr(59,7).c_str());
	a = atof(line.substr(66,14).c_str());
	la = atof(line.substr(81,10).c_str());
	lo = atof(line.substr(90,11).c_str());
	r = atoi(line.substr(101,5).c_str());
	d = atof(line.substr(106,8).c_str());

	Place * gotcha = new Place(c,s,n,p,a,la,lo,r,d);
	data.addPlace(gotcha);
}

bool validateState(string &input)
{
	if(input[0] == '0') exit(0);
	if(input.length()==2)
	{	for(int i=0; i<2; i++)
		{	if(input[i]<'A' || input[i]>'Z')
				input[i] -= 32;		// switch lower to upper case	
			if(input[i]<'A' || input[i]>'Z')
				return false;		// still not upper case letters
		}	
	}
	else return false;	// not a 2 character input
	return true;		// valid 2 letters
}

void search(Hashtable &data)
{
	string stateInput, nameInput;
	bool flag = false;
	while(true)
	{	cout << "\nEnter state (2 letters), or type 0 to exit:\n\t";
		cin >> stateInput;
		flag = validateState(stateInput);
		if(flag) break;
		cout << "Invalid input, try again.\n";
	}
	flag = false;
	cout << "Enter name, or type 0 to exit:\n\t";
	cin.ignore();
	getline(cin,nameInput);
	nameInput = trimSpaces(nameInput);

	if(nameInput[0] == '0') exit(0);

	data.search(stateInput,nameInput);
}

int main()
{
	ifstream fin("/home/www/class/een318/named-places.txt");
	if(fin.fail())
	{	cerr << "Failed to access .txt\n";
		exit(0);
	}
	Hashtable data(8192);
	string line;
	getline(fin,line);	// first line is bogus
	int count = 0;
	while(true)
	{
		getline(fin,line);
		if(fin.fail()) break;
		processLine(line, data);
		count++;
	}

	data.stats();
	cout << "Total entries: " << count << endl;

	cout << "\nSearch the database of named locations in the USA.\n"
		<< "Name entry is case sensitive and whitespace is processed.\n";
	while(true) search(data);

}
