/*#include<bits/stdc++.h>
using namespace std;
#define oo 105*50+5 // max value if the my path will go throw all the edges and more
int main()
{
    // build the graph
    int n;
    cin>>n;
    int f , t , w;
    int g[105][105] , path[105][105]; // use the adjacency matrix to represent the connection of the graph (weighted)
    for(int i=0; i<105; i++)
        for(int j=0; j<105; j++){
        g[i][j]=oo; // inf
        if(i==j)
            path[i][j]=i;  //  take care form that situation
        else
            path[i][j]=-1;
        }
    while(cin>>f>>t>>w && f!=0)
    {
        // directed graph
        g[f][t]=w;
        path[f][t]=f; // so I came to j form i as initial decision
    }
    // base case
    for(int i=1; i<=n; i++)
    g[i][i]=0; // me to my self
    // apply floyd algo  it will work in the original graph
    // take care of the self loops and the 0 cost of some vertex to it self
    for(int k=1; k<=n; k++)  // intermedite node to use to go from i ti j if it better or possible
    {// do we have to start it form 1 ????!!!  I think no we don`t it`s just intermedite  node
        // but it have to be the first loop , why ?? I think to apply the dp technique so every thinG I need is ready
        // we can do as a third dimension but we don`t need to and this is better for memory
        for(int i=1; i<=n; i++) // node i source
        {
            for(int j=1; j<=n; j++) // node j distnation
            {
                //g[i][j]=min(g[i][j] , g[i][k]+g[k][j]); // direct or using k as intermedite that itself using also intermedite nodes
                if(g[i][k]+g[k][j]<g[i][j]){
                    g[i][j]=g[i][k]+g[k][j]; // sp
                    // previous technique
                    // ******************** important *************************
                    // in case of intermedite nodes between k and J that I need to get
                    path[i][j]=path[k][j]; // so I come to j using k them I cam to K using some other node and we
                    // will keep going down until we reach node i it self
                }
            }
        }
    }
    cout<<"All pair shortest paths is : "<< endl;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++)
        cout<<g[i][j]<<" ";
        cout<< endl;
    }

    // displaying the path itself
    // do the same technique of previous like the 1D DJ
    // if sp==oo so no  path
    int ff , tt;
    cout<<"enter you source"<< endl;
    cin>>ff;
    cout<<"enter you distination"<< endl;
    cin>>tt;
    vector<int> p;
    if(g[ff][tt]==oo)
        cout<<"there is no path here"<< endl;
    else
    {
        p.push_back(tt);
        while(path[ff][tt]!=tt)  // condition mean source ! destination
        {
            //cout<<ff<<" "<<tt<<" "<<path[ff][tt]<< endl;
            p.push_back(path[ff][tt]);
            tt=path[ff][tt]; // new distination that I need to reach
            //cout<<endl<<ff<<" "<<tt<<" "<<path[ff][tt]<< endl;
        }
    }
    cout<< endl;
    for(int i=p.size()-1; i>=0; i--)
        cout<<p[i]<<" ";
    cout<< endl;
    return 0;
}
*/
// strongly connected components graph
// implementation of floyd that till me if I have a connection or not
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int f , t , w;
    bool g[105][105]; // will just represent connection
    for(int i=1; i<=n; i++)
        g[i][i]=1; // each node is connected to it self

    // we can do so by dfs from each node to the to all possible nodes which will be (n*(n+e)) I think it`s better than floyd
    while(cin>>f>>t && f!=0)
    {
        g[f][t]=1; // connection
    }
    // apply floyd to get the connections that depend on the intermedite vertix
    for(int k=1; k<=n; k++) // intermedite
        for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
        g[i][j]|=(g[i][k]&g[k][j]); // direct path or using j as intermedite node
    cout<<"connection"<< endl<<endl;
    for(int i=1; i<=n; i++){
    for(int j=1; j<=n; j++)
        cout<<g[i][j]<<" ";
    cout<< endl;
    }

    // get components (each vertex that have path from me to it and from it to me ) it will symetrically do so
    // with the node that do so with me cuz it will use me to go to them and they will use me to go to it
    vector<int> com(105 , -1);  // each component will have index to it starting from 1
    int index=0;
    for(int i=1; i<=n; i++){
    if(com[i]!=-1)
    continue;  // already in a component
        index++; // my new component
    com[i]=index;
    for(int j=1; j<=n; j++)  // if we have directed connection go and back so we are in the same component
    {
        if(g[i][j] && g[j][i])
            com[j]=index; // same component
    }
    }
    cout<< endl;
    // display components
    for(int i=1; i<=n; i++)
        cout<<com[i]<<" ";
    cout<< endl;
    cout<<"done"<< endl;
    // build the strongly connected component graph 
    bool s[105][105];
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
        if(g[i][j] && com[i]!=com[j]) //  they are connected so connect their components 
            s[com[i]][com[j]]=1;
    return 0;
}
