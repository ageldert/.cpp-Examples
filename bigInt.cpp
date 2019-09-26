/*
Big Integer

This code example creates a BigInt class with some basic arithmetic functionality.
BigInt inherits from vector, storing each digit as a separate int. All operations are performed digit by digit.
BigInt can therefore greatly exceed the ~4 billion values of a single 32-bit int.

--- Created by Aaron Geldert at the University of Miami
--- ECE 218 (Data Structures)
--- Copyright 2018. All Rights Reserved.
*/


#include <vector>
#include <iostream>
using namespace std;

class BigInt: public vector<int>
{
public:

  void become(string input)
  {	clear();
	for(int k=input.length()-1; k>=0; k--)
	{  int digit = input[k] - '0';
	   if(digit <0 || digit >9)
	   {	cerr << "could not read a digit\n";
		exit(1);}
	   else
		push_back(digit);		
	}
  }

  void print()
  {	for(int k=size()-1; k>=0; k--)
		cout << at(k);
	cout << endl;
  }

  int get_digit(int pos)
  {	if(pos>=size())
		return 0;
	return at(pos);
  }

  int set_digit(int pos, int val)
  {	if(pos==size())
		push_back(val);
	else
		at(pos)=val;
  }
  
  bool equals_one()
  {	bool b = true;
	if(size() >1)
		b = false;
	if(at(size()-1) != 1) 
		b = false;
	return b; 
  }

  void remove_extra_zeros()
  {	int pos=size()-1;
	while(get_digit(pos)==0 && pos>0)
	{	pop_back();
		pos--;
	}
  }

  void decrement()
  {	int pos = 0;
	while(get_digit(pos)==0)
	{	set_digit(pos,9);
		pos++;
	}
	set_digit(pos, get_digit(pos)-1);
	remove_extra_zeros();
  }

  void copy(BigInt &x)
  {	clear();
	for(int k=0; k<x.size(); k++)
		push_back(x.at(k));
  }

  void add(BigInt &a, BigInt &b)
  {	clear();
	int pos=0, carry=0, sum=0;
	while(pos < a.size() || pos < b.size() || carry!=0)
	{	sum = a.get_digit(pos) + b.get_digit(pos) + carry;
		push_back(sum%10);
		carry = sum/10;
		pos++;
	} 
 }

  void subtract(BigInt &a, BigInt &b)
  {	clear();
	int pos=0, borrow=0;
	while(pos < a.size()||pos < b.size())
	{	int diff = a.get_digit(pos)-b.get_digit(pos)-borrow;
		if(diff < 0)
		{ diff +=10;
		  borrow=1;
		}
		else borrow=0;
		push_back(diff);
		pos++;
	}
	if(borrow>0)
	{	cout <<"Invalid (negative) result.\n";
		exit(0);
	}
	remove_extra_zeros();
  }

  void multiply(BigInt &a, BigInt &b)
  {	clear();
	int carry=0, sum=0, dig=1, topdig, botdig;
	while(carry>0 || dig <= a.size()*2 || dig <= b.size()*2)
	{
		topdig=dig; botdig=1;
		sum = carry;
		while(topdig>=0)
		{
			sum += a.get_digit(topdig-1)*b.get_digit(botdig-1);
			topdig--; botdig++;
		} 
		push_back(sum%10); 
		carry = sum/10; 
		dig++;
	}	
	remove_extra_zeros();
  }

  void factorial(BigInt a) 
  {	clear();
	BigInt temp;
	BigInt result("1");
	temp.copy(a); 
	while(true)
	{	a.decrement(); 
		if(a.equals_one()) break;
		result.multiply(temp,a);
		temp.copy(result);
	}
	copy(result);
  }
  
  BigInt()
  {}

  BigInt(string s)
  {	become(s); }
};

void check(string input)			//check if wanting to exit
{	if(input[0] == 'x' || input[0] == 'X')
	{	cout<<"Exiting program.\n";
		exit(0); }
}

int main()
{ BigInt c("0");
  cout <<"BigInt Calculator: Enter positive integers only. Functions include +, -, *, !.\n";
  cout <<"Type x to exit\n";
  string input;
  char op;
  while(true)
  {
	do
	{	cout<<"Operation: ";
		cin >> input;
		check(input);
		op = input[0];
	}	while(op!='+' && op!='-' && op!='*' && op!='!');
	
	if(op == '!')
	{	cout<<"Number:\n";
		cin >> input;
		check(input);
		BigInt a(input);
		c = a;	
		c.factorial(a); }
	else
	{	cout<<" First number:\n";
		cin >> input;	check(input);
		BigInt a(input);
		cout<<"Second number:\n";
		cin >> input;	check(input);
		BigInt b(input);
		
		if(op == '+')
			c.add(a,b);
		else if(op == '-')
			c.subtract(a,b);
		else if(op == '*')
			c.multiply(a,b);
	}
		cout << "Answer:\n";
		c.print();
  }	
}
