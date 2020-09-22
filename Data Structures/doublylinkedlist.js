/*
this could be enhanced by removing the node 
I believe in c++ they overload operators that provide instant access to 
the inner objects 
*/
class Node 
{
    constructor(val)
    {
        this.val = val;  // could be any thing 
        this.prev = null;
        this.next = null;
    }
}

class doublyLinkedList
{
    constructor()
    {
        this.head = null;
        this.tail = null;
        this.count = 0;
    }
    
    push(val)
    {
        var newNode = new Node(val);
        if(this.head==null)
        {
            this.head = newNode;
            this.tail = newNode;
        }
        
        else
        {
            this.tail.next = newNode;
            newNode.prev = this.tail;
            this.tail = newNode;
        }
        this.count+=1;
    }
    
    pop()
    {
        if(this.tail == this.head)
        {
            this.head = null;
            this.tail = null;
        }
        else 
            this.tail = this.tail.prev;
        // does the tail node get deleted automatically 
        this.count -=1;
    }
    
    deleteNode(node)
    {
        // in the middle 
        if(node.prev!=null && node.next !=null)
        {
            console.log("in the middle");
            node.prev.next = node.next;
            node.next.prev = node.prev; 
        }
        
        // first one 
        else if(node.prev == null && node.next!=null)
        {
            console.log("first one ");
            this.head = node.next;
            node.next.prev = null;
        }
        // last one
        else if(node.next == null && node.prev !=null)
        {
            console.log("last one ");
            node.prev.next = null;
            this.tail = node.prev;
        }
        
        // only one 
        else if(this.head === node && this.tail === node)
        {
            console.log("only one ")
            this.head = null;
            this.tail = null;
        }
        this.count -=1;
    }
    
    begin()
    {
        return this.head;
    }
    
    end()
    {
        return null;    
    }
    length()
    {
        return this.count;
    }
}
