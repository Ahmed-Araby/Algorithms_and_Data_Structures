#include <iostream>
using namespace std;
class a
{
public:
	int x, y;
	a() {};
	a(int _x, int _y) {
		x = _x;
		y = _y;
	}
};

int main()
{
	/*
	int* a = new int[2];
	a[0] = 1;
	a[1] = 2;

	int b = 2;
	int c = 3;
	cout << "stack grows downward from high address to low address " << endl;
	cout << endl;
	cout << "dynamic array a first index position in the stack  " << &a << endl << endl;
	cout << "address that a contain -- address from the heap  " << a << endl << endl; // this address have integer variable
	cout << "variable b position in the stack  " << &b << endl << endl;
	cout << "variable c position in the stack " << &c << endl << endl;	
	*/

	int b;
	a* arr = new a[2];
	arr[0].x = 1;
	arr[1].y = 2;
	
	cout << "before assignment" << endl;
	cout << arr << endl; // same address in the heap 
	cout << &arr << endl;
	cout << &b << endl;
	cout << "after assignment " << endl;
	arr[0] = a(-1,-2);
	cout << arr << endl;   // same address in the heap 
	cout << arr[0].x << arr[0].y << endl;

	
	/*
	so what actually happens is 
	arr is pointer 
	that hold addresses from the heap 
	but arr it self as variable is located in the stack 
	
	so 

	arr -- address from the heap that point at object 
	&arr -- address of arr(pointer) in the stack 
	arr[0] --- dereference the heap address to access the object
	$arr[0] -- address of the heap 
	$arr[1] -- address of the heap 


	assignment operator 
	https://www.geeksforgeeks.org/copy-constructor-vs-assignment-operator-in-c/

	*/
	return 0;
	 
}
