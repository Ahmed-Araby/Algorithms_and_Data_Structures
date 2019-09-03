/*
finding bridges in a undirected graph 
*/
void dfs1(int node , int dad , vector<int> g[])
{
    id++;
    in[node]=low[node]=id;
    vis[node]=1;
    for(int i=0; i<g[node].size(); i++)
    {
        int child=g[node][i];
        if(child==dad)
            continue;
        if(vis[child])
        {
            low[node]=min(low[node] , in[child]);  // why this is enough
            continue;
        }
        else
        {
            dfs1(child , node , g);
            low[node]=min(low[node] , low[child]);
        }
    }
    return ;
}
void dfs2(int node , int dad , vector<int> g[] , vector<pair<int ,int> > &e)
{
    if(vis[node])
        return ;
    vis[node]=1;
    for(int i=0; i<g[node].size(); i++){
        int child=g[node][i];
        if(child==dad)
            continue;
        if(vis[child] && in[child]>in[node])  // this edge been relaxed before
            continue;

        if(in[node]<low[child])  // bridge we can't convert it
        {
            //cout<<"here"<< endl;
            e.push_back({child , node});
            e.push_back({node , child});
        }
        else
            e.push_back({node ,child});
        dfs2(child , node , g , e);
    }
    return ;
}
