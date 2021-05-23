package bbst;

public class tester {
    private boolean valid = true;
    private int dfs(Node root)
    {
        if(root==null)
            return 0;

        int lh = 0;
        if(root.left !=null)
            lh = dfs(root.left) + 1;

        int rh = 0;
        if(root.right !=null)
            rh = dfs(root.right) + 1;

        if(Math.abs(rh - lh) >=2) {
            valid = false;
            System.out.println(root.value + " " + lh + " " + rh);
        }

        return Math.max(lh, rh);
    }
    public boolean validateBBST(bbst tree) {
        Node root= tree.getRoot();
        dfs(root);
        if(valid)
            System.out.println("tree is BBST");
        else
            System.out.println("tree is not bbst");
        return valid;
    }
}
