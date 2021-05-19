package bst;

public class Node {
    public int value;
    public Node left, right;

    public Node()
    {
        value = 0;
        left = right = null;
    }

    public Node(int value, Node left, Node right)
    {
        this.value = value;
        this.left = left;
        this.right = right;
        return ;
    }
}
