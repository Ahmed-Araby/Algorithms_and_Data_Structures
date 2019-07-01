const int sz=100005;
int z[sz];
void z_algo(string &s)
{
    int l=0 , r=0;
    int n=(int)s.size();
    for(int i=1; i<n; i++)
    {
        // smart use of what I did matched before (slide)
        if(i<=r)
            z[i]=min(z[i-l] , r-i+1); // length
        // brute force  , match from i with the prefix of the original string
        for(int j=z[i]; i+j<n && s[j]==s[i+j]; ++j)  // index
        ++z[i];
        // update the slide  so I can make use of it for next i's
        if(z[i]+i-1>r){
            l=i;
            r=z[i]+i-1;
        }
    }
    return;
}
