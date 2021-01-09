package Btree;
import table.user;
public class bTree {
    public node root;
    /**
     * represent number of nods in the tree
     * it is not synchronized yet.
     */

    private int size = 0;

    /**
     * @param key
     * @param ref reference to the user data
     * @return reference to the leaf node that will contain the key
     */

    public boolean insert(String key, user ref) {
        if (size == 0) {
            // first insertion ever
            // this supposed to be inside create node method.
            root = new leafNode();
            root.insert(key, ref);
            size += 1;
            return true;
        }

        boolean needSplit = _insert(root, key, ref);
        if (needSplit) {
            // create new root
            innerNode newRoot = new innerNode();
            newRoot.biggerThan = root;
            splitChild(newRoot, -1);
            root = newRoot;
        }

        return true;
    }

    /**
     * split the node of the bigger than branch
     * assign the newly created node[right part] to the bigger than branch
     * insert the left part of the old biggerThan node to the current root
     * @param root reference to node that need to split the last child.
     */
    private void splitChildLastBranch(node root)
    {
        String newKey = ( (innerNode)root).biggerThan.getMedianKey();

        node rightNode = ((innerNode) root).biggerThan.split();
        node leftNode = ((innerNode) root).biggerThan;
        ((innerNode) root).biggerThan = rightNode;

        root.insert(newKey, leftNode);
    }

    /**
     * split the node at position index in the current node references
     * change the key of the splited node [left part of it ] to be
     * the min key in the splited right part of it
     *
     * insert new node with the old key of the splited node
     *
     * @param root reference to nood that need to split one of its childs
     * @param index index of the chid node that need to splited
     */
    private void splitChildMiddleBranch(node root, int index)
    {
        String newKey = ( (node) root.refs.get(index) ).getMedianKey();

        node rightNode = ((node) root.refs.get(index)).split();
        node leftNode = ((node) root.refs.get(index));

        String curKey = root.keys.get(index);
        root.keys.set(index, newKey);
        root.insert(curKey, rightNode);

        return ;
    }

    /**
     *
     * @param root reference to the nood that need to split one of its chidls
     * @param index index of the node to be splited
     *              if -1 ----> split the node at biggerThan brnach
     *              else get the node from the refs arraylist
     */
    private void splitChild(node root, int index)
    {
        //System.out.println("split child ");

        if(index == -1)
            splitChildLastBranch(root);
        else
            splitChildMiddleBranch(root, index);
    }

    private boolean _insert(node root, String key, user ref)
    {
        if(root instanceof leafNode)
        {
            root.insert(key, ref);
            return root.needSplit();
        }

        else {
            int index = root.getPosition(key);
            if(index == -1) {
                // biggerThan branch
                boolean needSplit = _insert( ( (innerNode) root).biggerThan, key, ref);
                if(needSplit) {
                    splitChild(root, index);
                    return root.needSplit();
                }
            }

            else {
                // middle branch
               boolean needSplit = _insert((node)root.refs.get(index), key, ref);
               if(needSplit) {
                   splitChild(root, index);
                   return root.needSplit();
               }
            }
        }

        return false;
    }

    /**
     * merge 2 neighbour node and reorder the keys and refs of this root
     * @param root
     * @return index of new node after  merge
     *          here it will be -1 as we will put the merged node into the biggerThan branch.
     * [tested]
     */

    public int mergeChildLastBranch(innerNode root)
    {
        int index = root.getSize()-1;
        String leftNodeKey = root.keys.get(index);
        node leftNode = (node) root.refs.get(index);

        root.remove(index);

        if(leftNode instanceof leafNode){
            leafNode leafLeftNode = (leafNode) leftNode;
            leafNode rightNode =(leafNode) root.biggerThan;
            leafLeftNode.merge(rightNode);
            root.biggerThan = leafLeftNode;
        }
        else{
            innerNode innerLeftNode = (innerNode) leftNode;
            innerNode rightNode = (innerNode) root.biggerThan;
            innerLeftNode.merge(rightNode, leftNodeKey);
            root.biggerThan = innerLeftNode;
        }
        return -1;
    }

