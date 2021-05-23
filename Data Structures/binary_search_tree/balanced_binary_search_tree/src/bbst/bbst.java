package bbst;

import java.util.ArrayList;
import java.util.List;

public class bbst {
    private Node root= null;
    private int size = 0;

    // start of BBST functionality
    private void update(Node root)
    {
        int hl = 0, hr = 0; // length of highest branch
        if(root.left!=null)
            hl = root.left.height + 1; // branch from me
        if(root.right !=null)
            hr = root.right.height + 1;
        //System.out.println("val : " + root.value + " hl : " + hl + " : " + hr);
        root.height = Math.max(hr, hl);
        root.balanceFactor = hr - hl;
        return ;
    }
    Node rotate_Left(Node root)
    {
        Node right = root.right;
        root.right = right.left;
        right.left = root;

        // order matters - child first
        update(right.left);
        update(right);
        return right;
    }

    Node rotate_right(Node root)
    {
        Node left = root.left;
        root.left = left.right;
        left.right = root;

        // order matters - child first
        update(left.right);
        update(left);
        return left;
    }
    Node rotate_right_left(Node root)
    {
        Node right = root.right;
        right = rotate_right(right);
        root.right = right;
        root = rotate_Left(root);
        return root;
    }
    Node rotate_left_right(Node root)
    {
        Node left = root.left;
        left = rotate_Left(left);
        root.left = left;
        root = rotate_right(root);
        return root;
    }

    private Node balance(Node root)
    {
        if(root.balanceFactor == 2){
            if(root.right.balanceFactor == 1)
                // right heavy, rotate left
                root = rotate_Left(root);
            else
                root = rotate_right_left(root);
        }
        else if(root.balanceFactor == -2){
            if(root.left.balanceFactor == -1)
                // left heavy
                root = rotate_right(root);
            else
                root = rotate_left_right(root);
        }
        return root;
    }
    // END of BST functionality

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

        // bbst
        update(root);
        root = balance(root);
        // bbst

        return root;
    }

    public boolean delete(int value)
    {
        boolean exist = find(value);
        if(exist == false)
            return false;

        root = delete(root, value);
        size -=1;
        return true;
    }

    private Node delete(Node root, int value)
    {
        if(root.value == value)
        {
            if(root.left == null && root.right == null)
                return null;
            else if(root.left==null)
                root = root.right;
            else if(root.right == null)
                root = root.left;
            else{
                Node maxNode = getMax(root.left);
                delete(maxNode.value);
                maxNode.left = root.left;
                maxNode.right = root.right;
                root = maxNode;
            }
        }
        if(value > root.value)
            root.right = delete(root.right, value);
        else
            root.left = delete(root.left, value);

        // bbst
        update(root);
        root = balance(root);
        // bbst

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
    public void preOrder()
    {
        preOrder(root);
    }

    private void preOrder(Node root)
    {
        if(root==null){
            System.out.println("leaf ");
            return ;
        }

        System.out.println("node is : " + root.value);

        System.out.println("go left " );
        preOrder(root.left);

        System.out.println("go right ");
        preOrder(root.right);
        return ;
    }
    public Node getRoot()
    {
        return root;
    }
}
