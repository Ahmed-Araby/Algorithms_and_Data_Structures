package Btree;

import table.user;

public class testBTree
{
    static private void fillBtree(bTree indexTree)
    {
        String keys[] = {"k", "a", "b", "c", "d", "e", "f", "y", "z", "i" , "h", "r", "w", "t", "q", "o", "p"};
        //user users[] = new user[6];
        int index = 0;
        for(; index< keys.length; index +=1)
        {
            //users[index] = new user();
            //users[index].name = keys[index];
            user newUser = new user();
            newUser.name = keys[index];
            indexTree.insert(keys[index], newUser);
            node root = indexTree.root;
            //System.out.println(root.keys);
            //indexTree.traverseBTree();
        }
    }

    static private void testInsert()
    {
        bTree indextree = new bTree();
        fillBtree(indextree);
        indextree.traverseBTree();
    }

    static private void testSelectInBTree()
    {
        bTree indextree = new bTree();
        fillBtree(indextree);
        String keys[] = {"k", "a", "b", "c", "d", "e", "f", "y", "z", "i" , "h", "r", "w", "t", "q", "o", "p"};
        for (String key:
             keys) {

            node refNode = indextree.select(key);
            if (refNode != null) {
                System.out.println("node reference founded ");
                System.out.println(refNode.keys);
            } else
                System.out.println("not found ");
            System.out.println("\n");
        }
    }

    static private void fillNode(node nodeObj, String[] keys)
    {
        for(String key:keys)
        {
            innerNode tmpNode = new innerNode();
            tmpNode.name = key;
            nodeObj.insert(key, tmpNode);
        }

    }
    static private void test_mergeChildLastBranch()
    {
        innerNode root = new innerNode();
        String keys[] = {"a", "b", "c"};
        fillNode(root, keys);
        String keys2[] = {"d", "e", "f", "y", "z", "i" , "h", "r", "w", "t", "q", "o", "p"};

        int index = 0;
        for(Object tmpRef: root.refs)
        {
            node tmpNode = (node)tmpRef;
            innerNode newNode = new innerNode();
            newNode.name = keys2[index];
            tmpNode.insert(keys2[index], newNode);
            index +=1;
        }
        // last ref bigger than =
        innerNode newNode = new innerNode();
        newNode.name = keys2[index];
        ((innerNode)(root.refs.get(2))).biggerThan = newNode;
        index +=1;

        // root bigger than
        newNode = new innerNode();
        newNode.insert(keys2[index], new innerNode());
        index+=1;
        root.biggerThan = newNode;
        index +=1;

        // merge
        bTree indexTree = new bTree();
        indexTree.mergeChildLastBranch(root);
        root.biggerThan.disp();
    }

    static private void test_mergeChildMiddleBranch()
    {
        innerNode root = new innerNode();
        String keys[] = {"a", "b", "c"};
        fillNode(root, keys);
        String keys2[] = {"d", "e", "f", "y", "z", "i" , "h", "r", "w", "t", "q", "o", "p"};

        int index = 0;
        for(Object tmpRef: root.refs)
        {
            node tmpNode = (node)tmpRef;
            innerNode newNode = new innerNode();
            newNode.name = keys2[index];
            tmpNode.insert(keys2[index], newNode);
            index +=1;
        }
        // last ref bigger than =
        innerNode newNode = new innerNode();
        newNode.name = keys2[index];
        ((innerNode)(root.refs.get(2))).biggerThan = newNode;
        index +=1;

        // root bigger than
        newNode = new innerNode();
        newNode.name = keys2[index];
        ((innerNode)(root.refs.get(1))).biggerThan = newNode;
        index +=1;

        //root.disp();

        // merge
        bTree indexTree = new bTree();
        indexTree.mergeChildMiddleBranch(root, 1);
        //root.disp();
        System.out.println(root.keys);

    }

    static private void test_delete()
    {
        bTree indextree = new bTree();
        // insert + split
        fillBtree(indextree);

        // delete from the tree
        //indextree.delete("e");
        //indextree.delete("f");
        //indextree.delete("o");
        //indextree.delete("p");

        indextree.traverseBTree();

        return ;

    }
    static public void Main()
    {
        //testInsert();
        //testSelectInBTree();
        //test_mergeChildLastBranch();
        //test_mergeChildMiddleBranch();
        //test_delete();
    }

}