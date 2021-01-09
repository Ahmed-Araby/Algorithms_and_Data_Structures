package Btree;

import table.user;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.LinkedList;

/**
 * biggerThan is reference to node that hold keys bigger than
 * all the keys in the keys array list of the current node.
 */

public class innerNode extends node
{
    String name;
    node biggerThan;
    public innerNode()
    {
        super();
        biggerThan = null;
    }

    public innerNode(ArrayList<String> keys, ArrayList<Object> refs, node biggerThan)
    {
        super(keys, refs);
        this.biggerThan = biggerThan;
    }

    /**
     *
     * @return reference to the newly created inner node
     */

    public node split()
    {
        assert this.needSplit() == true : "the inner node capacity is okay no need to split";

        // copy the second half of the keys and refs
        ArrayList<String> newKeys = new ArrayList<>();

        /**
         * this could be leaf node or inner node
         */
        ArrayList<Object> newRefs = new ArrayList<>();

        int mid = this.getSize() / 2;
        for(int index = mid; index < this.getSize(); index +=1)
        {
            newKeys.add(this.keys.get(index));
            newRefs.add(this.refs.get(index));
        }

        // resize the original keys and refs arrays
        int index = this.getSize()-1;
        for(; index>=mid; index--)
        {
            this.keys.remove(index);
            this.refs.remove(index);
        }

        /**[ this part is not tested yet ] */
        // create new node and
        // redirect bigger than reference
        innerNode newInnerNode = new innerNode(newKeys, newRefs, this.biggerThan);
        this.biggerThan = (node)this.refs.get(index);
        this.keys.remove(index);
        this.refs.remove(index);


        return newInnerNode;
    }

    /**
     * merge 2 inner nodes
     * the caller node will be the left node
     * caller node will contain the keys of both nodes at the end
     *
     * @param rightNode node with all it keys > than the called node keys
     * @param leftNodeKey key from the parent node that we use to descend to the caller node.
     * [tested]
     */

    public void merge(innerNode rightNode, String leftNodeKey)
    {
        this.keys.add(leftNodeKey);
        this.refs.add(this.biggerThan);
        for(int index = 0; index < rightNode.getSize(); index++)
        {
            String tmpKey = rightNode.keys.get(index);
            Object tmpRef = rightNode.refs.get(index);
            this.keys.add(tmpKey);
            this.refs.add(tmpRef);
        }
        this.biggerThan = rightNode.biggerThan;
    }

}
