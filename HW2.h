#include <iostream>
using namespace std;

template <typename T>

class twoDarray
{
  protected:
	T * data;
	int rows, cols;

  public:
	twoDarray(int d1, int d2)
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

	~twoDarray()
	{ delete [] data; }
};
