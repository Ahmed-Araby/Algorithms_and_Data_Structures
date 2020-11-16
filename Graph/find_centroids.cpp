#include <bits/stdc++.h>
using namespace std;
int n;

/*
the second defs force the graph to have only one centroid.
https://codeforces.com/contest/1406/problem/C
*/
int dfs1(int node , int dad,
        vector<int> *g, vector<int>& c)
{
    // job of this dfs is to return the size of the tree rooted at node
    // get the centroids of the tree
    int totSz = 1; //  me
    bool is_centroid = true;

    for(int i=0; i<g[node].size(); i++){
        int child = g[node][i];
        if(child == dad)
            continue;
        int childTreeSz = dfs1(child, node, g, c);
        totSz += childTreeSz;
        if(childTreeSz > n /2)
            is_centroid = false;
    }
    // sub tree of my dad and upward .
    if(n-totSz > n/2)
        is_centroid = false;
    if(is_centroid)
        c.push_back(node);
    return totSz;
}

int dfs2(int node, int dad, int c2, vector<int> *g)
{
    // aim of this dfs is to get leaf node from the the second centroid
    if(g[node].size()==1){
        // cut
        cout<<node<<" "<<dad<< endl;
        return node;
    }
    for(int i=0; i<g[node].size(); i++){
        int child = g[node][i];
        if(child == dad || child == c2)
            continue;
        return dfs2(child, node, c2, g);
    }
}
int main()
{
    int t;
    cin>>t;
    while(t--){
        cin>>n;

        // tree
        vector<int> g[n+1];
        for(int i=0; i<n-1; i++){
            int a, b;
            cin>>a>>b;
            g[a].push_back(b);
            g[b].push_back(a);
        }

        vector<int> c;
        dfs1(1, -1, g, c);

        if(c.size() == 1){
            int node = c[0];
            cout<<node<<" "<<g[node][0]<< endl;
            cout<<node<<" "<<g[node][0]<< endl;
        }
        else{
            int leaf = dfs2(c[0], -1, c[1], g);
            // wire
            cout<<leaf<<" "<<c[1]<< endl;
        }
    }
    return 0;
}
