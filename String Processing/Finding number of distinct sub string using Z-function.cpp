// [TO DO : find the unique substring itself]
#include <bits/stdc++.h>
using namespace std;
const  int sz=1005;
int z[sz];
int z_function(string s)
{
    /*
    the point of reversing : is any sub string have to include the new added char
    and max make sure to tell me about all the repeated substring that this new char build
    the whole new string is always added
    */
    for(int i=0; i<s.size(); i++)
        z[i]=0;

    reverse(s.begin() , s.end());
    int l=0 , r=0;
    for(int i=1; i<s.size(); i++)
    {
        // smart usage
        if(i<=r)
            z[i]=min(z[i-l] , r-i+1);

        for(int j=z[i]; j<s.size() && i+j<s.size(); j++){
            if(s[j]==s[i+j])
                z[i]++;
            else
                break;
        }
        if(i+z[i]-1>r){
            l=i;
            r=i+z[i]-1;
        }
    }
    // custom
    int maxi=0;
    for(int i=1; i<s.size(); i++)
        maxi=max(maxi , z[i]);
    // this substring and all smaller of it that start on it's start are repeated
    return s.size()-maxi;
}
int z_fun(string s)
{
    /*
    this iterative manner enable me to delete only what interest me which is end on the latest added
    letter
    */
    string tmp="";
    int ans=0;
    for(int i=0; i<s.size(); i++){
        tmp+=s[i];
        ans+=z_function(tmp);
    }
    return ans;
}
int main()
{
    int t;
    cin>>t;
    while(t--){
        string s;
        cin>>s;
        int ans2=0;
        //ans1=naieve(s);
        ans2=z_fun(s);
        cout<<ans2<< endl;
    }

    return 0;
}
