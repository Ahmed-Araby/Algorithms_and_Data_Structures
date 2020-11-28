package dataStructures;

class emptyVectorException extends Exception{
    emptyVectorException(String message){
        super(message);
     }
}

public class vector {
    /*
    for simplicity this will be vector of integer
    - we can downsize the vector when count < than size / 2
    to save memory
    * */

    private int [] array;
    private int size=0;  // size of the whole array
    private int count = 0; //  number of the actual elements

    vector()
    {
        /*default constructor*/
        System.out.println("default constructor : vector class");
        size = 10;
        array = new int[size];
    }

    vector(int Psize)
    {
        size = Psize;
        array = new int[size]; // all zero
    }

    private void enlarge()
    {
        int newSize = size * 2;
        int [] newArray = new int[newSize];
        for(int i=0; i<array.length; i++)
            newArray[i] = array[i];
        size = newSize;
        array = newArray;
        return ;
    }

    public void push_back(int element)
    {
        if(count == size)
            enlarge();
        array[count] = element;
        ++count;
        return ;
    }
    public int pop_back()
    {
        try {
            if(count == 0)
                throw new emptyVectorException("empty vector");
        }catch(Exception e){
            System.out.println(e.getMessage());
            System.exit(1);
        }

        count-=1; // pop the element
        return array[count];
    }

    public int back()
    {
        try {
            if(count == 0)
                throw new emptyVectorException("empty vector");
        }catch(Exception e){
            System.out.println(e.getMessage());
            System.exit(1);
        }
        return array[count-1];
    }

    public int getLength()
    {
        return count;
    }
}
