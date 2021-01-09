package table;
import Btree.*;
import java.util.LinkedList;

public class table {
    LinkedList<user> users;

    /*
    * have to be synchronized with each insert and delete operation into the linked list
    * the tree will store reference to the user object, that is stored in the linked list
    * */
    bTree bTreeindex;

    public void table()
    {
        System.out.println("table object has been created");
    }

    public boolean insert(user newUser)
    {
        return false;
    }

    public boolean delete(String key)
    {
        return false;
    }

    public user selectEqual(String name)
    {
        return new user();
    }

    public LinkedList<user> selectMoreEquak (String name)
    {
        return new LinkedList<user>();
    }

}
