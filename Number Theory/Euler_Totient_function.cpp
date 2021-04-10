/*
eular totient function / PHI
THIS IMPLEMENTATION IS NOT TESTED.
*/


#include<bits/stdc++.h>
using namespace std;

int gcd(int a, int b)
{
    if(b==0)
        return a;
    return gcd(b, a%b);
}
void Eular_totient(int n, int &phi, int *coPrime)
{
    for(int i=0; i<=n; i++)
        coPrime[i] = -1;
    coPrime[2] = (gcd(n, 2) == 1);
    coPrime[3] = (gcd(n, 3) == 1);
    phi = 1; // for 1

    for(int i=2; i<=n; i++)
    {
        //cout<<i<<" "<<coPrime[i]<< endl;
        if(n%i==0)
            coPrime[i] = 0;
        if(coPrime[i] == -1)
            coPrime[i] =1;
        if(coPrime[i]==1)
            phi+=1;
        // we may use primes only for marking, after all any num will be composed of some primes.
        for(int j=i+i; j<=n; j+=i){
            if(coPrime[j]==1 || coPrime[j]==-1)
                coPrime[j] = coPrime[i];
        }
    }
    return ;
}

int main()
{
    while(1){
        int n;
        cin>>n;
        int phi = 0;
        int *coPrime =new int [n + 2];
        Eular_totient(n, phi, coPrime);

        cout<<"# of CoPrimes is : "<<phi<<endl;
        for(int i=1; i<=n; i++){
            if(coPrime[i])
                cout<<i<<": is CoPrime "<<endl;
        }

        cout<< endl;
        delete [] coPrime;
    }
    return 0;
}
