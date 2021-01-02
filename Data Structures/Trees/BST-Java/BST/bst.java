package BST;

public class bst {
    private node root = null;
    int count = 0;


    // actual work
    private node insert(node root, int value)
    {
        if(root==null)
            return new node(value, null, null);

        if(value > root.value)
            root.right = insert(root.right, value);
        else
            root.left = insert(root.left,value);
        return root;
    }

    private boolean leef(node root)
    {
        if(root.left == null && root.right == null)
            return true;
        return false;
    }

    private int findBiggest(node root)
    {
        int max = 0;
        while(root!=null)
        {
            max = root.value;
            root = root.right;
        }
        return max;
    }

    private int findSmallest(node root)
    {
        int mini = 0;
        while(root!=null){
            mini = root.value;
            root = root.left;
        }

        return mini;
    }

    private node delete(node root, int value)
    {
        if(root.value == value)
        {
            if(leef(root))
                return null;
            else if(root.left == null){
                return root.right;
            }
            else if(root.right == null){
                return root.left;
            }
            else{
                // replace it with the biggest value
                // from its left subtree
                int newValue = findBiggest(root.left);
                root.left = delete(root.left, newValue);
                root.value = newValue;
            }
        }

        else if(value > root.value)
            root.right = delete(root.right, value);
        else
            root.left = delete(root.left, value);
        return root;
    }

    private boolean find(node root, int value)
    {
        if(root == null)
            return false;
        else if(root.value == value)
            return true;
        else if(value > root.value)
            return find(root.right, value);
        else
            return find(root.left, value);
    }
    // user interface
    public boolean insert(int value)
    {
        if(this.find(root, value))
            return false;

        root = this.insert(root, value);
        count +=1;
        return true;
    }

    public boolean delete(int value)
    {
        if(!this.find(root, value))
            return false;

        root = this.delete(root, value);
        count-=1;
        return true;
    }

    public boolean find(int value)
    {
        return this.find(root, value);
    }

    public boolean update(int oldValue ,int newValue)
    {
        if(!this.delete(oldValue))
            return false;
        this.insert(newValue);
        return true;
    }

    public int size()
    {
        return this.count;
    }


    // for testing purpose
    public void dfs(node root)
    {
        if(root==null) {
            System.out.println("current " + null);
            return;
        }
        System.out.println("current " + root.value);

        System.out.println("left ");
        dfs(root.left);

        System.out.println("right ");
        dfs(root.right);

        return;
    }

    public void dfs()
    {
        dfs(root);
    }
}

