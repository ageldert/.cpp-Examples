#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<double> stack;

void print_stack()
{
	if(stack.size() == 0)
		cout << "Stack empty.";
	else
	{
		cout << "Stack:\n";
		for (int k=0; k < stack.size(); k++)
			cout << stack.at(k) << endl;
	}
	cout << endl;
}

void start_calc()
{
	while(stack.size() > 0)
		stack.pop_back();	
}

void deal_with(double x)
{
	stack.push_back(x);
}

void deal_with(string s)
{
	if(stack.size() >= 2)
	{
		double b = stack.back(); stack.pop_back();
		double a = stack.back(); stack.pop_back();

		if(s=="+")
			stack.push_back(a+b);
		else if(s=="-")
			stack.push_back(a-b);
		else if(s=="*")
			stack.push_back(a*b);
		else if(s=="/")
		{
			if(b==0)
			{
				cout << "Error: cannot divide by zero! Stack cleared.\n";
				start_calc();
			}
			else
				stack.push_back(a/b);
		}
		else if(s=="%")
		{
			int a1 = (int)a; int b1 = (int)b;
			stack.push_back(a1%b1);
		}
	}
	else cout << "Error: stack only has " << stack.size() << " number(s)\n";
}

double answer()
{
	return(stack.back());
}

void main()
{
	cout << "Reverse Polish Calculator:\nInput numbers or operators (+ -  * / %)\nType '=' to evaluate\nType 'end' to quit\nType 'print' to see full stack\n";
	while(true)
	{
		string input;
		cout << ": ";
		cin >> input;
		
		if(input[0] >= '0' && input[0] <= '9')
		{
			double d = atof(input.c_str());
			deal_with(d);
		}
		else if(input[0] == 'e' || input[0] == 'E')
			break;
		else if(input[0] == 'p' || input[0] == 'P')
			print_stack();
		else if(input == "=")
			cout << "Answer: " << answer() << endl;
		else 
			deal_with(input);
	}
}
