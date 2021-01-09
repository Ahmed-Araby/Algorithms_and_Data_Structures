package Btree;

import table.user;
import java.util.ArrayList;

public class leafNode extends node
{
    public node next, prev;
    leafNode()
    {
        next = prev = null;
    }
    leafNode(ArrayList<String> keys , ArrayList<Object> refs)
    {
        super(keys, refs);
        next = prev = null;
    }

    @Override
    public node split()
    {
        assert this.needSplit() == true : "the leaf node capacity is okay no need to split";

        // copy the second half of the keys and refs
        ArrayList<String> newKeys = new ArrayList<>();

        /**
         * this could point to leaf nods
         * or user object of the actual data that we point at.
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

        // create new node
        leafNode newLeafNode = new leafNode(newKeys, newRefs);

        // redirect sibiling pointers
        newLeafNode.next = this.next;
        this.next = newLeafNode;
        newLeafNode.prev = this;


        return newLeafNode;
    }

    /**
     *  merge 2 leaf nodes
     *  the caller node will be the left node
     *  caller node will contain the keys of both nodes at the end
     * @param rightNode right node mean that all keys in right node > all keys in the left node
     *                  both nodes have the same parent node.
     * [tested]
     */
    public void merge(leafNode rightNode)
    {
        assert this.getSize() != 0 && rightNode.getSize() !=0 : "empty nodes can't be merged";
        for(int index=0; index<rightNode.getSize(); index++)
        {
            String tmpKey = rightNode.keys.get(index);
            Object tmpRef = rightNode.refs.get(index);
            this.keys.add(tmpKey);
            this.refs.add(tmpRef);
        }
        this.next = rightNode.next;
    }
}
