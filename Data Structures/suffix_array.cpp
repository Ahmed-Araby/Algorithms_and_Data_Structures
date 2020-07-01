/*
[my thoughts - understanding -
    miss understanding - doubts]
- the whole idea of the sorting algo here
    is to skip the complexity of comparing 2 strings
    in linear time using the observation of
    having ranks for our suffix that we will iterate throw
    them to do linear comparison

- suffix array
    sorted array of suffixed of some string
    and include the index of the beginning
    of each suffix in the original string

- take care of complexity of
    comparing strings in sorting

- we don't need to select the strings
    to be compared during the grouping
    as they will be pushed to each other
    exchanging indexes to express the right order


    no the very first step decide though
    as we do very normal sort depending on the
    first char which represent out starting point

    - do we swap after comporison!!???
    yes it's just a normal sort but on specific
    number of chars using the grouping as auxlary
    tool to sort

    sort on 1 char
    ad 1
    ab 1
    ac 1

    b  2
    c  3
    d  4

    sort on 2 chars
    if groups are different so the order
    is already known from the group int comp

    if equal groups then we need to use 2H chars
    my index + h = start index of some
    suffix that is sorted in h chars

    smaller length string is always smaller
    in case that  my index + h is out of bounds
- over load the operator as the inner sort function

- at the very first I will need the string
    then we will just need the group array

- take care of a[0] and a[index[0]] they are very error pruning

will take the object and do so
bool res = obj(p1 , p2);

# algo structure

- string
- index of each suffix
- group for each suffix attached to it's index
- user defined comparator

*/

/*
    Data Structure: [Suffix Array], string processing
    complexity: O(N log(n) log(n))
    Author: Ahmed Araby

    resources:
*/

#include <bits/stdc++.h>
using namespace std;

struct comp
{
private:
    char *s;
    int n, *suffix_rank, h;
public:
    comp(char *_s, int _n, int _h, int *_suffix_rank)
    {
        s = _s;
        n = _n;
        h = _h;

        // it will get changes reflected from the outside
        suffix_rank = _suffix_rank;
    }

    void inc_h()
    {
        h*=2;
    }

    bool operator()(int suffix1_index, int suffix2_index)
    {
        if(suffix_rank[suffix1_index] != suffix_rank[suffix2_index])
            return suffix_rank[suffix1_index] < suffix_rank[suffix2_index];

        // compare based on h chars
        if(suffix1_index + h/2 >= n)
            return true;
        else if(suffix2_index + h/2 >=n)
            return false;
        else if(suffix_rank[suffix1_index + h/2] < suffix_rank[suffix2_index + h/2])
            return true;
        return false;
    }
};

int * build_suffix_array(char *s, int n)
{
    int * suffix_rank    = new int [n];
    int * suffix_array   = new int [n];
    int * suffix_rank_c = new int [n];

    // initialize
    for(int i=0; i<n; i++){
        suffix_array[i] = i;

        // sort on h = 1
        suffix_rank[i] = int(s[i]);
    }

    comp custom_cmp(s, n, 1, suffix_rank);
    bool allDiff = false;

    while(!allDiff)  // O(log(n)) at max
    {
        allDiff = true;

        custom_cmp.inc_h();
        sort(suffix_array, suffix_array+n, custom_cmp);

        // re rank suffixes
        suffix_rank_c[suffix_array[0]] = 1;
        for(int i=1; i<n; i++){
            bool less_than = custom_cmp(suffix_array[i-1] , suffix_array[i]);
            if(!less_than){
                // equal [think about it ;)]
                suffix_rank_c[suffix_array[i]] = suffix_rank_c[suffix_array[i-1]];
                allDiff = false;
            }
            else
                suffix_rank_c[suffix_array[i]] = suffix_rank_c[suffix_array[i-1]]+1;
        }

        // reflect new groups
        // absence of the copy array was my bug As i was changing the ranking
        // investigate this bug in more depth !!!!!
        for(int i=0; i<n; i++)
            suffix_rank[i] = suffix_rank_c[i];
        //here we can intercept the sorting
        //based on h chars of the suffixes
    }
    return suffix_array; // [don't worry it's dynamically allocated]
}

string print_s(int s , int e, char *a)
{
    string tmps = "";
    for(; s<e; s++)
        tmps.push_back(a[s]);
    return tmps;
}
int main()
{
    int n;
    cin>>n;
    char *s = new char[n];
    cin>>s;

    int *suffix_array = build_suffix_array(s, n);
    cout<<"[Sorted suffixes]"<< endl;
    cout<< endl;
    for(int i=0; i<n; i++)
        cout<<print_s(suffix_array[i] , n, s)<< endl;
    cout<< endl;
    cout<<"[we are done]"<< endl;
    return 0;
}

