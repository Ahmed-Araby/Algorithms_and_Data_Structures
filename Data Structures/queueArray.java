package dataStructures;

import java.lang.Math;

/*
*
* first in first out.
* based on dynamic array.
* if start came to end = empty array.
* if end came to start = full array.
* at the very begining empty array.
*
* */

public class queueArray {
    private int[] array;
    private int size = 0; // memory size of the array
    private int count = 0; // number of elements in the queue
    private int start = 0, end =0; // first element, next position to place an element in it

    public queueArray()
    {
        size = 10;
        array = new int [size];
    }
    public queueArray(int Psize)
    {
        size = Math.max(Psize, 0);
        array = new int[size];
    }
    private void enlarge()
    {
        /*
        * only called when the array is full*/
        int newSize = size * 2;
        int[] newArray = new int[newSize];
        // copy the old array into the new array
        for(int i=0; i<count; i++){
            newArray[i] = array[start];
            start = ( start + 1) % size;
        }
        size = newSize;
        array = newArray;
        start = 0;
        end = count; // next pos to add in
        return ;
    }

    public void push_back(int value)
    {
        if(count == size)
            enlarge();
        array[end] = value;
        end = (end + 1)  % size;
        ++count;
        return ;
    }
    public int pop_front()
    {
        if(count==0){
            System.out.println("empty queue");
            System.exit(1);
        }
        int value = array[start];
        start = (start + 1) % size;
        count-=1;

        // no need to edit the end pointer
        return value;
    }

    /*
    * queue DS don't support back
    public int back()
    {
        if(count==0){
            System.out.println("empty queue");
            System.exit(1);
        }
        int index = (end-1 < 0?count-1:end-1);
        return array[index];
    }*/
    public int front()
    {
        if(count==0){
            System.out.println("empty queue");
            System.exit(1);
        }
        return array[start];
    }

    public int getLength()
    {
        return count;
    }
    public int getCapacity()
    {
        return size;
    }
}
