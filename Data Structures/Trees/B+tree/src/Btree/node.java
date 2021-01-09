package Btree;

import java.lang.reflect.Array;
import java.util.ArrayList;
import table.user;

import javax.swing.plaf.SpinnerUI;

/*
 * node will hold
 * array of keys
 * array of references
 * number of allowed keys
 * */
abstract class node {
    public int keysLimit = config.keysLimit;
    public ArrayList<String> keys;


    /**
     * the object that we refer at could be
     *
     * inner node inside the tree
     * leaf node from the level before the end
     * user object in the leaf node
     */
    public ArrayList<Object> refs;

    public node()
    {
        keys = new ArrayList<String>();
        refs = new ArrayList<Object>();
    }

    public node(ArrayList<String> keys, ArrayList<Object> refs)
    {
        this.keys = keys;
        this.refs = refs;
    }

    /*
    * get the first index with keys[index] >= key
    * -1 if the array is empty or the key is the biggest
    * [tested]
    * */

    public int getPosition(String key)
    {
        int lIndex = 0, rIndex = keys.size()-1, mid = 0;
        int position = -1;

        while(lIndex <=rIndex)
        {
            mid = (lIndex + rIndex) / 2;
            int compRes = keys.get(mid).compareTo(key);
            if(compRes >= 0)
            {
                rIndex = mid-1;
                position = mid;
            }

            else if(compRes <0)
            {
                lIndex = mid +1;
            }
        }

        return position;
    }

    /**
     * remove key and corresponding reference at position index
     * @param index
     * @return true indicating that the index is valid and the deletion is successful
     */
    public boolean remove(int index)
    {
        assert index >=0 && index < getSize() : "index out of range";
        keys.remove(index);
        refs.remove(index);

        return true;
    }

    public boolean delete(String key)
    {
        int index = getPosition(key);
        if(index == -1)
            return false;

        String curKey = keys.get(index);
        int compRes = key.compareTo(curKey);
        if(compRes != 0)
            return false;

        remove(index);
        return true;
    }

    /**
     *
     * @param key
     * @param ref
     * @return position of of key and ref in the keys and refs array
     *          they always will be inserted in the same position.
     * [tested]
     */

    public int insert(String key, Object ref)
    {
        int position = getPosition(key);
        insertKey(key, position);
        insertRef(ref, position);
        return position;
    }
    /**
     *
     * @param key
     * @param position index of the first key in keys > argument key
     * @return true if the key is successfully inserted
     *          false other wise
     * [tested]
     */

    public boolean insertKey(String key, int position)
    {
        if(position == -1)
            keys.add(key);
        else
            keys.add(position, key);

        return true;
    }

    /**
     *
     * @param ref reference to node in case of inner node
     *            and reference to user object in case of leaf node
     * @param position corresponding position of the key related to this reference
     * @return true if the reference is inserted successfully.
     * [tested]
     */
    public boolean insertRef(Object ref ,int position)
    {
        if(position == -1)
            refs.add(ref);
        else
            refs.add(position, ref);
        return true;
    }

    public void setKeysLimit(int keysLimit)
    {
        this.keysLimit = keysLimit;
    }

    /**
     *
     * @return true if the number of key in the node
     * equal | exceed the limit of allowed keys per node before split.
     * [tested]
     */
    public boolean needSplit()
    {
        return keys.size() >= keysLimit;
    }

    public boolean needMerge()
    {
        return getSize() < keysLimit /2 -1;
    }

    public int getSize()
    {
        return keys.size();
    }

    public boolean find(String key)
    {
        assert getSize()!=0 : "node is empty, it is supposed to be deleted";

        int index = getPosition(key);
        if(index == -1)
            return false;

        int compRes = key.compareTo(keys.get(index));
        if(compRes == 0)
            return true;

        return false;
    }

    /**
     *
     * @return key in the median position that will be placed in the parent node
     * for spliting operation.
     */

    public String getMedianKey()
    {
        assert getSize()==keysLimit : "node is not full";
        int median = getSize() / 2 -1;
        return keys.get(median);
    }
    /*
     * split the current node and return
     * reference to the new generated node
     * */
    abstract public node split();

    // for testing purpose
    public void disp()
    {
        System.out.println("here");
        int index = 0;
        for(String key: keys)
        {
            System.out.printf("key : " + key + "\n");
            user userObj= (user) refs.get(index);
            System.out.printf("ref name : " + userObj.name + "\n");
            index +=1;
        }
        return ;
    }

}