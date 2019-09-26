#include <iostream>
#include <cstdlib>
#include <time.h>
#include <sys/resource.h>

using namespace std;

double get_cpu_time()
{ struct rusage ruse;
  getrusage(RUSAGE_SELF, &ruse);
  return ruse.ru_utime.tv_sec+ruse.ru_utime.tv_usec/1000000.0 + 
         ruse.ru_stime.tv_sec+ruse.ru_stime.tv_usec/1000000.0; }

void swap(string &x, string &y)
{
	string temp = x;
	x = y;
	y = temp;
}

void peek(string A[], int size)
{
	cout << endl;
	for(int k=0; k<5; k++)
		cout << A[k] << endl;
	cout << "...\n";
	for(int k=5; k>0; k--)
		cout << A[size-k] << endl;
	cout << endl;
}

string random_string(int length)
{
	string s = "";
	string const letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for(int k=0; k<length; k++)
		s+=letters[random()%26];
	return s;
}

void selection_sort(string A[], int size)
{
	for(int rep=0; rep<size-1; rep++)
	{
		int small = rep;
		for(int k=rep; k<size; k++)
		{
			if(A[k]<A[small])
				small = k;
		}
		swap(A[rep], A[small]);
	}	
}

void bubble_sort(string A[], int size)
{
	for(int rep=0; rep<size-1; rep++)
		for(int k=0; k<size-rep-1; k++)
			if(A[k+1]<A[k])
				swap(A[k],A[k+1]);
}

int main(int argc, char*argv[])
{
	srandomdev();
	int n;
	if(argc > 1)
		n = atoi(argv[1]);
	else
	{
		cout << "Defaulted to 1000 strings\n";
		n = 1000;
	}
	
	string *sSort = new string[n];
	string *bSort = new string[n];
	for(int k=0; k<n; k++)
	{
		sSort[k] = random_string(10);
		bSort[k] = sSort[k];
	}
	peek(sSort, n);

	double t1 = get_cpu_time();
	selection_sort(sSort, n); 
	double t2 = get_cpu_time();
	bubble_sort(bSort, n);
	double t3 = get_cpu_time();
	double ts = t2-t1, tb = t3-t2;

	cout << "Selection sorted array:";
	peek(sSort, n);
	cout << "Bubble sorted array:";
	peek(bSort, n);

	cout << "Time to complete selection sort: " << ts << " sec\n";
	cout << "   Time to complete bubble sort: " << tb << " sec\n";
	if(ts < tb)
		cout << "Bubble sort was " << tb/ts << " times slower than selection sort.\n";
	else 
		cout << "Selection sort was " << ts/tb << " times slower than bubble sort.\n";
}

