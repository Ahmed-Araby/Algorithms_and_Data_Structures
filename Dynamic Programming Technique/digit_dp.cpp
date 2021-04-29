/*
digit dp



5 5
0 5

10 5
0 5


15 5 
0 5 14


20 5
0 5 14 19


24 5
0 5 14 19 23

100 5
0 5 14 41 19 23 32 46 64 78 87 69 96  91 19 82 28 37 73 55 





*/

#include <bits/stdc++.h>
using namespace std;

int solve(int index, bool s, int rem,
          string &a, int k,
          int dp[10][2][10])
{
    if(index == a.size())
        return dp[index][s][rem] = rem == 0;

    int &ret = dp[index][s][rem];
    if(ret!=-1)
        return ret;

    ret  = 0;
    int curD = a[index]  - '0';

    for(int i=0; i<=9; i++)
    {
        if(!s && i>curD) // not allowed
            break;
        else{
            bool ts = i<curD;
            int trem = (rem + i) % k;
            ret += solve(index+1, ts | s, trem, a, k, dp);
        }
    }
    return ret;
}

int main()
{



    while(true){
        string a, b;
        cin>>b;
        int bb;
        cin>>bb;

        int k;
        cin>>k;

        int dp[10][2][10];
        for(int i=0; i<10; i++)
            for(int j=0; j<2; j++)
                for(int k=0; k<10; k++)
                    dp[i][j][k] = -1;

        /*
        num in range [a, b] inclusive
        digitSum(num) % k
        count num.

        */
        int tans = 0;
        for(int i=0; i<=bb; i++)
            if(i%k==0)
                tans +=1;

        int bans = solve(0, 0, 0, b, k, dp);
        //int aans = solve(0, 0, 0, a, k, dp);
        cout<<bans<<" "<<tans<< endl;
    }


}
