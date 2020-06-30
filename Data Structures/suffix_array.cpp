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

#include <bits/stdc++.h>
using namespace std;

struct comp
{
private:
    char *s;
    int h, n; // to be sorted in , already on h/2;
    int *group;

public:
    comp(char *_s , int _h, int *_group, int _n)
    {
        // assign address
        s = _s;
        h = _h;
        n = _n;

        //will have the changes reflected from the
        //out side

        group = _group;
    }

    void incH()
    {
        h*=2;
        return ;
    }

    bool operator()(int i , int j)
    {
        if(h==1)
        {
            // use the string
            if(s[i] < s[j])
                return true;
            else
                return false;
        }

        else{
            // use the group
            if(group[i] !=group[j])
                return group[i] < group[j];

            if(i+h/2 >=n)
                return true;
            else if(j+h/2 >=n)
                return false;

            if(group[i+h/2] < group[j+h/2])
                return true;
            else
                return false;
        }
    }
};

int* build_suffix_array(char *s, int n)
{
    int *index = new int [n];
    int *group = new int [n];

    // initial suffix
    for(int i=n-1; i>=0; i--)
        index[i] = i;


    // start by sorting on the first character
    comp custom_comp(s, 1, group, n);

    bool allDiff = false;

    while(!allDiff)
    {
        cout<<"inside"<< endl;
        allDiff = true;
        int gID = 1;
        sort(index, index+n, custom_comp);

        // we need to distribute the groups
        // again , how do do so !?
        // I believe we can use the custom comp again
        // nope this is the wrong way to do it
        group[index[0]] = 1;
        for(int i=1; i<n; i++){
            bool les = custom_comp(index[i-1], index[i]);
            bool gret = custom_comp(index[i] , index[i-1]);

            cout<<les<<" "<<gret<< endl;
            if(!les && !gret){
                // equal
                allDiff = false;
                group[index[i]] = gID;
            }
            else{
                gID +=1;
                group[index[i]] = gID;
            }
        }

        // compare on larger portion NOW
        custom_comp.incH();
    }

    return index;  // don't worry , dynamically allocated array
}

string printS(char *s, int i , int n)
{
    string tmp ="";
    for(; i<n; i++)
        tmp.push_back(s[i]);
    return tmp;
}
int main()
{
    cout<<"start "<< endl;
    int n;
    char *s = new char[n+1];

    s[n] = '\n';  // end of line

    cout<<"enter the string length "<< endl;
    cin>>n;
    cout<<"enter the string "<< endl;
    cin>>s;

    //cout<<int(s[5])<< endl;
    //return 0;

    cout<<"string  is : "<<s<< endl;

    // get suffix array
    int *index = build_suffix_array(s, n);

    cout<< endl;
    cout<<"sorted suffixes are "<< endl;
    cout<< endl;

    for(int i=0; i<n; i++)
        cout<<printS(s, index[i], n)<< endl;

    cout<<"we are done "<< endl;

    return 0;
}

/*
// Suffix array algorithms (nlognlog and nlogn) are from my oach Mohamed Abd Wahab, aka Fegla

#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

#define all(v)      ((v).begin()), ((v).end())
#define sz(v)     ((int)((v).size()))
#define clr(v, d)   memset(v, d, sizeof(v))
#define rep(i, v)   for(int i=0;i<sz(v);++i)
#define lp(i, n)    for(int i=0;i<(int)(n);++i)
#define lpi(i, j, n)  for(int i=(j);i<(int)(n);++i)
#define lpd(i, j, n)  for(int i=(j);i>=(int)(n);--i)
typedef long long ll;

void buildSuffixArraySlow(string str) {
  map<string, int> suffix_idx_map;
  vector<string> suffixes;

  for (int i = 0; i <= (int) str.size(); i++) {
    string suffix = str.substr(i, str.size() - i);
    suffix_idx_map[suffix] = i;
    suffixes.push_back(suffix);
  }
  sort(suffixes.begin(), suffixes.end());
  for (int i = 0; i < (int) suffixes.size(); i++)
    cout << suffixes[i] << "\t" << suffix_idx_map[suffixes[i]] << "\n";
}

////////////////////////////////////////////////////
////////////////////////////////////////////////////

// Use N_LOGN_LOGN and N_LOGN to switch between 2 codes if needed

const int MAXLENGTH = 5000;

char str[MAXLENGTH + 1];      //the string we are building its suffix array
int suf[MAXLENGTH + 1];//the sorted array of suffix indices
int group[MAXLENGTH + 1];//In ith iteration: what is the group of the suffix index
int sorGroup[MAXLENGTH + 1];//temp array to build grouping of ith iteration

struct comp//compare to suffixes on the first 2h chars
{
  int h;
  comp(int h)
  : h(h) {
  }

  bool operator()(int i, int j) {
    if (group[i] != group[j])     // previous h-groups are different
    return group[i] < group[j];
    return group[i + h] < group[j + h];
  }
};

void print_suffix(int suf_pos, int n) {
  for (int j = suf_pos; j < n - 1; ++j)  // n-1 is string length NOT n
    cout << str[j];
}

void buildSuffixArray() {
  int n;  //number of suffixes = 1+strlen(str)
  //Initially assume that the group index is the ASCII
  for (n = 0; n - 1 < 0 || str[n - 1]; n++)
  suf[n] = n, group[n] = str[n];//code of the first char in the suffix

  sort(suf, suf + n, comp(0));//sort the array the suf on the first char only
  sorGroup[0] = sorGroup[n - 1] = 0;

  //loop until the number of groups=number of suffixes
  for (int h = 1; sorGroup[n - 1] != n - 1; h <<= 1) {
    sort(suf, suf + n, comp(h));  //sort the array using the first 2h chars

    for (int i = 1; i < n; i++)//compute the 2h group data given h group data
    sorGroup[i] = sorGroup[i - 1] + comp(h)(suf[i - 1], suf[i]);

    for (int i = 0; i < n; i++)//copy the computed groups to the group array
    group[suf[i]] = sorGroup[i];


    if (true) {  // For print
      for (int i = 0; i < n; i++) {
        print_suffix(suf[i], n);

        cout << "\t" << suf[i] << "\n";
      }
      cout << "\n";
    }
  }
}

int main() {
#ifndef ONLINE_JUDGE
  //freopen("test.txt", "rt", stdin);
#endif

  cin >> str; // aaabaca
  buildSuffixArray();

  return 0;
}
*/
