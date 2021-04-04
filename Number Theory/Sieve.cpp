// sieves implementation to find primes up to number n
#include <bits/stdc++.h>
using namespace std;
bool a[2000001];
int main()
{
    /*
    here I just used first optimization
    we still can do more optimization 
    by having just the odd numbers in the array 
    */
    int n;
    long long res=0;
    cin>>n;
    // find all primes up to n
    for(int i=3; i<=n; i+=2) //just mark odds
        a[i]=1;  // candidate prime
    /*
    possible mistake 
    if we started form 2 here he will walk only throw even numbers so if will not ever give us true
    and all odds will be kept marked so it will some them all 
    */
    for(int i=3; i*i<=n; i+=2)
        if(a[i]==1)  // prime
            //  mark all it's proper multiples
            for(int j=i*i; j<=n; j+=2*i) // i is odd ans odd^2 is also odd and odd+2 is also odd so I just jump on odd numbers , between j ans i^2 is reachable before me
                a[j]=0; // not prime
    res=2;  // fact
    for(int i=3; i<n; i+=2)  // just odd is candidate , even number by nature are divisible by 2 so they are not primes
        if(a[i])
        res+=i;
    cout<<res<< endl;
    return 0;
}
