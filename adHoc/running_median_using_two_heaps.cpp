/*
*https://www.youtube.com/watch?v=VmogG01IjYc&ab_channel=HackerRank
* in this video solution I guess we do not need to add any elemetn to the higher heap at all, 
 we just can keep adding to the lower heap and repalance them after every addition
*/
#include <bits/stdc++.h>
using namespace std;

void add(int x,
    priority_queue<int> &p,
    priority_queue<int, vector<int> , greater<int> > &s)
{
    // this addition method will always keep them replanced
    if(p.size() == s.size()){
        if(p.empty() || x <= s.top())
            p.push(x);
        else {

            p.push(s.top());
            s.pop();
            s.push(x);
        }
    }

    else {
        if(x >= p.top())
            s.push(x);
        else{
            s.push(p.top());
            p.pop();
            p.push(x);
        }
    }

    return ;
}

float getMedian(
    priority_queue<int> &p,
    priority_queue<int, vector<int> , greater<int> > &s)
{
    if(p.size() > s.size())
        return p.top();
    else
        return ((float)p.top() + s.top()) / 2;
}

vector<float> runningMedian(int *a, int n)
{
    /**
    max element in heap p should be
    less than or equal to the min element
    int the heap s.
    */
    priority_queue<int > p; // max heap
    priority_queue<int, vector<int> , greater<int> > s;  // min heap
    vector<float> med;

    for(int i=0; i<n; i++){
        add(a[i], p, s);
        float median = getMedian(p, s);
        med.push_back(median);
    }

    return med;

}

int main()
{
    int n;
    cin>>n;
    int *a = new int [n+2];
    for(int i=0; i<n; i++)
        cin>>a[i];

    vector<float> med = runningMedian(a, n);
    cout<<"medians are : "<< endl;
    for(int i=0; i<n; i++)
        cout<<med[i]<<" ";
    cout<< endl;
    return 0;
}
