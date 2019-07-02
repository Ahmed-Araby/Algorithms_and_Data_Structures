#include <iostream>
using namespace std;
int mod_exp(int num, int p, int mod)
{
	// base case 
	if (p == 0)
		return 1;
	// divide and conquer , modular multiplication theory 
	// even  power 
	if (p % 2 == 0)
	{
		int tmp = mod_exp(num, p / 2, mod);
		return (tmp*tmp)&mod;
	}
	// odd power 
	else
		return ((num%mod)*mod_exp(num, p - 1, mod)) % mod;
}
int main()
{
	int n, p, m;
	cin >> n;  //  base 
	cin >> p; // power 
	cin >> m; // modulus 
	cout << mod_exp(n, p, m) << endl;
	return 0;
}



////////////////////////////////////////////////////////////////////////////////////
// simpler on e
int fast_pow(int n , int p)
{
    if(p==0) return 1;
    if(p==1) return n;
    int tmp=fast_pow(n , p/2);
    tmp=tmp*tmp;
    if(p%2)
        tmp*=n;
    return tmp;
}
