/*
implementing hash table with liner probing
for collection resolution

*** very important observation ***

having a cell in the table empty
is an indication that there is no key , with similear hashing value
or smaller one have ever made it to this point , neither by hashing nor
hashing with collision,
and it's not an indicator for having the lower cells empty, they could been taken with
very simple direct adding operation.

before accessing a value of some key , we need to make sure
that the key is exist first other wise.
*/
#include <bits/stdc++.h>
using namespace std;

struct node
{
    int state; // -1 removed , 0 empty , 1 exist
    string key; // depend on the use, it have to be template
    int value; // depend on the use, it have to be template
    node()
    {
        state = 0; // empty
    }
    node(int _state, string _key, int _value)
    {
        state = _state;
        key = _key;
        value = _value;
        return ;
    }
};
struct hashTable
{
    int len, counter;
    node *table;
    hashTable(int _len)
    {
        len = _len;
        table = new node[len];
        counter = 0;
    }

    /*
    hash table features
    1- add
    2- exist
    3- delete

    we need to handle
    - collision with linear probing
    we need to have
    - hashing function
    */

    int hashFunction(string key)
    {
        /*
        simple hashing function
        use the Asci value of the char
        */

        int H = 0;
        for(int i=0; i<key.size(); i++)
            H = (H + int(key[i]) % len  ) % len;
        return H;
    }

    bool add(string key, int value)
    {
        bool added = 0;
        int index = hashFunction(key);
        int Oindex = index;
        do
        {
            if(table[index].state == 0 ||
               table[index].state == -1 ||
               table[index].key == key)
            {
                table[index].state = 1;
                table[index].key  = key;
                table[index].value = value;
                added = 1;
                counter +=1;
                break;
            }

            index = (index + 1) % len;
        }while(index!=Oindex);

        return added;
    }

    bool remove(string key)
    {
        bool removed = 0;
        int index = hashFunction(key);
        int Oindex = index;
        do
        {
            if(table[index].state == 1 &&
                table[index].key == key)
            {
               table[index].state = -1;
               counter-=1;
               removed = 1;
               break;
            }
            /* if true there is no point from searching after this
            as no element with the same hashing or smaller have ever made it
             to this point*/
            else if(table[index].state == 0)
                break;
            index = (index + 1) % len;
        }while(Oindex !=  index);
        return removed;
    }

    bool exist(string key)
    {
        int index = hashFunction(key);
        int Oindex = index;

        do
        {
            if(table[index].state == 1 &&
               table[index].key == key)
                return 1;
            else if(table[index].state == 0)
                break;
            index = (index + 1) % len;
        }while(Oindex != index);

        return 0;
    }

    int getValue(string key)
    {
        if(exist(key) == false)
            throw "key is not exist ";

        int index = hashFunction(key);
        int Oindex = index;
        do
        {
            if(table[index].state == 1 &&
               table[index].key == key)
                return table[index].value;
            index = (index + 1) % len;
        }while(Oindex != index);
    }

    int getLength()
    {
        return len;
    }
    int getSize()
    {
        return counter;
    }

    /*
    for testing
    */
    void printTable()
    {
        cout<<"************************************ "<< endl;
        for(int i=0; i<len; i++)
        {
            if(table[i].state == 0)
            {
                cout<<"index "<<i<<" empty"<< endl;
            }

            else if(table[i].state == 1)
            {
                cout<<"index "<<i<<" "<<table[i].key <<" "<<table[i].value<< endl;
            }
            else{
                cout<<"index "<<i<<" deleted"<< endl;
            }
        }
        cout<<"************************************ "<< endl;
        cout<< endl;
        return ;
    }
    void isExist(string key)
    {
        cout<<"key : "<<key<<" is "<<(exist(key)==1?"exist":"not exist")<< endl;
        return ;
    }

};

int main()
{
    hashTable t(10);

    // add elements
    t.add("ahmed", 1234);
    t.add("mom", 123455);
    t.add("nrmeen", 12121);
    t.add("nrmeen", 11);

    t.printTable();

    // remove elements
    t.remove("ahmed");

    t.printTable();

    // add element again
    //t.add("ahmed", 1311998);
    //t.add("ahmde", 1321998);
    t.printTable();


    // test exist
    t.isExist("ahmed");
    return 0;
}
