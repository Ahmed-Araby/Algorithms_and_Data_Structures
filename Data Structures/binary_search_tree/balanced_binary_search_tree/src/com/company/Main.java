package com.company;
import bbst.*;

import java.util.ArrayList;
import java.util.List;

public class Main {

    public static void print()
    {
        System.out.println("\n");
    }
    public static void main(String[] args) {
	    // write your code here
        bbst t = new bbst();
        int arr[] = new int[]{10, 15, 18, 20, 16, 13, 7, 3, 2};
        for(int val :arr){
            t.insert(val);
        }
        /*
        t.insert(5);
        print();
        t.insert(2);
        print();
        t.insert(4);
        print();
        */
        //t.preOrder();
        tester test = new tester();
        test.validateBBST(t);
    }
}
