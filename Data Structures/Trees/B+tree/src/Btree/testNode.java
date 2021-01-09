package Btree;
import table.user;

import java.util.ArrayList;

public class testNode
{

    static private node fillNode(node nodeObj, String []keys)
    {
        // associate users  reference to the keys positions
        user users[] = new user[keys.length];
        int index = 0;
        for (String key: keys) {
            users[index] = new user();
            users[index].name = key;
            index +=1;
        }

        index= 0;
        for(String key:keys)
        {
            int position = nodeObj.getPosition(key);
            //System.out.printf("position : " + position + "\n");

            //nodeObj.insertKey(key, position);
            //nodeObj.insertRef(users[index], position);
            nodeObj.insert(key, users[index]);
            index +=1;

            int sz = nodeObj.getSize();
            //System.out.println("size : " + sz );

            //String MaxKey = nodeObj.getMaxKey();
            boolean needSplit = nodeObj.needSplit();

            //System.out.println("max key : " + MaxKey);
            //System.out.println("need split : " + needSplit);
            //System.out.printf("\n\n");
        }
        return nodeObj;
    }

    static private void testNodeClass()
    {
        /*
        System.out.printf("testing node class \n");
        // test keys stuff
        String keys[] = {"aaaabcd", "aaabcd", "aaabb", "aaaaa", "dklsjdkls", "oiddsds"};

        // associate users  reference to the keys positions
        user users[] = new user[keys.length];
        int index = 0;
        for (String key: keys) {
            users[index] = new user(key);
            index +=1;
        }

        node nodeObj = new node();
        index= 0;
        for(String key:keys)
        {
            int position = nodeObj.getPosition(key);
            System.out.printf("position : " + position + "\n");

            //nodeObj.insertKey(key, position);
            //nodeObj.insertRef(users[index], position);
            nodeObj.insert(key, users[index]);
            index +=1;

            int sz = nodeObj.getSize();
            System.out.println("size : " + sz );

            String MaxKey = nodeObj.getMaxKey();
            boolean needSplit = nodeObj.needSplit();

            System.out.println("max key : " + MaxKey);
            System.out.println("need split : " + needSplit);
            System.out.printf("\n\n");
        }

        System.out.printf("\n\n");
        nodeObj.disp();
        */
    }

    static public void testInnerNode()
    {
        String keys[] = {"aaaabcd", "aaabcd", "aaabb", "aaaaa", "dklsjdkls", "oiddsds"};
        innerNode nodeObj = new innerNode();
        fillNode(nodeObj, keys);

        nodeObj.disp();
        System.out.println(nodeObj.needSplit());

        /**
         * we need to cast it here
         * as the return type of the method is node
         * which will always upcast the returned object
         */

        innerNode newInnerNode = (innerNode) nodeObj.split();


        System.out.println("node obj " + nodeObj.needSplit());
        System.out.println("new inner node " + newInnerNode.needSplit());

        System.out.println("inner node ");
        nodeObj.disp();

        System.out.println("\n\n");
        System.out.println("new inner node ");
        newInnerNode.disp();
    }

    static public void testLeafNode()
    {
        System.out.println("test leaf node \n\n ");
        leafNode l1 = new leafNode();
        leafNode l2 = new leafNode();
        leafNode l3 = new leafNode();

        l2.prev = l1;
        l2.next = l3;
        String keys[] = {"aaaabcd", "aaabcd", "aaabb", "aaaaa", "dklsjdkls", "oiddsds"};
        l2 = (leafNode) fillNode(l2, keys);

        System.out.println("\n\nbefore spliting\n\n");

        System.out.println(l2.needSplit());
        System.out.println(l2.getSize());
        System.out.println(l2.next.getSize());
        System.out.println(l2.prev.getSize());

        // split
        System.out.println("\n\n after spliting \n\n");
        leafNode newLeafNode = (leafNode) l2.split();
        //System.out.println(l2.needSplit());
        //System.out.println(l2.getSize());
        //System.out.println(newLeafNode.needSplit());
        //System.out.println(newLeafNode.getSize());

        System.out.println("\n\nl2 node disp \n\n");
        //l2.disp();

        System.out.println("\n\nnew leaf node disp \n\n");
        //newLeafNode.disp();

        System.out.println("check connections ");
        System.out.println("l2 prev size " + l2.prev.getSize());
        System.out.println("l2 next size " + l2.next.getSize());

        System.out.println( "new node prv size "+ newLeafNode.prev.getSize());
        System.out.println( "new node next size "+ newLeafNode.next.getSize());

        if(l2.next == newLeafNode && newLeafNode.prev == l2)
            System.out.println("reference are set correctly");

        return ;
    }

