using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace IntelligentScissors  // this was my 3rd year Algorithm course project and this heap was part of it  , it might have extra things or customized 
{
    /*
     * building block for my heap cell 
     * id is the id of my pixel 
     * w is the weight from the orginal pixel to me  
     */
    public struct node
    {
        public int id;
        public double w;
        public node(int _id, double _w)
        {
            id = _id;
            w = _w;
        }


        /*
         * they have to take 2 parameters cuz they are static so we cannot call them by specific instance of struct 
         */
        public static bool operator >(node obj1, node obj2)
        {
            if (obj1.w > obj2.w)
                return true;
            return false;
        }
        public static bool operator <(node obj1, node obj2)
        {
            if (obj1.w < obj2.w)
                return true;
            return false;
        }
    }

    /*
     * the property that we choose minimum here depending on is  weight (double w) in node struct it's our key ;
     */
    public class Priority_Queue
    {
        // data 
        node[] heap;
        int p, count, size;

        // methods 

        // constructors 
        public Priority_Queue()
        {
            heap = new node[1005];
            p = 1;
            count = 0;
            size = 0;
        }
        public Priority_Queue(int sz)
        {
            heap = new node[sz + 2];
            size = sz + 2;  // 0- based
            p = 1;
            count = 0;
        }

        // helpe methods
        private bool have_left_child(int index)
        {
            if (index * 2 < p)
                return true;
            return false;
        }
        private bool have_right_child(int index)
        {
            if (index * 2 + 1 < p)
                return true;
            return false;
        }

        private void swap(int i, int j)
        {
            node sw = heap[i];
            heap[i] = heap[j];
            heap[j] = sw;
        }
        public int length()
        {
            return count;
        }
        public bool empty()
        {
            return (count == 0?true:false);
        }
        // process methods 
        void reallocate()
        {
            /*
             * I'm not sure with this ask about it ???
             * 
             * here is what happens here 
             * we declare a new array that remains ini the heap 
             * and it have to get destroid at the end of the scope of the method but 
             * this do not happen cuz it have a variable with longer live time that refer to it 
             * 
             * and the old array that I used to have get destroied by the garapage collector 
             * cuz there is no more any variable that refer to it's address in the heap 
             */

            int nsz = 2 * count;
            node[] tmp = new node[nsz];

            // copy 
            for (int i = 0; i < size; i++)
                tmp[i] = heap[i];

            /*
             *  what does this statement do ???
             *  it assigns the address of stores in tmp refering to the array in the heap (memory part)
             *  to heap (variable name remain in the stack).
             */

            heap = tmp;

            /*
             *   how to delete tmp   ???
             *   we can't 
             *   
             */
        }




        public void insert(int id, double w)
        {
            /*
             *  heap is full 
             *  reallocate it 
             */
            if (p == size)
            {
                reallocate();
                // now p is valid position 
            }

            int tmp = p;
            heap[p] = new node(id, w);
            p++; // next valid position 
            count++;

            /*
             * Apply heapfiy  
            */
            up_heapify();
        }

        private void up_heapify()
        {
            int tp = p - 1; // pos of recently inserted element 
            int dad = tp / 2;
            while(dad>=1 && heap[dad]>heap[tp])
            {
                swap(dad, tp);
                // go up 
                tp = dad;
                dad = tp / 2;
            }
        }

        public node top()
        {
            /*
             *  how to assert empty  heap ???
             */

            /*
             * the user defined data type that we return have to be public 
             * so it could be seen out side that name space 
             */
            return heap[1]; // minimum element in the heap 
        }


        /*
         *  delete the smallest element and  mantain the property of the 
         *  min - heap which is each parent is smaller than his to childes 
         */
        public void pop()
        {
            node tmp = heap[p - 1]; // last element in the heap 
            p--; // decrease the size 
            count--;

            /*
             * p is my next valid pos to place data  
             */

            heap[1] = tmp;
            // apply downfiy  on index 1
            down_heapify();
        }
        private void down_heapify()
        {
            int tp = 1;
            while(have_left_child(tp))
            {
                int index = tp * 2; // left (index of min element)
                // right child 
                if(have_right_child(tp) && heap[index+1]<heap[index])
                {
                    index++;
                }
                if (heap[index] < heap[tp])
                {
                    swap(index, tp);
                    // go down 
                    tp = index;
                }
                else
                {
                    break;
                }
            }
            
        }
        public void display()
        {
            for (int i = 1; i < p; i++)
            {
                Console.Write(heap[i].id);
                Console.WriteLine(heap[i].w);
            }
        }


        /*
         * didn't get tested yet !!!!!!!!!
         * 
         * building min_heap from an already existing array 
         * 
         */


        /*
         * this function place a root in it's place 
         * with it's childes 
         * p is next valid pos to place an element 
         * it's 1 based array 
         */
        public void build_min_down_heapify(node[] tmp, int index, int p)
        {
            while (index * 2 < p)
            {
                int mini = index * 2;
                if (index * 2 + 1 < p && tmp[mini] > tmp[index * 2 + 1])
                {
                    mini = index * 2 + 1;
                }

                if (tmp[index] > tmp[mini])
                {
                    node sw = tmp[index];
                    tmp[index] = tmp[mini];
                    tmp[mini] = sw;
                    // go down;
                    index = mini;
                }
                else
                    break;
            }
        }

        /*
         * p is next valid pos to place an element 
         * it's 1 based array 
         */
        public void build(node[] tmp, int p)
        {
            /*
             *  build the heap level by level from bottom to up 
             *  that mantain the assumation of single violation at a time at most 
             *  leaves are min_heap by default 
             */

            int n = Math.Max((p - 1) / 2, 1);
            for (int i = n / 2; i >= 0; i--)
            {
                build_min_down_heapify(tmp, i, p);
            }
        }
    }
}
