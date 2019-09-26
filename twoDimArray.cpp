#include <iostream>
#include "HW2.h"

using namespace std;

void input(twoDimArray<int> &A)
{
	char ans;
	cout << "Array currently " << A.getrows() << " x " << A.getcols();
	cout << "\nDo you wish to resize this array? Y/N\n";
	cin >> ans;	
	if(ans == 'Y'|| ans == 'y')
	{
		int rows, cols;
		cout << "Rows: "; cin >> rows;
		cout << "Cols: "; cin >> cols;
		A.resize(rows,cols);
	}
	for(int r=0; r<A.getrows(); r++)
	{
		for(int c=0; c<A.getcols(); c++)
		{
		  cout << r << ", " << c <<": ";
		  cin >> A.get(r,c); 
		}
	}
}

void print(twoDimArray<int> &A)
{
	cout << endl;
	for(int r=0; r<A.getrows(); r++)
	{
	  cout << "( ";
	  for(int c=0; c<A.getcols(); c++)
		cout << A.get(r,c) << " ";
	  cout << ")\n";
	}
	cout << endl;
}

void multiply(twoDimArray<int> &A, twoDimArray<int> &B, twoDimArray<int> &R)
{
	if(A.getcols() !=  B.getrows())
	{ cout << "Incorrect matrix dimensions!\n"; abort(); }
	R.resize(A.getrows(), B.getcols());
	for(int r=0; r<R.getrows(); r++)
		for(int c=0; c<R.getcols(); c++)
		{
			int sum=0;
			for(int k=0; k<R.getcols(); k++)
				sum += A.get(r,k) * B.get(k,c);
			R.get(r,c) = sum;
		}
}

int main()
{
	twoDimArray<int> A(2,2), B(2,2), C(1,1);
	cout << "Input array A:\n";
	input(A); print(A);
	cout << "Input array B:\n";
	input(B); print(B);
	multiply(A, B, C);
	cout << "Result of A * B:\n";
	print(C);
	cout << "Finished\n";
}