    static private void testInnerNodeWithBiggerThanBranch()
    {
        /*

        String names[] = {"aaaa", "bbbb", "cccc", "dddd", "eeee", "ffff"};
        innerNode nodeObj = new innerNode();
        int index = 0;
        for(; index < names.length-1; index++) {
            nodeObj.insert(names[index], new innerNode(names[index]));
        }
        nodeObj.biggerThan = new innerNode(names[index]);


         // why we are not able to cast array list <node>
         //     to array list <object>


        System.out.println("node object size " + nodeObj.getSize());
        System.out.println("node object needSplit " + nodeObj.needSplit());
        System.out.println("\n\n after spliting");

        innerNode rightNode = (innerNode) nodeObj.split();
        System.out.println("node object display ");
        nodeObj.disp();
        System.out.println("\n\n");

        System.out.println("right node display");
        rightNode.disp();

        System.out.println("\n\n");
        System.out.println("bigger than name node object " + ((innerNode)nodeObj.biggerThan).name);
        System.out.println("bigger than name right node " + ((innerNode)rightNode.biggerThan).name);

        System.out.println("\n\n");
        System.out.println("needSplit need split  " + nodeObj.needSplit());
        System.out.println("rightNode  need split " + rightNode.needSplit());

        System.out.println("\n\n");
        System.out.println("node object size " + nodeObj.getSize());
        System.out.println("right node  size " + rightNode.getSize());

        return ;
        */
    }

    static private void testMergeLeafNode()
    {
        String leftkeys[] = {"a", "b", "c"};
        String rightKeys[] = {"e", "f"};

        leafNode leftNode = new leafNode();
        leafNode rightNode = new leafNode();
        leafNode lastNode = new leafNode();
        lastNode.insert("h", null);

        leftNode.next = rightNode;
        rightNode.next = lastNode;

        fillNode(leftNode, leftkeys);
        fillNode(rightNode, rightKeys);

        System.out.println("before merge ");
        System.out.println("left node keys " + leftNode.keys);
        System.out.println("left node next keys " + leftNode.next.keys);
        System.out.println("right node keys " + rightNode.keys);
        System.out.println("right node next keys " + rightNode.next.keys);
        System.out.println("\n\n");

        leftNode.merge(rightNode);

        System.out.println("after merge ");
        System.out.println("left node keys " + leftNode.keys);
        System.out.println("left node next keys " + leftNode.next.keys);
        System.out.println(leftNode.needSplit());

        System.out.println("\n\n");
        leftNode.disp();
        return ;
    }

    static private void testMergeInnerNode()
    {

        String lk []  = {"a", "b"};
        innerNode leftNode = new innerNode();
        fillNode(leftNode, lk);

        String rk []  = {"g", "h"};
        innerNode rightNode = new innerNode();
        fillNode(rightNode, rk);

        String lb []  = {"c", "d"};
        innerNode leftBigger =  new innerNode();
        fillNode(leftBigger, lb);

        String rb []  = {"x", "z"};
        innerNode rightBigger = new innerNode();
        fillNode(rightBigger, rb);

        leftNode.biggerThan = leftBigger;
        rightNode.biggerThan = rightBigger;

        //System.out.println("before merge ");
        String leftNodKey = "d";
        leftNode.merge(rightNode, leftNodKey);
        System.out.println("after merge ");
        //leftNode.disp();
        System.out.println(((node)leftNode.refs.get(2)).keys);
    }

    static public void Main(String[] args)
    {

        //testNodeClass();
        //testInnerNode();
        //testLeafNode();
        //testInnerNodeWithBiggerThanBranch();
        //testMergeLeafNode();
        //testMergeInnerNode();
    }

}