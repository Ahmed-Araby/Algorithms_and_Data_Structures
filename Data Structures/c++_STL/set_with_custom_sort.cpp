#include <bits/stdc++.h>
using namespace std;

class cell
{
public:
	int x, y;
	int imp;
	cell(int _x, int _y, int _imp)
	{
		x = _x;
		y = _y;
		imp = _imp;
	}

	void display() const
	{
		cout << "object content " << endl;
		cout << this->x<< " " << this->y << " " << this->imp<< endl;
		return;
	}
 
};

// build functor class 
class comp
{
public:
	bool operator() (const cell& obj1, const cell& obj2) const
	{
		/*
		bigger impoertance first
		left to right 
		up to down 
		cell order 
		*/

		if (obj1.imp != obj2.imp)
			return obj1.imp > obj2.imp;
		
		else if (obj1.x != obj2.x)
			return obj1.x < obj2.x;

		return obj1.y < obj2.y;
	}


};

int main()
{
  set<cell, comp> s;
  
}
