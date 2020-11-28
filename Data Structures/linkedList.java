package dataStructures;

import org.jetbrains.annotations.NotNull;

class node  // package - private
{
    /*
    * node is the building block
    * of my doubly linked list */
    public int value;
    // pointers, actually in java theses are reference holders
    public node prev = null;
    public node next = null;

    node(){}
    node(int Pvalue){
        value = Pvalue;
    }
}

/*
* functionality are taken from c++ STL library
* */

public class linkedList {
    node start=null; // reference of the first element in the chain.
    node end=null; // reference of the last element in the chain.
    int count = 0;
    public linkedList(){}

    public void validateLinkedList()
    {
        if(count == 0){
            System.out.println("empty linked list");
            System.exit(1);
        }
    }

    public int back()
    {
        validateLinkedList();
        return end.value;
    }

    public int front()
    {
        validateLinkedList();
        return start.value;
    }

    public node begin()
    {
        validateLinkedList();
        return start;
    }

    public node end()
    {
        validateLinkedList();
        return end;
    }

    public int size()
    {
        return count;
    }

    public void push_back(int value)
    {
        if(count==0)
            start = end = new node(value);
        else{
            node newNode = new node(value);
            end.next = newNode;
            newNode.prev = end;
            end = newNode;
        }
        count+=1;
    }

    public void pop_back()
    {
        if(count==0){
            System.out.println("empty queue");
            System.exit(1);
        }
        else if(count == 1)
            start = end = null;
        else{
            end = end.prev;
            end.next = null;
            // there is no variabel that refere to the deleted element
            // so JVM will garbage collect it.
        }
        count -=1;
    }

    public void push_front(int value)
    {
        if(count == 0)
            start = end  = new node(value);
        else{
            node newNode = new node(value);
            newNode.next = start;
            start.prev = newNode;
            start = newNode;
        }
        count +=1;
    }
    public void pop_front()
    {
        if(count == 0){
            System.out.println("empty Queue");
            System.exit(1);
        }
        else if(count == 1)
            start = end = null;
        else{
            start = start.next;
            start.prev = null;
        }
        count -=1;
    }

    public void insert(int index, int value)
    {
        if( index < 0 || index > count ) {
            System.out.println("invalid position");
            System.exit(1);
        }

        node newNode = new node(value);
        if(index == 0)
        {
            // start case
            newNode.next = start;
            if(start!=null)
                start.prev = newNode;
            else
                end = newNode;
            start = newNode;
        }
        else if(index == count){
            // end case
            end.next = newNode;
            newNode.prev = end;
            end = newNode;
        }
        else
        {
            // middle case
            node tmpPtr = start;
            for(int i=0; i<index-1; i++)
                tmpPtr = tmpPtr.next; // will point at the element before index
            // place new node in between
            newNode.next = tmpPtr.next;
            tmpPtr.next.prev = newNode;

            tmpPtr.next = newNode;
            newNode.prev = tmpPtr;
        }
        count +=1;
        return ;
    }

    public boolean remove(final int value)
    {
        /*
        remove first element with node value == value
        * */
        validateLinkedList();

        node tmpPtr = start;
        while (tmpPtr!=null) {
            if(tmpPtr.value == value) {
                // erase will decrease the count for us.
                return erase(tmpPtr);
            }
            tmpPtr = tmpPtr.next;
        }
        return false;
    }

    public boolean erase(final @NotNull node ref)
    {
        // test erase first, before remove.
        if(ref==null){
            System.out.println("invalid reference ");
            System.exit(1);
        }
        if(ref.prev !=null)
            ref.prev.next = ref.next;
        if(ref.next !=null)
            ref.next.prev = ref.prev;
        if(ref==start)
            start = ref.next;
        if(ref==end)
            end = ref.prev;
        count -=1;
        return true;
    }

    // overloading, the previous method.
    public boolean erase(node startPtr, node endPtr)
    {
        // this code could be buggy !!!!!!!!!!! ***************
        // if the user still hold endPtr and startPtr in the cline code
        // they would still reference same node which mean theses nodes wont be erased

        /* delete all nodes in this range
        * both start and end are included within the range to be deleted.
        *
        * this is dangerous, how to know that theses references are pointing
        * at elements on the linked list - same linked list - start comes before end in order !!???.
        * all of this could be done using additional information in the nodes
        * id for the linked list, index in each node that represent the order.
        * */

        validateLinkedList();
        if(startPtr == null || endPtr == null){
            System.out.println("invalid references");
            System.exit(1);
        }
        node prev = startPtr.prev;
        node next = endPtr.next;
        if(end == endPtr)
            end = prev;
        if(start == startPtr)
            start = next;

        if(endPtr!=startPtr) {
            // want to delete more than one element
            while (true) {
                endPtr = endPtr.prev;
                endPtr.next = null;
                count-=1;
                if(endPtr == startPtr)
                    break;
            }
        }

        // link the parts of the linked list again
        if(prev!=null)
            prev.next = next;
        if(next!=null)
            next.prev = prev;

        startPtr = endPtr = null;
        count-=1;
        return true;
    }

    public void clear()
    {
        /*delete all nodes
        * we have to loop over them and make sure that every node
        * have no variabel that refere to it so that the JVM will be able to garbage collect
        * the  nodes !!!
        * what If I only deleted the begining and the end would this behaviour propogate !!???
        * start = end = null --- only
        * */
        validateLinkedList();
        while(true){
            if(end == start) {
                end = start = null;
                break;
            }
            end = end.prev;
            // do we need to set the reference end.prev = null !!??
            end.next = null;
        }
        count = 0;
    }

    public boolean empty()
    {
        return count==0;
    }

    public void display()
    {
        validateLinkedList();
        node tmpPtr = start;
        while(tmpPtr !=null)
        {
            System.out.print(tmpPtr.value + " ");
            tmpPtr = tmpPtr.next;
        }
        System.out.println();
    }
}