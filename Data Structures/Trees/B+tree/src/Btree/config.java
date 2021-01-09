package Btree;

public class config
{
    /**
     * max number of keys in both leaf node and
     * inner node
     * however inner node has extra branch point for keys bigger
     * than any key in the current inner node.
     * we can't go lower than 4 as this could make
     * inner node have only bigger than branch and no keys for less than branches.
     */
    public static int keysLimit = 7;

}
