package bbst;

public class Node {
    public int value;
    public Node left, right;
    public int height;
    public int balanceFactor;

    public Node()
    {
        value = 0;
        left = right = null;
        height = balanceFactor = 0;
    }

    public Node(int value, Node left, Node right)
    {
        this.value = value;
        this.left = left;
        this.right = right;
        return ;
    }
}