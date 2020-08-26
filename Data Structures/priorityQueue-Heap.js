/*
min priority queue using heap 
*/

'use strict';

class priorityQueue
{
    constructor(capacity, compFunction)
    {
        /*
        - why do we have to have a specific capacity 
          for the heap. 

        - depending on the comp function we would have 
          max heap or min heap

        - 1 based heap
        */

        this.capacity = capacity;
        this.compFunction = compFunction;

       /*
       head could be IDs 
       or pointer to objects with a specific comparison function 
       */
       this.heap = [];
       this.size = 0; //  number of actual nodes in the heap
    }

    getParentIndex(index)
    {
        // 1- based indexing heap
        return parseInt(index / 2);
    }

    getLeftChildIndex(index)
    {
        // 1- based indexing heap 
        return  index * 2;
    }

    getRightChildIndex(index)
    {
        // 1 based indexing heap
        return index * 2 + 1;
    }

    upHeapify(index)
    {
        // [tested]

        while(true)
        {
            if(index==1) // root 
                break;

            var parentIndex = this.getParentIndex(index);
            var compResult = this.compFunction(this.heap[index], this.heap[parentIndex]);
            if(compResult == true){
                // exchange 
                var tmpValue = this.heap[parentIndex];
                this.heap[parentIndex] = this.heap[index];
                this.heap[index] = tmpValue;
                index = parentIndex;
            }
            else{
                break;
            }
        }

        return ;
    }

    downHeapify(index)
    {
        // [tested]
        // empty heap, as we just removed the last node 
        if(this.size == 0)
            return;

        while(true)
        {
            // leaf
            if(index == this.size)  
                break;
            
            var leftChlidIndex = this.getLeftChildIndex(index);
            var rightChlidIndex = this.getRightChildIndex(index);

            var finalIndex = index;
            if(leftChlidIndex <= this.size)
            {
                var compResult = this.compFunction(this.heap[finalIndex], this.heap[leftChlidIndex]);
                if(compResult == false)
                    finalIndex = leftChlidIndex;   
            }
            if(rightChlidIndex <= this.size)
            {
                var compResult = this.compFunction(this.heap[finalIndex], this.heap[rightChlidIndex]);
                if(compResult == false)
                    finalIndex = rightChlidIndex;
            }

            if(finalIndex == index) // the node is in the right position.
                break;
            
            // exchange 
            var tmpValue = this.heap[index];
            this.heap[index] = this.heap[finalIndex];
            this.heap[finalIndex] = tmpValue;

            index = finalIndex;

        }

        return ;
    }

    insert(value)
    {
        
        /*
        [this method is Tested, required methods also tested]

        to make sure that we have heap 
        thet is reprsented as complete binary tree 
        we would insert new elemnts as leafs from 
        left to right to to bottom , finishing current level 
        before starting a new level, this garante the log(n) height of the tree 
        hence lon(n) complexity for all the queries on this Data Strcture.
        */
       if(this.capacity == this.size + 1)
       {
           // assert an error
           console.log("heap is full");
           throw "heap is full";
       }

       else
       {
           this.size +=1;  // get next valid position
           this.heap[this.size] = value;
           this.upHeapify(this.size);
       }
    }

    top()
    {
        // [tested]
    
        if(this.size == 0)  // empty
        {
            console.log("heap is empty");
            throw "heap is empty";
        }

        return this.heap[1];
    }

    pop()
    {
        /*
        [this method is tested, also the required methods is tested]
        - remove the element in the top 
          min element in case of min heap. 
          max element in case of max heap.
        */
        if(this.size == 0)
        {
            console.log("heap is empty");
            throw "heap is empty";
        }

        else
        {
            /*
             - exchange with the most left node
             - this will also handles the case, when the heap 
                have only 1 node. 
             */ 

            this.heap[1] = this.heap[this.size];
            this.size -=1;
            this.downHeapify(1);
            return ;   
        }

    }

    find(value)
    {
        
        /*

        - return the index of the value 

        - the first node with this value 
          walking on the heap binary tree 
          left to right , top to bottom.

        - you may need to provide custom
          equality funtion in case of complex objects representatio.
        
        - complexity is linear  in number of elements in the heap.
        
        */

        for(var index=1; index<this.size; index++){
            if(this.heap[index] == value)
                return index;
        }

        // -1 is indicator for not found.
        return -1;
    }

    // ***
    delete(index)
    {
        throw "no implemented yet";
    }

    // ***
    chnageValue(index, newValue)
    {
        /*
        - decrement or increment, for both min and max heap

        - we may detect the behavior or the change we need 
          apply to the strcture of the tree using the compFunction
        */
       
        throw "no implemented yet";

    }

    // ***
    heapify(array)
    {
        /*
        convert array to heap 
        in place

        refernce for arrays in js !!!!????
        */
    }

    // ***
    heapSort(array)
    {
        /*
        convert the array to heap, in place 
        then sort it in ascending order
        */
    }

    length()
    {
        return this.size;
    }



    // for testing, using the HTML document for displaying
    display(htmlElement)
    {
        
        var str = "";

        for(var index=1; index<=parseInt(this.size / 2); index++){
            var tmpStr = "";
            
            // parent
            tmpStr += " parent is " + this.heap[index];
            tmpStr += '<br>';

            // left child
            tmpStr += " left child is  " ;
            var leftChlidIndex = this.getLeftChildIndex(index);
            if(leftChlidIndex <= this.size){
                tmpStr += this.heap[leftChlidIndex];
            }else{
                tmpStr +=' not exist '
            }

            tmpStr +='<br>';

            // right child
            tmpStr += "right child is  ";
            var rightChlidIndex = this.getRightChildIndex(index);
            if(rightChlidIndex <= this.size){
                tmpStr += this.heap[rightChlidIndex];
            }else{
                tmpStr +=' not exist '
            }

            // new line 
            tmpStr +='<br> <br>';

            str += tmpStr;
        }

        // put it into the HTML DOC 
        htmlElement.innerHTML  = str;
        return ;
    }
}



//////////////////////////////////////////////////////////////////


// testing the insertion for min heap 
function minHeapCompFunction(value1, value2)
{
    /*
    this function checks if the value1 is in the right position
    and the developer have to use to make sure that the min heap invarient is holding or not 
    */

    if(value1 < value2)
        return true;

    return false; // for = and >
}


var minPQ = new priorityQueue(20, minHeapCompFunction);




/*

// Testing

// INSERTING
var ls = [6, -2, -3, 1, 2 ,3, 3, -2];
for(var index=0; index <ls.length; index++){
    minPQ.insert(ls[index]);

    //var divElement = document.createElement('div');
    //divElement.id = 'disp'+index;
    
    //var divElement = document.getElementById("disp");
    //minPQ.display(divElement);
    //document.body.append(divElement);
    
}




// poping 
var minPqLength = minPQ.length();
for(var index=0; index<minPqLength; index++)
{
    console.log("top ", minPQ.top(), "length is ", minPQ.length());

    minPQ.pop();
    
    var divElement = document.createElement('div');
    divElement.id = 'disp'+index;
    
    //var divElement = document.getElementById("disp");
    minPQ.display(divElement);
    document.body.append(divElement);
}   

*/