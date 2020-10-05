string to_string(int num)
{
    stringstream cvt;
    cvt << num;
    string s;
    cvt >> s;
    return s;
}

int to_int(string s)
{
    stringstream cvt (s);
    int num =0;
    cvt >> num;
    return num;
}

void str_split(string s, char dlim, vector<string> &v)
{
    string tmp = "";
    // avoid [ and ]
    for(int i=1; i<s.size()-1; i++)
    {
    if(s[i]== dlim)
    {
        v.push_back(tmp);
        tmp = "";
    }
    else 
        tmp +=s[i];
    }
    if(tmp!="")
    v.push_back(tmp);
    return ;
}
