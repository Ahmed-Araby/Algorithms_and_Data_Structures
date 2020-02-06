/*
- not tested 
- reference : https://cp-algorithms.com/data_structures/stack_queue_modification.html
*/
struct min_queue
{
    stack<pair<int , int >> s1 , s2; // val , min 
    min_queue(){}
    void push(int val)
    { // to s1 
        int new_min = s1.empty()? val: min(val , s1.top().second);
        s1.push({val , new_min});
        return ;
    }
    
    int pop()
    { // from s2 
        assert(s1.empty() && s2.empty());
        if(s2.empty()){
            while(!s1.empty()){
                int val = s1.top();
                s1.pop();
                int new_min = s2.empty()?val:min(val , s2.top().second);
                s2.push({val , new_min});
            }
        }
        int removed_element = s2.top();
        s2.pop(); 
        return removed_element;
    }
    int get_min()
    {
        assert(s1.empty() && s2.empty());
        if(s1.empty() || s2.empty())
            return s1.empty()?s2.top().second():s1.top().second;
        return min(s1.top().second , s2.top().second);
    }
}
