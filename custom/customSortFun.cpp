/**
custom sort function could be function pointer == reference to the function using its name 
function object which is a class with operator "()" overloaded as the custom sort function.
*/

#include <iostream>
#include <algorithm>
#define pii pair<int, int>
using namespace std;
bool comp(pii a, pii b)
{
    if(a.second == b.second){
        if(a.first < b.first)
            return 1;
        return 0;
    }
    else if(a.second < b.second)
        return 1;
    return 0;
}

int main()
{
    int n;
    cin>>n;
    pii *ev = new pii[n];
    for(int i=0; i<n; i++)
        cin>>ev[i].first>>ev[i].second;
    sort(ev, ev+n, comp); // comp is a fucntion pointer.
    int maxEvs = 1;
    int eTime = ev[0].second;
    for(int i=1; i<n; i++){
        if(ev[i].first > eTime){
            eTime = ev[i].second;
            maxEvs +=1;
        }
    }
    cout<<maxEvs<< endl;
    return 0;
}
