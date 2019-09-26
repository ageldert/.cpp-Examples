/*
Two Dimensional Array (header)

This code example defines the class for a two dimensional resizeable array, using a typename template.
The two dimensional array and its operations are implemented with (a pointer to) a single array. 
See twoDimArray.cpp for more example code.

--- Created by Aaron Geldert at the University of Miami
--- ECE 218 (Data Structures)
--- Copyright 2018. All Rights Reserved.
*/

#include <iostream>
using namespace std;

template <typename T>

class twoDimArray
{
  protected:
	T * data;
	int rows, cols;

  public:
	twoDimArray(int d1, int d2)
	{	rows = d1; cols = d2;
		data = new T[rows*cols];	}
	T & get(int r, int c)
	{	if(r<0||r>=rows||c<0||c>=cols)
		{ cout << "Index out of bounds\n" << "Given r=" << r << ", c=" << c << endl;
		  cout << "\nBounds are 0 to " << rows << " rows, 0 to " << cols <<" cols\n";
		  abort(); }
		return data[r*cols + c];	}

	int getrows()
	{	return rows; }
	int getcols()
	{	return cols; }

	void resize(int newrows, int newcols)
	{
		int smallest_size = rows*cols;
		rows = newrows; cols = newcols;
		T * newdata = new T[newrows*newcols];
		if(newrows*newcols < smallest_size) smallest_size = newrows*newcols;
		for(int k=0; k<smallest_size; k++)
			newdata[k] = data[k];
		delete [] data;
		data = newdata; }

	~twoDimArray()
	{ delete [] data; }
};
