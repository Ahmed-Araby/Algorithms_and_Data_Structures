package bst;

import java.util.ArrayList;
import java.util.List;

public class bst {
    private Node root= null;
    private int size = 0;

    public boolean insert(int value)
    {
        if(find(value))
            return false;

        root = insert(root, value);
        size +=1;
        return true;
    }

    private Node insert(Node root, int value)
    {
        if(root==null)
            return new Node(value, null, null);
        if(value > root.value)
            root.right = insert(root.right, value);
        else
            root.left = insert(root.left, value);
        return root;
    }

    public boolean delete(int value)
    {
        boolean exist = find(value);
        if(exist == false)
            return false;

        root = delete(root, value);
        return true;
    }

    private Node delete(Node root, int value)
    {
        if(root.value == value)
        {
            if(root.left == null && root.right == null)
                return null;
            else if(root.left==null)
                return root.right;
            else if(root.right == null)
                return root.left;
            else{
                Node maxNode = getMax(root.left);
                delete(maxNode.value);
                maxNode.left = root.left;
                maxNode.right = root.right;
                return maxNode;
            }
        }
        if(value > root.value)
            root.right = delete(root.right, value);
        else
            root.left = delete(root.left, value);
        return root;
    }

    private Node getMax(Node root)
    {
        while(root.right !=null)
            root = root.right;
        return root;
    }


    public boolean find(int value)
    {
        Node node = find(root, value);
        if(node == null)
            return false;
        return true;
    }

    private Node find(Node root,  int value)
    {
        if(root == null)
            return null;
        if(value == root.value)
            return root;
        if(value > root.value)
            return find(root.right, value);
        else
            return find(root.left, value);
    }

    // for testing
    public List<Integer> inOrder()
    {
        List<Integer> values = new ArrayList<Integer>();
        inOrder(root, values);

        return values;
    }

    private void inOrder(Node root, List<Integer> values)
    {
        if(root == null){
            System.out.println("leaf node ");
            return ;
        }

        System.out.println("go left ");
        inOrder(root.left, values);

        System.out.println("value is "  + root.value);
        values.add(root.value);

        System.out.println("go right ");
        inOrder(root.right, values);

        return ;
    }
}