    /**4
     *
     * @param root
     * @param index
     * @return index of the new node after merge
     * [tested --- *]
     */
    public int mergeChildMiddleBranch(node root, int index)
    {
        int leftIndex = index;
        int rightIndex = index + 1;
        if(rightIndex == root.getSize()){
            leftIndex -=1;
            rightIndex -=1;
        }

        assert leftIndex >=0 && rightIndex >=0 : "invalid indices for nodes to be merged";

        String leftNodeKey = root.keys.get(leftIndex);
        node leftNode = (node) root.refs.get(leftIndex);

        if(leftNode instanceof leafNode){
            leafNode leafLeftNode = (leafNode) leftNode;
            leafNode rightNode = (leafNode) root.refs.get(rightIndex);
            leafLeftNode.merge(rightNode);
            root.refs.set(rightIndex, leafLeftNode);
        }
        else{
            innerNode innerLeftNode = (innerNode) leftNode;
            // we can avoid casting the right node
            // by casting in the merge method.
            innerNode rightNode = (innerNode) root.refs.get(rightIndex);
            innerLeftNode.merge(rightNode, leftNodeKey);
            root.refs.set(rightIndex, innerLeftNode);
        }

        root.remove(leftIndex);

        return rightIndex -1;
    }

    /**
     *
     * @param root  node that have one of its childes need to merge with another
     *              node of its childes.
     * @param index index of the node that need to merge with some neighbour
     *              -1 mean the bigger than branch node need to merge.
     * @return  index of the new node after merge in the root node.
     */
    private int mergeChild(innerNode root, int index)
    {
        // root is stable node
        // one of its child is not
        // root will always be inner node.

        assert root.getSize() != 0 : "there is no neighbour nodes to merge with ";

        if(index==-1 || root.getSize() == 1)
            return mergeChildLastBranch(root);
        else
            return mergeChildMiddleBranch(root, index);
    }


    private boolean keyExist(String key)
    {
        return true;
    }

    /**
     * delete the first occurrence of key in the tree
     * @param key
     * @return true if we managed to delete the key
     */
    public boolean delete(String key)
    {
        // make sure the key is exist
        if(keyExist(key) == false)
            return false;
        return delete(root, key);
    }

    /**
     *  this method is only called after making sure that key is exist in the tree
     * @param root
     * @param key
     * @return
     */
    private boolean delete(node root, String key)
    {
        if(root instanceof leafNode) {
            return root.delete(key);
        }

        int index = root.getPosition(key);
        boolean success = false;
        node newRoot = null;
        if(index == -1) {
            newRoot = ( (innerNode) root ).biggerThan;
            success = delete(newRoot, key);
        }

        else{
            newRoot = (node)root.refs.get(index);
            success = delete(newRoot, key);
        }

        // check for merge
        if(newRoot.needMerge())
            mergeChild((innerNode)root, index);
        // check for split
        if(newRoot.needSplit())
            splitChild(root, index);

        return success;
    }

    /**
     *
     * @param key
     * @return reference to leaf node with the first occurance
     * of the key
     *
     * [tested]
     */

    public node select(String key)
    {
        return select(root, key);
    }

    /**
     * we can implement it in iterative manner.
     * @param root
     * @param key
     * @return reference to the first leaf node that contain the first occurance of key that we search for
     *
     * [tested]
     */

    private node select(node root, String key)
    {
        if(root instanceof leafNode) {
            if(root.find(key) == true)
                return root;
            return null;
        }
        int index = root.getPosition(key);
        if(index == -1)
            return select( ( (innerNode) root).biggerThan, key);

        node rootNode = (node)root.refs.get(index);
        return select(rootNode, key);
    }

    /**
     * should we handle range stuff here
     * or the table will handle it using the node reference returned from find method.
     */

    /**
     * for testing purpose.
     */

    public void traverseBTree()
    {
        assert size !=0 : "tree is empty ";
        traverseBTree(root);
    }

    public void traverseBTree(node root)
    {
        // dfs manner
        System.out.println("keys " + root.keys);
        if(root instanceof leafNode) {
            System.out.println("leaf node ");
            return ;
        }

        for (Object ref:root.refs) {
            node nodRef = (node) ref;
            traverseBTree(nodRef);
        }
        System.out.println("go for bigger than ");
        traverseBTree(((innerNode) root).biggerThan);

        return ;
    }

}