package com.company;

import java.util.ArrayList;
import java.util.List;
import bst.*;

public class Main {

    public static void main(String[] args) {
        int [] values = {5, 10, 12, 8, 3, 4, 2, 1};
        bst tree = new bst();
        for(int i=0; i<values.length; i++){

            tree.insert(values[i]);
        }
        tree.delete(5);
        tree.delete(10);
        tree.delete(2);
        System.out.println("in order traversal ");
        tree.inOrder();


        /*
        List<Integer> ls = new ArrayList<Integer>();
        ls.add(1);
        ls.add(2);
        List<Integer> ls2 = ls;
        if(ls2==ls){
            System.out.println("equal");
        }
        System.out.println(ls2 + "  " + ls);*/
    }
}
