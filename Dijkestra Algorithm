// UNdirected graph 
// Dijkestra O(V^2)

// dIJKESTRA (n^2) Adjacency matrix
/*#include <iostream>
using namespace std;
int n;
int dis[1005] , vis[1005] , prv[1005];
int g[1005][1005];
void dijkestra(int s)
{
    // initial
    dis[s]=0;
    prv[s]=s;
    while(1)
    {
        /*
        complexity O(n*2n)
        first loop go n
        second loop go n
        and all of them keep going till all be visited or no more
        close nodes
        so it`s considered as another n
        at all N*2N= O(n^2);
        */
        // index is the node itself
        /*int idx=-1 , tdis=INT_MAX;
        // pick closest node
        for(int i=1; i<=n; i++)
            if(!vis[i] && dis[i]<tdis)
            {
                tdis=dis[i];
                idx=i;
            }
        if(idx==-1)
            break;
        vis[idx]=1; // I process from here

        // relax == build connection if it make our path shorter
        for(int i=1; i<=n; i++){
            /*cout<<idx<<" "<<i<< endl;
            cout<<dis[i]<<" "<<dis[idx]<<" "<<g[idx][i]<<endl;
            cout<<dis[idx]+g[idx][i]<< endl;
            cout<< endl;*/
            /*if(dis[i]>dis[idx]+g[idx][i]){
                dis[i]=dis[idx]+g[idx][i]; // relax
                prv[i]=idx; // path to me
            }
        }
    }
    return ;
}
int main()
{
    cin>>n;
    for(int i=0; i<=n; i++)
        dis[i]=INT_MAX;

    int f , t , w;

    for(int i=0; i<=n; i++)
    for(int j=0; j<=n; j++)
    g[i][j]=10000;

    while(cin>>f>>t>>w  && f && t && w)
    {
        // directed graph
        g[f][t]=w;
    }
    dijkestra(1);
    cout<<"shortest path for all from source node "<<1<< endl;
    for(int i=1; i<=n; i++)
        cout<<dis[i]<<" ";
    cout<< endl;
    cout<<"path for node 6 from source node"<<1<< endl;
    int i=6;
    while(prv[i]!=i)
    {
        cout<<prv[i]<<" ";
        i=prv[i];
    }
    cout<< endl;
    return 0;
}

// DIJKESTRA O(Vlog(E))
// O(Nlog(n)) Dijkestra implementation
/*
we will acheive this by
iterating just throw the connections to the closest node we picked
and get the closest node on log n using instead of iterating throw them all to get it
that happing using adjacency list for graph
and priority queue to store the nodes that is not visited yet and have connection with the source
we will put in it the source with distance = 0
*/
#include <bits/stdc++.h>
using namespace std;
#define pi pair<int , int>
struct node
{
    int id , w;
    node()
    {
    }
    node(int _id , int _w)
    {
        id=_id;
        w=_w;
    }
    bool operator <(const node &obj) const
    {
        return w>obj.w;
    }
};
int dis[1005] , vis[1005] , prv[1005];
void dijkestra(int s , vector<vector<pi> > &g)
{
    priority_queue<node> q;
    q.push(node(s , 0));
    dis[s]=0;
    prv[s]=s;
    while(!q.empty())
    {
        //pick most close
        node tmp=q.top();
        q.pop();
        s=tmp.id;
        // relax
        cout<<s<< endl;
        for(int i=0; i<g[s].size(); i++)
        {
            int child=g[s][i].first;
            int w=g[s][i].second;
            cout<<child<<" "<<w<<" "<<endl;
            cout<<dis[child]<<" "<<dis[s]<<" "<<endl;
            cout<< endl;
            if(dis[child]>dis[s]+w)
            {
                dis[child]=dis[s]+w;
                q.push(node(child , dis[child]));
                prv[child]=s;
            }
        }
    }
    return ;
}
int main()
{
    int n;
    cin>>n;
    for(int i=0; i<=n; i++)
        dis[i]=10000;
    int f , t , w;
    vector<vector<pi> > g(1005);
    while(cin>>f>>t>>w && f && t && w)
    {
        g[f].push_back({t , w});
    }
    /*for(int i=0; i<g[1].size(); i++)
        cout<<g[1][i].first<<" "<<g[1][i].second<< endl;*/

    dijkestra(1 , g);
    for(int i=1; i<=n; i++)
        cout<<dis[i]<<" ";
    cout<< endl;
    int i=6;
    while(prv[i]!=i)
    {
        cout<<prv[i]<<" ";
        i=prv[i];
    }
    cout<< endl;
}
