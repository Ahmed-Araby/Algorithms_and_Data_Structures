/*
I believe that we do not have to get the smallest factor any factor will do
*/
#include <bits/stdc++.h>
using namespace std;
int *fact_sieve(int n)
{
    int *SPF = new int [n+2];
    for(int i=0; i<=n; i++)
        SPF[i] = 0;
    for(int i=4; i<=n; i+=2) SPF[i] = 2;
    SPF[2] = 2;

    for(int i=3; i*i<=n; i++)
    {
        if(SPF[i]==0){
            SPF[i] = i;
            for(int j=i*i; j<=n; j+=i)
                SPF[j] = i;
        }
    }

    return SPF;
}

vector<int> getPF(int *SPF, int n, int x)
{
    vector<int> v;
    if(x>n) return v;
    while(SPF[x] !=x){
        v.push_back(SPF[x]);
        x = x/SPF[x];
    }
    v.push_back(x);
    return v;
}

void disp(vector<int> pfs)
{
    cout<<"PRIME FACTOR ARE"<< endl;

    for(int i=0; i<pfs.size(); i++)
        cout<<pfs[i]<<" ";
    cout<< endl;
    return ;
}

int main()
{
    int n;
    cin>>n;
    int x;
    cin>>x;

    int *SPF = fact_sieve(n);
    vector<int> pfs = getPF(SPF, n, x);
    disp(pfs);
    return 0;
}
